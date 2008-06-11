#!/usr/bin/env python
"""
GUI framework and application for use with Python unit testing framework.
Execute tests written using the framework provided by the 'unittest' module.

Further information is available in the bundled documentation, and from

  http://pyunit.sourceforge.net/

Copyright (c) 1999, 2000, 2001 Steve Purcell
This module is free software, and you may redistribute it and/or modify
it under the same terms as Python itself, so long as this copyright message
and disclaimer are retained in their original form.

IN NO EVENT SHALL THE AUTHOR BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OF
THIS CODE, EVEN IF THE AUTHOR HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH
DAMAGE.

THE AUTHOR SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
PARTICULAR PURPOSE.  THE CODE PROVIDED HEREUNDER IS ON AN "AS IS" BASIS,
AND THERE IS NO OBLIGATION WHATSOEVER TO PROVIDE MAINTENANCE,
SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
"""

__author__ = "Steve Purcell (stephen_purcell@yahoo.com)"
__version__ = "$Revision: 1.1 $"[11:-2]

#********************************************************
#************Modified by: Zoltan Molnar******************
#************zolmol@isis.vanderbilt.edu******************
#*****************Vanderbilt Univ.***********************
#********************************************************

###########################################################################################
# Execution Mode Selection: Time-out Mode or Normal Mode?
#    Normal  mode: testsuites and testcases are executed in the same process, showing errors
#                  in the list box below, and the total number of errors, failures in the 
#                  results box, progress while it is executing
#    Timeout mode: testsuites are executed in a spawned process if one exceeds the timeout
#                  limit, it is killed. It is important to note that the timeout is 
#                  calculated per one testsuite (not per testcase).
#                  The total progressbar is shown in blue, but no other details are captured
#                  from the running tests. For errors and failures see the DOS window, the
#                  testcases produce output to.
###########################################################################################
gTimeOutMode = False

###########################################################################################
# Two flags for time-out mode
#------------------------------------------------------------------------------------------
# 1.Location of python.exe on your hard drive
#==========================================================================================
gPythonExe                                = "c:/python24/python.exe"
#
#------------------------------------------------------------------------------------------
# 2.Timeout for each testcase
#==========================================================================================
gDefTimeOut                               = 120
#
#
# End flag-section for time-out mode
###########################################################################################


###########################################################################################
# testcase files loaded on these pattern
# use these patterns if you have named your testcases files according to some naming convention
# i.e. : tc_1, tc_2
# endPattern is matched against the portion preceeding the extension, so it must not contain '.py'
#==========================================================================================
gStartPattern = ''  
gEndPattern = ''

###########################################################################################
# list here all files (as exceptions) you may not want to include in your test list
# when you load a directory of testcases
#==========================================================================================
gSkipTheseFilesOnLoad = \
        [ '__init__.py' 
        , 'unittest.py'
        , 'unittestgui.py'
        , 'gpyunit.py'
        , 'gmeutils.py'
        ] 

###########################################################################################
# animate file selection when multiple files are executed
#==========================================================================================
gAnimateIt = False

###########################################################################################
# debug messages displayed if True [not about testcases,but about the way they are invoked]
#==========================================================================================
gDebugIt = False #True

import unittest
import sys
import os
import time
import Tkinter
import tkFileDialog
import tkMessageBox
import traceback
import win32process
import win32api
import types

import string
tk = Tkinter # Alternative to the messy 'from Tkinter import *' often seen

class Debugger:
        def log(self, x):
            if gDebugIt:
                print x


##############################################################################
# GUI framework classes
##############################################################################

class BaseGUITestRunner:
    """Subclass this class to create a GUI TestRunner that uses a specific
    windowing toolkit. The class takes care of running tests in the correct
    manner, and making callbacks to the derived class to obtain information
    or signal that events have occurred.
    """
    def __init__(self, *args, **kwargs):
        self.currentResult = None
        self.running = 0
        self.__rollbackImporter = None
        apply(self.initGUI, args, kwargs)

    def getSelectedTestName(self):
        "Override to return the name of the test selected to be run"
        pass

    def errorDialog(self, title, message):
        "Override to display an error arising from GUI usage"
        pass

    def runClicked(self):
        "To be called in response to user choosing to run a test"
        if self.running: return
        testName = self.getSelectedTestName()
        if not testName:
            self.errorDialog("Test name entry", "You must enter a test name")
            return
        if self.__rollbackImporter:
            self.__rollbackImporter.rollbackImports()
        self.__rollbackImporter = RollbackImporter()
        try:
            test = unittest.defaultTestLoader.loadTestsFromName(testName)
        except:
            exc_type, exc_value, exc_tb = sys.exc_info()
            apply(traceback.print_exception,sys.exc_info())
            self.errorDialog("Unable to run test '%s'" % testName,
                             "Error loading specified test: %s, %s" % \
                             (exc_type, exc_value))
            return
        self.currentResult = GUITestResult(self)
        self.totalTests = test.countTestCases()
        self.running = 1
        self.notifyRunning()
        test.run(self.currentResult)
        self.running = 0
        self.notifyStopped()

    def stopClicked(self):
        "To be called in response to user stopping the running of a test"
        if self.currentResult:
            self.currentResult.stop()

    # inserted by zolmol
    def exploreBeforeRun(self, testName):
        "To be called in response to user choosing to run a test"
        if not testName:
            self.errorDialog("Test name entry", "You must enter a test name")
            return
        if self.__rollbackImporter:
            self.__rollbackImporter.rollbackImports()
        self.__rollbackImporter = RollbackImporter()
        try:
            test = unittest.defaultTestLoader.loadTestsFromName(testName)
        except:
            exc_type, exc_value, exc_tb = sys.exc_info()
            apply(traceback.print_exception,sys.exc_info())
            self.errorDialog("Unable to run test '%s'" % testName,
                             "Error loading specified test: %s, %s" % \
                             (exc_type, exc_value))
            return
        self.grandTotalTests += test.countTestCases()

    # inserted by zolmol
    # runs the method given in its parameter
    def runThisSuite(self, testName):
        "To be called in response to user choosing to run a test"
        if self.running: return
        if not testName:
            self.errorDialog("Test name entry", "You must enter a test name")
            return
        if self.__rollbackImporter:
            self.__rollbackImporter.rollbackImports()
        self.__rollbackImporter = RollbackImporter()
        try:
            test = unittest.defaultTestLoader.loadTestsFromName(testName)
        except:
            exc_type, exc_value, exc_tb = sys.exc_info()
            apply(traceback.print_exception,sys.exc_info())
            self.errorDialog("Unable to run test '%s'" % testName,
                             "Error loading specified test: %s, %s" % \
                             (exc_type, exc_value))
            return
        self.currentResult = GUITestResult(self)
        self.totalTests = test.countTestCases()
        self.running = 1
        self.notifyRunning()
        test.run(self.currentResult)
        self.running = 0
        self.notifyStopped()

    # Required callbacks

    def notifyRunning(self):
        "Override to set GUI in 'running' mode, enabling 'stop' button etc."
        pass

    def notifyStopped(self):
        "Override to set GUI in 'stopped' mode, enabling 'run' button etc."
        pass

    def notifyTestFailed(self, test, err):
        "Override to indicate that a test has just failed"
        pass

    def notifyTestErrored(self, test, err):
        "Override to indicate that a test has just errored"
        pass

    def notifyTestStarted(self, test):
        "Override to indicate that a test is about to run"
        pass

    def notifyTestFinished(self, test):
        """Override to indicate that a test has finished (it may already have
           failed or errored)"""
        pass


class GUITestResult(unittest.TestResult):
    """A TestResult that makes callbacks to its associated GUI TestRunner.
    Used by BaseGUITestRunner. Need not be created directly.
    """
    def __init__(self, callback):
        unittest.TestResult.__init__(self)
        self.callback = callback

    def addError(self, test, err):
        unittest.TestResult.addError(self, test, err)
        self.callback.notifyTestErrored(test, err)

    def addFailure(self, test, err):
        unittest.TestResult.addFailure(self, test, err)
        self.callback.notifyTestFailed(test, err)

    def stopTest(self, test):
        unittest.TestResult.stopTest(self, test)
        self.callback.notifyTestFinished(test)

    def startTest(self, test):
        unittest.TestResult.startTest(self, test)
        self.callback.notifyTestStarted(test)


class RollbackImporter:
    """This tricky little class is used to make sure that modules under test
    will be reloaded the next time they are imported.
    """
    def __init__(self):
        self.previousModules = sys.modules.copy()
        
    def rollbackImports(self):
        for modname in sys.modules.keys():
            if not self.previousModules.has_key(modname):
                # Force reload when modname next imported
                del(sys.modules[modname])


##############################################################################
# Tkinter GUI
##############################################################################

_ABOUT_TEXT="""\
PyUnit unit testing framework.

For more information, visit
http://pyunit.sourceforge.net/

Copyright (c) 2000 Steve Purcell
<stephen_purcell@yahoo.com>

GPyUnit unit testing framework
- extended version of PyUnit -
by: Zoltan Molnar
Vanderbilt University
<zolmol@isis.vanderbilt.edu>

"""
_HELP_TEXT="""\
Select a testcase directory by its name or by Load button. Testcase files can be loaded and run from ./ or subdirectory of ./ .
Note: if subdirectory specified '__init__.py' files will be created along the access path to enable instant Python access.

Select the desired test files, and Run Selected or Run All. Double click on a test file implies running that test.
The 'suites()' method will be called in each file.

Click on each file in the list to see the individual results of the last run.

Double click on an error in the listbox to see more information about it, \
including the stack trace.

For more information, visit
http://pyunit.sourceforge.net/
or see the bundled documentation

Shortcuts:
F1		Help
F3		Load directory
Shift+F3		Jump to directory selection edit field
F4		Show Next Error
Shift+F4		Show Prev Error
F5		Run all
F6		Run selected
F8		Del All
F10		Options
"""

class TkTestRunner(BaseGUITestRunner):
    """An implementation of BaseGUITestRunner using Tkinter.
    """
    def initGUI(self, root, initialTestName):
        """Set up the GUI inside the given root window. The test name entry
        field will be pre-filled with the given initialTestName.
        """
        self.root = root
        # Set up values that will be tied to widgets
        self.suiteNameVar = tk.StringVar()
        self.suiteNameVar.set(initialTestName)
        self.statusVar = tk.StringVar()
        self.statusVar.set("Idle")
        self.runCountVar = tk.IntVar()
        self.failCountVar = tk.IntVar()
        self.errorCountVar = tk.IntVar()
        self.remainingCountVar = tk.IntVar()
        self.grandErrorDescr = { }
        self.grandTotalTests = 0
        self.grandRunCountVar = tk.IntVar()
        self.grandFailCountVar = tk.IntVar()
        self.grandErrorCountVar = tk.IntVar()
        self.grandRemainingCountVar = tk.IntVar()
        self.top = tk.Frame()
        self.top.pack(fill=tk.BOTH, expand=1)
        self.createWidgets()
        self.tsts = []
        self.myRunningOptions = RunningOptions()
        self.startUpDirectory = os.path.abspath(os.path.curdir)

    def createWidgets(self):
        """Creates and packs the various widgets.
        
        Why is it that GUI code always ends up looking a mess, despite all the
        best intentions to keep it tidy? Answers on a postcard, please.
        """
        
        #self.root.bind('<Key>', lambda ev, self=self: self.runKeyHandler(ev))
        self.root.bind('<F1>', lambda ev, self=self: self.showHelpDialog())
        self.root.bind('<Shift-F3>', lambda ev, self=self: self.focusToDirEdit())
        self.root.bind('<F3>', lambda ev, self=self: self.loadClicked())
        self.root.bind('<F4>', lambda ev, self=self: self.showNextErr())
        self.root.bind('<Shift-F4>', lambda ev, self=self: self.showPrevErr())
        self.root.bind('<Alt-F4>', lambda ev, self=self: self.quitApp(), add='')
        self.root.bind('<F5>', lambda ev, self=self: self.runAllClicked())
        self.root.bind('<F6>', lambda ev, self=self: self.runSelClicked())
        self.root.bind('<F8>', lambda ev, self=self: self.delAllClicked())
        self.root.bind('<F10>', lambda ev, self=self: self.showMyOptionsDialog())
        
        # Status bar
        statusFrame = tk.Frame(self.top, relief=tk.SUNKEN, borderwidth=2)
        statusFrame.pack(anchor=tk.SW, fill=tk.X, side=tk.BOTTOM)
        tk.Label(statusFrame, textvariable=self.statusVar).pack(side=tk.LEFT)

        # Area to enter name of test to run
        leftFrame = tk.Frame(self.top, borderwidth=3)
        leftFrame.pack(fill=tk.BOTH, side=tk.LEFT, anchor=tk.NW, expand=1)
        suiteNameFrame = tk.Frame(leftFrame, borderwidth=3)
        suiteNameFrame.pack(fill=tk.X)
        
        tk.Label(suiteNameFrame, text="Directory:").pack(side=tk.LEFT)
        self.entry = tk.Entry(suiteNameFrame, textvariable=self.suiteNameVar, width=25)
        self.entry.pack(side=tk.LEFT, fill=tk.X, expand=1)
        self.entry.focus_set()
        self.entry.bind('<Key-Return>', lambda ev, self=self: self.loadDirectoryOnEnterPressed())

        # FileListBox frame
        tk.Label(leftFrame, text="Files in directory:").pack(anchor=tk.W)
        filelistFrame = tk.Frame(leftFrame, borderwidth=2)      #, relief=tk.GROOVE
        filelistFrame.pack(fill=tk.X, expand=0, anchor=tk.NW)
        scrollbar = tk.Scrollbar(filelistFrame, orient=tk.VERTICAL)#, width = 20)
        xcrollbar = tk.Scrollbar(filelistFrame, orient=tk.HORIZONTAL) #, width = 20)
        self.fileListbox = tk.Listbox(filelistFrame
                        , yscrollcommand=scrollbar.set
                        , xscrollcommand=xcrollbar.set
                        , selectmode = tk.EXTENDED
                        , width = 47
                        , height = 10
                        )    # checkable
        scrollbar.config(command=self.fileListbox.yview)
        xcrollbar.config(command=self.fileListbox.xview)
        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        xcrollbar.pack(side=tk.BOTTOM, fill=tk.X)
        self.fileListbox.pack(side=tk.LEFT, fill=tk.BOTH, expand=1,
                          anchor=tk.NW)
        self.fileListbox.bind("<Double-1>",
                               lambda ev, self=self: self.doubleClickedFileListItem())
        self.fileListbox.bind("<ButtonRelease-1>",
                               lambda ev, self=self: self.showLastRunInfo())
        self.fileListbox.bind("<Key-Up>", 
                               lambda ev,self=self: self.showLastRunInf2(ev))
        self.fileListbox.bind("<Key-Down>", 
                               lambda ev,self=self: self.showLastRunInf2(ev))

        ## firstFrame ------->  in leftFrame
        firstFrame = tk.Frame( leftFrame, relief=tk.GROOVE, borderwidth=2)
        firstFrame.pack(fill=tk.X, expand=0, anchor=tk.NW)
        
        #### progressFrame -----> in firstFrame
        progressFrame = tk.Frame(firstFrame)#, relief=tk.GROOVE, borderwidth=2)
        progressFrame.pack(fill=tk.X, expand=0, anchor=tk.NW)


        ###### Label        ------> in progressFrame
        tk.Label(progressFrame, text="Progress:").pack(side = tk.LEFT, anchor=tk.W)

        ###### Progress bar ------> in progressFrame
        self.progressBar = ProgressBar(progressFrame, relief=tk.SUNKEN,
                                       borderwidth=1)
        self.progressBar.pack(fill=tk.X, expand=1,side=tk.LEFT)

        #### partResultsFrame-------> in firstFrame
        partResultsFrame = tk.Frame(firstFrame, relief=tk.SUNKEN, borderwidth = 2)
        partResultsFrame.pack(fill=tk.X, expand=0, anchor=tk.NW)

        ###### Area with labels reporting results
        for label, var in (('Run:', self.runCountVar),
                           ('Failures:', self.failCountVar),
                           ('Errors:', self.errorCountVar),
                           ('Remaining:', self.remainingCountVar)):
            tk.Label(partResultsFrame, text=label).pack(side=tk.LEFT)
            tk.Label(partResultsFrame, textvariable=var,
                     foreground="blue").pack(side=tk.LEFT, fill=tk.X,
                                             expand=1, anchor=tk.W)


        ## secndFrame ------->  in leftFrame
        secndFrame = tk.Frame( leftFrame, relief=tk.GROOVE, borderwidth=2)
        secndFrame.pack(fill=tk.X, expand=0, anchor=tk.NW)
        
        #### grandProgressFrame -----------> secndFrame
        grandProgressFrame = tk.Frame(secndFrame) #, relief=tk.GROOVE, borderwidth=2)
        grandProgressFrame.pack(fill=tk.X, expand=0, anchor=tk.NW)

        ###### Label ---------------->grandProgressFrame
        tk.Label(grandProgressFrame, text="   Total:   ").pack(side = tk.LEFT, anchor=tk.W)

        ###### grand Progress Bar ---------> grandProgressFrame
        self.grandProgressBar = ProgressBar(grandProgressFrame, relief=tk.SUNKEN,
                                       borderwidth=1)
        self.grandProgressBar.pack(fill=tk.X, expand=1)

        #### grandResultFrame-----------> in secndFrame
        grandResultsFrame = tk.Frame(secndFrame, relief=tk.SUNKEN, borderwidth=2)
        grandResultsFrame.pack(fill=tk.X, expand=0, anchor=tk.NW)

        ###### Area with labels for global reporting results
        for label, var in (('Run:', self.grandRunCountVar),
                           ('Failures:', self.grandFailCountVar),
                           ('Errors:', self.grandErrorCountVar),
                           ('Remaining:', self.grandRemainingCountVar)):
            tk.Label(grandResultsFrame, text=label).pack(side=tk.LEFT)
            tk.Label(grandResultsFrame, textvariable=var,
                     foreground="blue").pack(side=tk.LEFT, fill=tk.X,
                                             expand=1, anchor=tk.W)


        # Area with buttons to start/stop tests and quit
        buttonFrame = tk.Frame(self.top, borderwidth=3)
        buttonFrame.pack(side=tk.LEFT, anchor=tk.NW, fill=tk.Y)
        
        self.loadButton = tk.Button(buttonFrame, text="Load",
                                    command=self.loadClicked)
        self.loadButton.pack(fill=tk.X, pady = 0)

        #self.stopGoButton = tk.Button(buttonFrame, text="Start",
        #                              command=self.runClicked)
        #self.stopGoButton.pack(fill=tk.X)

        self.runAllButton = tk.Button(buttonFrame, text="Run All",
                                      command=self.runAllClicked)
        self.runAllButton.pack(fill=tk.X, pady = 0)

        self.runSelButton = tk.Button(buttonFrame, text="Run Sel",
                                      command=self.runSelClicked)
        self.runSelButton.pack(fill=tk.X, pady = 0)

        self.clearAllButton = tk.Button(buttonFrame, text="Del All",
                                      command=self.delAllClicked)
        self.clearAllButton.pack(fill=tk.X, pady = 0)

        self.clearSelButton = tk.Button(buttonFrame, text="Del Sel",
                                      command=self.delSelClicked)
        self.clearSelButton.pack(fill=tk.X, pady = 0)

        tk.Button(buttonFrame, text="Options",
                  command=self.showMyOptionsDialog).pack(fill=tk.X, pady = 5)

        tk.Button(buttonFrame, text="Reset",
                  command=self.resetResultsList).pack(side=tk.TOP, fill=tk.X, pady = 120)

        tk.Button(buttonFrame, text="Close",
                  command=self.top.quit).pack(side=tk.BOTTOM, fill=tk.X)
        tk.Button(buttonFrame, text="About",
                  command=self.showAboutDialog).pack(side=tk.BOTTOM, fill=tk.X)
        tk.Button(buttonFrame, text="Help",
                  command=self.showHelpDialog).pack(side=tk.BOTTOM, fill=tk.X)

        # List box showing errors and failures
        tk.Label(leftFrame, text="Failures and errors:").pack(anchor=tk.W)
        listFrame = tk.Frame(leftFrame, relief=tk.SUNKEN, borderwidth=2)
        listFrame.pack(fill=tk.BOTH, anchor=tk.NW, expand=1)


        self.grandErrorListbox = tk.Listbox(listFrame, foreground='red',
                                       selectmode=tk.SINGLE,
                                       selectborderwidth=0)
        self.grandErrorListbox.pack(side=tk.LEFT, fill=tk.BOTH, expand=1,
                               anchor=tk.NW)
        listScroll = tk.Scrollbar(listFrame, command=self.grandErrorListbox.yview)
        listScroll.pack(side=tk.LEFT, fill=tk.Y, anchor=tk.N)
        self.grandErrorListbox.bind("<Double-1>",
                               lambda e, self=self: self.showClickedError())
        self.grandErrorListbox.configure(yscrollcommand=listScroll.set)


    def getSelectedTestName(self):
        return self.suiteNameVar.get()
        #return makeOneSuite

    def errorDialog(self, title, message):
        tkMessageBox.showerror(parent=self.root, title=title,
                               message=message)

    def notifyRunning(self):
        self.runCountVar.set(0)
        self.failCountVar.set(0)
        self.errorCountVar.set(0)
        self.remainingCountVar.set(self.totalTests)
        self.errorInfo = []

        #while self.grandErrorListbox.size():
        #    self.grandErrorListbox.delete(0)

        #Stopping seems not to work, so simply disable the start button
        ##self.stopGoButton.config(command=self.stopClicked, text="Stop")
        #self.stopGoButton.config(state=tk.DISABLED)

        self.progressBar.setProgressFraction(0.0)
        self.top.update_idletasks()

    def notifyStopped(self):
        #self.stopGoButton.config(state=tk.ACTIVE)
        ##self.stopGoButton.config(command=self.runClicked, text="Start")
        self.statusVar.set("Idle")

    def notifyTestStarted(self, test):
        self.statusVar.set(str(test))
        self.top.update_idletasks()

    def notifyTestFailed(self, test, err):
        self.failCountVar.set(1 + self.failCountVar.get())
        self.grandFailCountVar.set(1 + self.grandFailCountVar.get())

        self.errorInfo.append((test,err))
        self.grandErrorInfo.append((test,err))

        self.grandErrorListbox.insert(tk.END, "Failure: %s" % test)

    def notifyTestErrored(self, test, err):
        self.errorCountVar.set(1 + self.errorCountVar.get())
        self.grandErrorCountVar.set(1 + self.grandErrorCountVar.get())

        self.errorInfo.append((test,err))
        self.grandErrorInfo.append((test,err))

        self.grandErrorListbox.insert(tk.END, "Error: %s" % test)

    def notifyTestFinished(self, test):
        self.runCountVar.set(1 + self.runCountVar.get())
        self.remainingCountVar.set(self.remainingCountVar.get() - 1)
        
        self.grandRunCountVar.set(1 + self.grandRunCountVar.get())
        self.grandRemainingCountVar.set(self.grandRemainingCountVar.get() -1)

        fractionDone = float(self.runCountVar.get())/float(self.totalTests)
        fillColor = len(self.errorInfo) and "red" or "green"
        self.progressBar.setProgressFraction(fractionDone, fillColor)

        fractionDone = float(self.grandRunCountVar.get())/float(self.grandTotalTests)
        fillColor = len(self.grandErrorInfo) and "red" or "green"
        self.grandProgressBar.setProgressFraction(fractionDone, fillColor)
        
        self.errorDescr.append( ( self.runCountVar.get(), self.failCountVar.get(), self.errorCountVar.get(), self.remainingCountVar.get() ) )

    def showMyOptionsDialog(self):
        MyOptionDialog(self.root, self, self.myRunningOptions)

    def showAboutDialog(self):
        tkMessageBox.showinfo(parent=self.root, title="About GPyUnit",
                              message=_ABOUT_TEXT)

    def showHelpDialog(self):
        tkMessageBox.showinfo(parent=self.root, title="GPyUnit help",
                              message=_HELP_TEXT)

    def showClickedError(self):
        selection = self.grandErrorListbox.curselection()
        if not selection: return
        selected = int(selection[0])
        self.showSelectedError( selected)

    def showSelectedError(self, selected):
        txt = self.grandErrorListbox.get(selected)
        test, error = self.grandErrorInfo[selected]
        tracebackLines = apply(traceback.format_exception, error + (10,))
        tracebackText = string.join(tracebackLines,'')

        # modal dialog invokation
        MyChildDialog(self.root, self, txt, tracebackText)

    def deselectItemInFailBox(self, err_idx):
        self.grandErrorListbox.selection_clear( err_idx, err_idx)

    def selectItemInFailBox(self, err_idx):
        self.grandErrorListbox.selection_set( err_idx, err_idx)

        # scroll the view to show the currently selected item
        self.grandErrorListbox.see( err_idx )

    def showNextErr(self):
        if self.grandErrorListbox.size() == 0: 
            tkMessageBox.showerror( message='No error message found')
            return

        # default value: if no item selected show the first
        err_idx = 0

        errs = self.grandErrorListbox.curselection()
        if len(errs) > 0:
            # if item was selected, show the next
            err_idx = string.atoi( errs[0])
            self.deselectItemInFailBox( err_idx)
            err_idx += 1
            if err_idx >= self.grandErrorListbox.size():
                err_idx = 0

        # select item in the box
        self.selectItemInFailBox( err_idx)

        # show the error in a dialog
        self.showSelectedError( err_idx)
    
    def showPrevErr(self):
        if self.grandErrorListbox.size() == 0: 
            tkMessageBox.showerror( message='No error message found')
            return

        # default value: if no item selected show the last
        err_idx = self.grandErrorListbox.size() - 1

        errs = self.grandErrorListbox.curselection()
        if len(errs) > 0:
            # if item was selected, show the next
            err_idx = string.atoi( errs[0])
            self.deselectItemInFailBox( err_idx)
            err_idx -= 1
            if err_idx < 0:
                err_idx = self.grandErrorListbox.size() - 1

        # select item in the box
        self.selectItemInFailBox( err_idx)

        # show the error in a dialog
        self.showSelectedError( err_idx)

    def loadDirectoryOnEnterPressed(self):
        # return if path not specified
        if len(self.suiteNameVar.get()) == 0 : return

        os.chdir(self.startUpDirectory)

        # path syntax: '..' not allowed, because it goes up
        if '..' in self.suiteNameVar.get():
            tkMessageBox.showerror(parent=self.root, title="Error",
                              message="Testcases must be located in ./ or in a subdirectory of ./" )
            return

        abs_path = False
        # path syntax: absolute path with drive spec'd
        if ':' in self.suiteNameVar.get():
            abs_path = True
        
        # path syntax: absolute path, but drive missing => prepend it before the path
        if '/' == self.suiteNameVar.get()[0] or '\\' == self.suiteNameVar.get()[0]:
            abs_path = True
            drive, pt = os.path.splitdrive(os.path.realpath(os.path.curdir))
            self.suiteNameVar.set( drive.lower() + self.suiteNameVar.get())

        # if not current directory [ ./ , .\] specified
        if self.suiteNameVar.get() != './' and self.suiteNameVar.get() != '.\\':
             # if package syntax: 'subdir1.subdir2' specified then convert from '.' to '\\'
             self.suiteNameVar.set( string.replace( os.path.normpath( self.suiteNameVar.get()), '.','\\'))

        
        if abs_path:
            dir_to_load = self.suiteNameVar.get()
        else:
            dir_to_load = os.path.join( os.path.abspath(os.path.curdir), self.suiteNameVar.get())
        
        Debugger().log( "Dir to load: " + dir_to_load)
        allright = self.reloadDirectory( dir_to_load)

        if allright:
            # set the focus to the RunAll Button
            # self.runAllButton.focus_set()
            pass

    def focusToDirEdit(self):
        self.entry.focus_set()

    def loadClicked(self):
        os.chdir(self.startUpDirectory)
        fn = tkFileDialog.askdirectory( title = 'Please select testcase directory in ' + self.startUpDirectory, parent = self.top )

        # quit if cancelled
        if len( fn ) == 0: return

        allright = self.reloadDirectory( fn)
               
        if allright:
            # set the focus to the RunAll Button
            # self.runAllButton.focus_set()
            pass

    def reloadDirectory(self, directory_name):

        # make sure we load a subdir of ./
        self.dirName = os.path.normpath(directory_name)
        
        # exists directory?
        if not os.path.exists( self.dirName):
            tkMessageBox.showerror(parent=self.root, title="GPyUnit", message="Directory doesn't exist")
            return False
            
        Debugger().log("reloadDirectory: " + self.dirName)
        Debugger().log("currentDirectory:" + os.path.normpath(os.path.abspath(os.path.curdir)))
        cp = os.path.commonprefix( [ string.lower(self.dirName), string.lower(os.path.normpath(os.path.abspath(os.path.curdir)))])
        Debugger().log( 'common prefix: ' + cp)
        if string.lower(cp) != string.lower(os.path.normpath(os.path.abspath(os.path.curdir))):
            tkMessageBox.showerror(parent=self.root, title="GPyUnit", message= "Testcases must be located in ./ or in a subdirectory of ./")
            self.statusVar.set("0 testcase files loaded")
            return False
            

        # make sure the subdirectories are loadable (__init__.py creation)
        relDirName = self.dirName[ len(cp) :]
        if len(relDirName) > 0 :
            # subdirectories are loaded
            if relDirName[0] == '\\':
                relDirName = relDirName[ 1:]
            Debugger().log( "relDirName: " + relDirName)
            dir_list = relDirName.split( '\\')
            cp_2 = cp
            for one_dir in dir_list:
                cp_2 = os.path.join( cp_2, one_dir)
                self.makeDirAValidPackage( cp_2);

            self.relPackName = '.'.join( dir_list)
            self.suiteNameVar.set(self.relPackName)
        else:
            # only ./ is loaded
            self.suiteNameVar.set('./')
            self.relPackName = ''

        try:
            # we need to change into that directory, so that the testcase will run as if executed standalone from there
            # this is important if file create, open operations are made
            os.chdir( self.dirName)
        except:
            tkMessageBox.showerror(parent=self.root, title="GPyUnit", message="Could not change directory to " + self.dirName)
            return False

        # clear all items from the listbox
        self.fileListbox.delete(0, tk.END)

        # finally load the files
        self.tsts = self.selectTests( self.dirName, self.myRunningOptions.getStartPattern() , self.myRunningOptions.getEndPattern()) # begin_pattern, and endpattern for testcases

        # copy the file names into the fileListbox
        for i in self.tsts:
            self.fileListbox.insert( tk.END, i)
        
        # show in status line how many files .py files found
        self.statusVar.set(str(len(self.tsts)) + " testcase files loaded")
        
        # reset the results
        self.resetResultsList()
        
        return True
        
        
        
    def makeDirAValidPackage(self,directory_name):
        """Creates a __init__.py file in selected directory if not exists
        """
        fn = os.path.join( directory_name, '__init__.py')
        """
        try:
                Debugger().log("Looking for __init__.py file...")
                #f = file( fn, 'r')
                #Debugger().log( fn + ' found.')
                #f.close()
        except Exception:
                Debugger().log("File __init__.py not found. Creating it in order to see this directory as a package from Python")
                try:
                        f = file( fn, 'w')
                        f.write("#this file created by the unittester to see this directory as a package from Python")
                        f.write("\n#on " + time.asctime( time.localtime()))
                        Debugger().log( fn + ' found.')
                except:
                        Debugger().log("::makeDirAValidPackage: create or write failed")
                f.close()
        """
        
        Debugger().log("Looking for __init__.py file...")
        isinit = os.path.exists( fn)
        if isinit:
            Debugger().log( 'File '+ fn + ' found.')
        else:
            Debugger().log("File __init__.py not found.")
            try:
                f = file( fn, 'w')
                f.write("#this file created by Gpyunit to see this directory as a package from Python")
                f.write("\n#on " + time.asctime( time.localtime()))
                Debugger().log( 'File ' + fn + ' created. This directory will be seen as a Python package.')
            except:
                Debugger().log("::makeDirAValidPackage: create or write failed")
            f.close()

        
    def selectTests( self, dir, begin_pattern = "", end_pattern = ""):
        """makes a list of the .py files matching the [begin_pattern*end_pattern]
           pattern in the directory specified ( exceptions may exist: __init__.py)
           the end_pattern need not contain the ".py" to string
        """
        Debugger().log("::selectTests")
        
        ld = os.listdir( dir)
        pys = []
        for k in ld:
                if k.endswith( end_pattern + ".py") and k.startswith( begin_pattern) and k.lower() not in gSkipTheseFilesOnLoad:
                        pys.append( k[ 0 : k.rfind(".py") ])
        return pys

    def runKeyHandler(self, event):
        
        #print 'K=',event.char, 'state:', event.state
        #print 'seven:', event.send_event
        #print event.keysym_num
        #print event.char, 'Repr:', repr(event.char)
        #s = event.char
        #print 'intben:', s[0]
        """
        print event.keysym
        if event.keycode == 116:    #F5
            self.runAllClicked()
        elif event.keycode == 117:  #F6
            self.runSelClicked()
        elif event.keycode == 114:  #F3
            self.loadClicked()
        elif event.keycode == 115:  #F4
            self.showNextErr()
        elif event.keycode == 119:  #F8
            self.delAllClicked()
        elif event.keycode == 112:  #F1
            self.showHelpDialog()
        """
        #else:
        #    tkMessageBox.showinfo( message = repr(event.keycode) )


    def runAllClicked(self):
        Debugger().log("::runAll")
        
        # clear selection
        self.fileListbox.selection_clear( 0, len(self.tsts))

        # update
        self.top.update_idletasks()

        all = range( len( self.tsts))  # suppose all indexes are selected
        conv = lambda i : (i, self.tsts[i])
        items = map( conv, all)        # converting from index to element
        if len(items) == 0 :
             tkMessageBox.showerror(message = "No testcases are loaded")
             return

        Debugger().log("::runAll  elems selected: " + repr( items ))
        self.runThese( items)
        
        # set the focus to the file list
        self.fileListbox.focus_set()
            
    
    def runSelClicked(self):
        Debugger().log("::runSelected")
        items = self.fileListbox.curselection()
        if len(items) == 0 : 
            tkMessageBox.showerror(message = "No testcase file selected")
            return
        items_save = items

        if gAnimateIt:
            # clear selection
            self.fileListbox.selection_clear( 0, len(self.tsts))
        
        # update
        self.top.update_idletasks()

        items = map(string.atoi, items) # converting from 'index' to index form i.e. from '4' to 4

        #items = map(lambda i,d=self.tsts: d[i], items) # converting from index to element ( compressed )
        conv = lambda i : (i, self.tsts[i])
        items = map( conv, items)       # converting from index to element

        Debugger().log("::runSelected  elems selected: " + repr( items ))
        self.runThese( items)

        if gAnimateIt:
            # revert the selection
            for i in items_save: self.fileListbox.selection_set( i, i )

        # set the focus to the file list
        self.fileListbox.focus_set()
        
    def runThese(self, items):
        Debugger().log( self.relPackName)

        self.errorDescr = []
        self.grandErrorDescr = {}
        self.grandRunCountVar.set(0)
        self.grandFailCountVar.set(0)
        self.grandErrorCountVar.set(0)
        self.grandRemainingCountVar.set(0)
        self.grandTotalTests = 0
        self.errorInfo = []
        self.grandErrorInfo = []
        self.grandErrorListbox.delete(0, tk.END)
        
        # disable the launcher buttons
        self.runSelButton.config(state=tk.DISABLED)
        self.runAllButton.config(state=tk.DISABLED)


        if self.myRunningOptions.getGuardedExec():
            how_many_killed = 0


            self.progressBar.setProgressFraction(0.0)
            self.grandProgressBar.setProgressFraction(0.0)

            # updating the status bar
            self.statusVar.set('Tests running in the background')
            self.top.update_idletasks()

            i = 0
            for idx, name in items:
                r = Manager(self.myRunningOptions).guardedExecOfTestcase( name, self.dirName)
                i += 1
                self.grandProgressBar.setProgressFraction( float(i) / float( len( items)))
                
                if isinstance( r, types.IntType):
                    how_many_killed += r

            # updating the status bar
            if how_many_killed > 0 :
                self.statusVar.set( str(how_many_killed) + ' out of ' + str(len(items)) + ' tests killed for exceeding the timeout.')
            else:
                self.statusVar.set( str(len(items)) + ' tests executed.')
            
            #self.grandRunCountVar.set(len(items))
            #self.grandFailCountVar.set(0)
            #self.grandErrorCountVar.set(0)
            #self.grandRemainingCountVar.set(how_many_killed)

        else:
            # updating the status bar
            self.statusVar.set("Counting testcases...")
            self.top.update_idletasks()
    
            # explore first the files, counting the testcases in each file
            for idx, name in items:
                to_run = '.'.join( [ name, 'suites' ])
                if len( self.relPackName ) > 0 : 
                    to_run = '.'.join( [ self.relPackName, to_run])
    
                Debugger().log( 'Suite to explore:' + to_run)
                self.exploreBeforeRun( to_run)
    
            Debugger().log( "Total number of testmethods: " + str(self.grandTotalTests))
            self.grandRemainingCountVar.set( self.grandTotalTests)
    
            # updating the status bar
            if self.grandTotalTests > 0:
                self.statusVar.set( str(self.grandTotalTests) + " testcases will be run...")
            else:
                self.statusVar.set( "No testcase will be run.")
                tkMessageBox.showerror( title = "Error", message="No testcases will be run!")
                return
    
            self.top.update_idletasks()
    
            # run the tests
            for idx, name in items:
                if gAnimateIt:
                    # animation: moving the selection cursor to the executing testfile
                    self.fileListbox.selection_set( idx, idx)
                    self.top.update_idletasks()
                    self.fileListbox.see( idx )
    
                to_run = '.'.join( [ name, 'suites' ])
                if len( self.relPackName ) > 0 : 
                    to_run = '.'.join( [ self.relPackName, to_run])
    
                Debugger().log( 'Suite to run:' + to_run)
    
                self.runThisSuite( to_run)
                
                if len(self.errorDescr):
                    self.grandErrorDescr[ idx ] = self.errorDescr[-1]
    
            if gAnimateIt:
                # clear the selection
                self.fileListbox.selection_clear( 0, len(self.tsts))
    
        # enable the launcher buttons
        self.runSelButton.config(state=tk.ACTIVE)
        self.runAllButton.config(state=tk.ACTIVE)

    def resetResultsList(self):
        self.runCountVar.set(0)
        self.failCountVar.set(0)
        self.errorCountVar.set(0)
        self.remainingCountVar.set(0)

        self.grandRunCountVar.set(0)
        self.grandFailCountVar.set(0)
        self.grandErrorCountVar.set(0)
        self.grandRemainingCountVar.set(0)

        self.errorInfo = []
        self.grandErrorInfo = []

        self.progressBar.setProgressFraction(0.0)
        self.grandProgressBar.setProgressFraction(0.0)

        self.runSelButton.config(state=tk.ACTIVE)
        self.runAllButton.config(state=tk.ACTIVE)

        self.errorDescr = []
        self.grandErrorDescr = {}

        self.grandTotalTests = 0

        self.grandErrorListbox.delete(0, tk.END)

    def delAllClicked(self):
        self.tsts = []
        self.fileListbox.delete( 0, tk.END )        
        self.statusVar.set("Idle")

    def delSelClicked(self):
        items = self.fileListbox.curselection()
        if len(items) == 0 : return
        
        while len(items) > 0:
            m = items[0]
            self.fileListbox.delete(m, m)
            self.tsts.pop( string.atoi(m))
            items = self.fileListbox.curselection()

    def quitApp(self):
         self.top.quit()

    def doubleClickedFileListItem(self):
        self.runSelClicked()

    def showLastRunInfo(self):
        items = self.fileListbox.curselection()
        if len(items) == 0: return
        
        self.updateDisplayWithLastRunInfo(  string.atoi( items[0] ))

    def showLastRunInf2(self, event):
        # 38: UP keycode
        # 40: DOWN keycode
        kc = event.keycode        
        if kc not in [38,40]: return
        kc = kc - 39
        
        # the cur selection is not yet moved, that is why we have to calculate the next selected object
        items = self.fileListbox.curselection()
        if len(items) == 0: return
        
        nextsel = string.atoi( items[0])
        nextsel += kc
        if nextsel < 0 or nextsel >= len( self.tsts) : return
        
        self.updateDisplayWithLastRunInfo( nextsel)
        
    def updateDisplayWithLastRunInfo(self, idx):
        if self.grandErrorDescr.has_key( idx ):
            run, fails, errs, rem = self.grandErrorDescr[ idx]
            self.runCountVar.set( run)
            self.failCountVar.set( fails)
            self.errorCountVar.set( errs)
            self.remainingCountVar.set( rem)
            fractionDone = 0.0
            if self.runCountVar.get() + self.remainingCountVar.get() > 0:
                fractionDone = float(self.runCountVar.get()) / float( self.runCountVar.get() + self.remainingCountVar.get())
            fillColor = (self.failCountVar.get() + self.errorCountVar.get() > 0) and "red" or "green"
            self.progressBar.setProgressFraction(fractionDone, fillColor)
        else:
            self.runCountVar.set( 0)
            self.failCountVar.set( 0)
            self.errorCountVar.set( 0)
            self.remainingCountVar.set( 0)
            self.progressBar.setProgressFraction( 0.0)


class Dialog(tk.Toplevel):
    def __init__(self, parent, title = None):

        tk.Toplevel.__init__(self, parent)
        self.transient(parent)

        if title:
            self.title(title)

        self.parent = parent

        self.result = None

        self.buttonbox()

        body = tk.Frame(self, relief=tk.SUNKEN, borderwidth=2)
        self.initial_focus = self.body(body)
        body.pack( padx=10, pady=10, fill=tk.BOTH, expand = 1, anchor=tk.SE)

        self.grab_set()

        if not self.initial_focus:
            self.initial_focus = self

        self.protocol("WM_DELETE_WINDOW", self.cancel)

        self.geometry("+%d+%d" % (parent.winfo_rootx()+50,
                                  parent.winfo_rooty()+50))

        self.initial_focus.focus_set()

        self.wait_window(self)

    #
    # construction hooks

    def body(self, master):
        # create dialog body.  return widget that should have
        # initial focus.  this method should be overridden

        pass

    def buttonbox(self):
        # add standard button box. override if you don't want the
        # standard buttons
        
        box = tk.Frame(self)

        w = tk.Button(box, text="OK", width=10, command=self.ok, default=tk.ACTIVE)
        w.pack(side=tk.LEFT, padx=5, pady=5)
        w = tk.Button(box, text="Cancel", width=10, command=self.cancel)
        w.pack(side=tk.LEFT, padx=5, pady=5)

        self.bind("<Return>", self.ok)
        self.bind("<Escape>", self.cancel)

        box.pack()

    #
    # standard button semantics

    def ok(self, event=None):

        if not self.validate():
            self.initial_focus.focus_set() # put focus back
            return

        self.withdraw()
        self.update_idletasks()

        self.apply()

        self.cancel()

    def cancel(self, event=None):

        # put focus back to the parent window
        self.parent.focus_set()
        self.destroy()

    #
    # command hooks

    def validate(self):

        return 1 # override

    def apply(self):

        pass # override


class MyChildDialog(Dialog):
    def __init__(self, parent, invoker, test, tracebacktext):
        self.invokerObj = invoker
        self.test = test
        self.tracebackText = tracebacktext

        Dialog.__init__(self, parent, title = test)

    def body(self, master):
        tk.Label(master, text=str(self.test),
                 foreground="red", justify=tk.LEFT).pack(padx = 5, pady = 5, anchor=tk.W)
        tk.Label(master, text=self.tracebackText, justify=tk.LEFT).pack(padx = 5, pady = 5, anchor=tk.W)

        #return obj # may return initial focus

    def buttonbox(self):
        # overriden
        
        box = tk.Frame(self)

        w1 = tk.Button(box, text="Prev", width=6, command=self.prev)
        w1.pack(side=tk.LEFT, ipadx = 2, padx=2)
        w2 = tk.Button(box, text="Next", width=6, command=self.next)
        w2.pack(side=tk.LEFT, ipadx = 2, padx=2)
        w3 = tk.Button(box, text="OK", width=8, command=self.ok, default=tk.ACTIVE)
        w3.pack(side=tk.LEFT, ipadx = 2, padx=10)

        self.bind("<Prior>"    , lambda ev, self=self: self.prev())
        self.bind("<Shift-F4>" , lambda ev, self=self: self.prev())
        self.bind("<F4>"       , lambda ev, self=self: self.next())
        self.bind("<Next>"     , lambda ev, self=self: self.next())
        self.bind("<Return>"   , lambda ev, self=self: self.ok())
        self.bind("<Escape>"   , lambda ev, self=self: self.ok())

        box.pack( padx = 10, pady = 5, anchor=tk.NW)

    def apply(self):
        pass

    def next(self):
        self.apply()
        self.ok()
        self.invokerObj.showNextErr()
    def prev(self):
        self.apply()
        self.ok()
        self.invokerObj.showPrevErr()
        
class OptionDialog(tk.Toplevel):
    def __init__(self, parent, title = None):

        tk.Toplevel.__init__(self, parent)
        self.transient(parent)

        if title:
            self.title(title)

        self.parent = parent

        self.result = None

        body = tk.Frame(self)
        self.initial_focus = self.body(body)
        body.pack( padx=10, pady=10)#, fill=tk.BOTH, expand = 1, anchor=tk.SE)
        #body.grid( padx=10, pady=10)

        self.buttonbox()

        self.grab_set()

        if not self.initial_focus:
            self.initial_focus = self

        self.protocol("WM_DELETE_WINDOW", self.cancel)

        self.geometry("+%d+%d" % (parent.winfo_rootx()+50,
                                  parent.winfo_rooty()+50))

        self.initial_focus.focus_set()

        self.wait_window(self)

    #
    # construction hooks

    def body(self, master):
        # create dialog body.  return widget that should have
        # initial focus.  this method should be overridden

        pass

    def buttonbox(self):
        # add standard button box. override if you don't want the
        # standard buttons
        
        box = tk.Frame(self)

        w = tk.Button(box, text="OK", width=10, command=self.ok, default=tk.ACTIVE)
        w.pack(side=tk.LEFT, padx=5, pady=5)
        w = tk.Button(box, text="Cancel", width=10, command=self.cancel)
        w.pack(side=tk.LEFT, padx=5, pady=5)

        self.bind("<Return>", self.ok)
        self.bind("<Escape>", self.cancel)

        box.pack()

    #
    # standard button semantics

    def ok(self, event=None):

        if not self.validate():
            self.initial_focus.focus_set() # put focus back
            return

        self.withdraw()
        self.update_idletasks()

        self.apply()

        self.cancel()

    def cancel(self, event=None):

        # put focus back to the parent window
        self.parent.focus_set()
        self.destroy()

    #
    # command hooks

    def validate(self):

        return 1 # override

    def apply(self):

        pass # override

class MyOptionDialog(OptionDialog):
    def __init__(self, parent, p_invoker, p_options):
        self.invokerObj = p_invoker
        self.optionsObj = p_options

        OptionDialog.__init__(self, parent, title = 'Options')

    def checkButtonChanges(self):
        if self.runMode.get() == 1:
            self.time_range.config(state=tk.NORMAL)
            self.pytonloc.config(state=tk.NORMAL)
            self.brw.config(state=tk.ACTIVE)
        else:
            self.time_range.config(state=tk.DISABLED)
            self.pytonloc.config(state=tk.DISABLED)
            self.brw.config(state=tk.DISABLED)

    def body(self, master):
        
        part = tk.Frame( master)

        self.runMode = tk.IntVar()
        self.runMode.set(self.optionsObj.getGuardedExec() and 1 or 0)
        self.runModeButton = tk.Checkbutton( part, text="Timeout mode", variable=self.runMode, command = lambda self=self: self.checkButtonChanges(), width = 12, anchor = tk.W)
        self.runModeButton.grid( row = 0, sticky=tk.W)

        lab = tk.Label( part, text = 'Timeout value (secs):')
        lab.grid( row = 1, sticky=tk.W)
        
        self.time_range = tk.Entry( part, width = 4)
        self.time_range.grid( row = 1, column = 1, sticky=tk.W)

        la2 = tk.Label( part, text = 'Python.exe location:')
        la2.grid( row = 2, sticky=tk.W)
        self.pytonloc = tk.Entry( part, width = 30)
        self.pytonloc.grid( row = 2, column = 1, sticky=tk.W)
        
        self.brw = tk.Button( part, text="...", command=self.brwClicked)
        self.brw.grid(row=2, column = 2, sticky=tk.W, padx = 2)

        patt = tk.Frame( master)

        la3 = tk.Label( patt, text = 'Filename patterns:')
        la3.grid( pady = 5, row = 3, sticky=tk.W)
        la4 = tk.Label( patt, text = 'Start')
        la4.grid( pady = 5, row = 3, column = 1, sticky=tk.W)
        la5 = tk.Label( patt, text = 'End')
        la5.grid( pady = 5, row = 3, column = 2, sticky=tk.W)
        self.startPattEntry = tk.Entry( patt, width = 6)
        self.startPattEntry.grid( padx = 3, row = 4, column = 1, sticky=tk.W)
        self.endPattEntry   = tk.Entry( patt, width = 6)
        self.endPattEntry.grid( padx = 3, row = 4, column = 2, sticky=tk.W)

        # initial update:
        self.time_range.insert( tk.END, str( self.optionsObj.getTimeOut()) )
        self.pytonloc.insert( tk.END, self.optionsObj.getPythonExeLoc())
        
        self.startPattEntry.insert( tk.END, self.optionsObj.getStartPattern())
        self.endPattEntry.insert( tk.END, self.optionsObj.getEndPattern())

        # move the entry field into the correct state
        self.checkButtonChanges()
        
        part.pack( padx=10, pady=10, expand = 1, anchor=tk.SW)
        patt.pack( padx=10, pady=10, expand = 1, anchor=tk.SW)

        return self.runModeButton # may return initial focus
        
    def brwClicked(self):
        fn = tkFileDialog.askopenfilenames( title = 'Please specify location of python.exe', parent = self)
        if len(fn)>0:
           self.pytonloc.delete(0, tk.END)
           self.pytonloc.insert(tk.END, fn)

    def apply(self):
        self.optionsObj.setGuardedExec( self.runMode.get() == 1)
        self.optionsObj.setTimeOut( self.time_range.get())

        if len( self.pytonloc.get()) > 0:
            if os.path.exists( self.pytonloc.get()):
                self.optionsObj.setPythonExeLoc( self.pytonloc.get())
            else:
                tkMessageBox.showerror(message='Specified path does not exist!')
                self.optionsObj.setPythonExeLoc('python.exe')
        else:
            self.optionsObj.setPythonExeLoc('python.exe')
        
        self.optionsObj.setStartPattern( self.startPattEntry.get())
        self.optionsObj.setEndPattern( self.endPattEntry.get())

class RunningOptions:
     def __init__(self):
         self.guardedExec = gTimeOutMode
         self.timeOut     = gDefTimeOut
         self.pythonExeLoc= gPythonExe
         self.startPatt   = gStartPattern
         self.endPatt     = gEndPattern

     def setGuardedExec(self, val):
         self.guardedExec = val
     def getGuardedExec(self):
         return self.guardedExec
         
     def setTimeOut(self, val):
         self.timeOut = val
     def getTimeOut(self):
         return self.timeOut

     def setPythonExeLoc(self, val):
         self.pythonExeLoc = val
     def getPythonExeLoc(self):
         return self.pythonExeLoc
         
     def getStartPattern(self):
         return self.startPatt
     def setStartPattern(self, val):
         self.startPatt = val
         
     def getEndPattern(self):
         return self.endPatt
     def setEndPattern(self, val):
         self.endPatt = val

class ProgressBar(tk.Frame):
    """A simple progress bar that shows a percentage progress in
    the given colour."""

    def __init__(self, *args, **kwargs):
        apply(tk.Frame.__init__, (self,) + args, kwargs)
        self.canvas = tk.Canvas(self, height='10', width='60',
                                background='white', borderwidth=3)
        self.canvas.pack(fill=tk.X, expand=1)
        self.rect = self.text = None
        self.canvas.bind('<Configure>', self.paint)
        self.setProgressFraction(0.0)

    def setProgressFraction(self, fraction, color='blue'):
        self.fraction = fraction
        self.color = color
        self.paint()
        self.canvas.update_idletasks()
        
    def paint(self, *args):
        totalWidth = self.canvas.winfo_width()
        width = int(self.fraction * float(totalWidth))
        height = self.canvas.winfo_height()
        if self.rect is not None: self.canvas.delete(self.rect)
        if self.text is not None: self.canvas.delete(self.text)
        self.rect = self.canvas.create_rectangle(0, 0, width, height,
                                                 fill=self.color)
        percentString = "%3.0f%%" % (100.0 * self.fraction)
        self.text = self.canvas.create_text(totalWidth/2, height/2,
                                            anchor=tk.CENTER,
                                            text=percentString)

class Manager:
        def __init__(self, optionsObj):
            self.optionsObj = optionsObj
            
        def guardedExecOfTestcase( self, scriptfile_name, directory):
                """Public method
                """

                timeout_val = self.optionsObj.getTimeOut()
                Debugger().log( str(timeout_val))
                try:
                        # create a process running the script file with python
                        process_info = self.createProcess( scriptfile_name, directory )
                except:
                        print "Error occurred in Manager::createProcess."
        
                Debugger().log( "We'll wait for %s seconds to complete." % str(timeout_val))
        
                #time.sleep( timeout_val ) # instead of this, use a more sophisticated sleep
        
                start_time = time.time()
                kill_it  = False
                run_more = True
                while run_more:
                        time.sleep( 1 )
                        proc_exit_code = self.watchProcess( process_info )
                        if time.time() - start_time > float(timeout_val):      # timeout has expired
                                run_more = False
                                kill_it  = True
                        elif 259 != proc_exit_code:    # proc_ended
                                run_more = False
                
                if kill_it:
                        print "Sorry, timeout expired. The testrunner process will be killed: <", scriptfile_name, ">"
                
                        try:
                                self.killProcess( process_info)
                                return 1
                        except:
                                Debugger().log("Error occurred in Manager::killProcess")

        def createProcess( self, the_script, the_directory ):
                """Private method
                """
                script_to_exec  = the_directory + ( the_directory[-1] in ['\\','/'] and ['',] or ['\\',])[0] + the_script + ( the_script.endswith('.py') and ['',] or ['.py',])[0]
                Debugger().log('Script to execute: ' + script_to_exec)
                command_ln = "%s %s" % (self.optionsObj.getPythonExeLoc(), script_to_exec)
                Debugger().log('Command line: ' + command_ln + '\n\n')
        
                si = win32process.STARTUPINFO()
                si.lpTitle = ''
        
                # return value:  process information 4 element tuple
                t = (hProcess, hThread, dwProcessId, dwThreadId) = \
                win32process.CreateProcess( \
                  None
                 ,command_ln
                 ,None          #proc_attr,
                 ,None          #thre_attr,
                 ,False         #inher_handles,
                 ,0             #creation flags
                 ,None          #environment
                 ,the_directory #current directory
                 ,si            #startup info
                )
                
                Debugger().log('\n \t hProcess = %s \n \t hThread = %s \n \t dwProcessId = %s \n \t dwThreadId = %s\n' % ( hProcess, hThread, dwProcessId, dwThreadId ))
                Debugger().log('CreateProcess process handle value: ' + str(hProcess))
                Debugger().log("createProcess,GetExitCodeProcess: " + str(win32process.GetExitCodeProcess( hProcess )))
                
                return t
        
        
        """ Tries to investigate the status of a process. If exit code is 0 then it might have ended
        """
        def watchProcess( self, tup):
                """Private method
                """
                vt = 0
                try:
                 vt = win32process.GetExitCodeProcess( tup[0] )
                 str = ""
                 if vt == 259: str = "No more data is available. It may run yet."
                 elif vt == 0: str = "Might have ended?"
                 #if debug_it: print "watchProcess,GetExitCodeProcess: " , vt, str
                        
                except:
                 Debugger().log("watchProcess, GetExitCodeProcess exception")
                
                return vt
                
        
        def killProcess( self, tup):
                """Private method

                PROCESS_TERMINATE
                SYNCHRONIZE
                HANDLE OpenProcess(  DWORD dwDesiredAccess,  BOOL bInheritHandle,  DWORD dwProcessId);
        
                define SYNCHRONIZE                      (0x00100000L)
                define STANDARD_RIGHTS_REQUIRED         (0x000F0000L)
                
                define PROCESS_TERMINATE         (0x0001)  
                define PROCESS_CREATE_THREAD     (0x0002)  
                define PROCESS_SET_SESSIONID     (0x0004)  
                define PROCESS_VM_OPERATION      (0x0008)  
                define PROCESS_VM_READ           (0x0010)  
                define PROCESS_VM_WRITE          (0x0020)  
                define PROCESS_DUP_HANDLE        (0x0040)  
                define PROCESS_CREATE_PROCESS    (0x0080)  
                define PROCESS_SET_QUOTA         (0x0100)  
                define PROCESS_SET_INFORMATION   (0x0200)  
                define PROCESS_QUERY_INFORMATION (0x0400)  
                define PROCESS_SUSPEND_RESUME    (0x0800)  
                define PROCESS_ALL_ACCESS        (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0xFFF)
                """
        
                vt = 0
                try:
                 vt = win32process.GetExitCodeProcess( tup[0] )
                 str = ""
                 if vt == 259: str = "No more data is available. It may run yet."
                 elif vt == 0: str = "Might have ended?"
                 Debugger().log("killProcess,GetExitCodeProcess: " + vt + str)
                        
                except:
                 Debugger().log("killProcess, GetExitCodeProcess exception")
                
                try:
                 win32process.TerminateProcess( tup[0], 0 )
                 #win32api.CloseHandle( tup[0]) 
                 Debugger().log("TerminateProcess success, It might have ran")
                except:
                 Debugger().log("TerminateProcess has thrown, It might have ended before")
                 e = win32api.GetLastError()
                 str = ""
                 if e == 5: str = "Access is denied, it might have ended?"
                 Debugger().log("GetLastError: " + e + str)
        
        


def main(initialTestName=""):
    root = tk.Tk()
    root.title("GPyUnit")
    runner = TkTestRunner(root, initialTestName)
    root.protocol('WM_DELETE_WINDOW', root.quit)
    root.mainloop()


if __name__ == '__main__':
    import sys
    if len(sys.argv) == 2:
        main(sys.argv[1])
    else:
        main()
