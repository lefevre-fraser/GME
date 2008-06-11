VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "ReferenceInterpreter"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
Option Explicit
Public InteractiveMode As Boolean
Public ComponentName As String
Public ComponentType As Long
Public Paradigm As String
Public ComponentProgID As String
Public Version As Long
Public Icon As String

Dim CP As New Collection

Private Sub Class_Initialize()
    ComponentName = "Reference Interpreter (VB)"
    ComponentType = MgaLib.COMPONENTTYPE_INTERPRETER
    Paradigm = "MetaGME"
    ComponentProgID = "MGAVBInterpreter.ReferenceInterpreter"
    Version = GmeLib.MgaInterfaceVersion_Current
    Icon = "" ' set to path for icon if desired
End Sub

' Utility function: returns path to the base GME installation folder
Private Function GMEPath() As String
    Dim WshShell As New IWshShell_Class
    Dim Path As String
    Path = WshShell.RegRead("HKLM\Software\Microsoft\Windows\CurrentVersion\App Paths\GME.exe\Path")
    GMEPath = Mid(Path, 1, Len(Path) - 4)
End Function

Public Function GetComponentParameter(ByVal paramname As String) As Variant
    Dim retval As Variant
    GetComponentParameter = retval
    On Error Resume Next
    GetComponentParameter = CP(paramname)
End Function

Public Sub SetComponentParameter(ByVal paramname As String, ByVal newVal As Variant)
    On Error Resume Next
    CP.Remove paramname
    CP.Add newVal, paramname
End Sub

Public Sub ObjectsInvokeEx(ByVal Project As MgaProject, ByVal currentobj As MgaFCO, ByVal selectedobjs As MgaFCOs, ByVal param As Long)
    ' This method is currently not used by GME
End Sub

Public Sub InvokeEx(Project As IMgaProject, currentobj As IMgaFCO, selectedobjs As IMgaFCOs, param As Long)
    Dim territory As IMgaTerritory
    Project.CreateTerritory Nothing, territory
    Project.BeginTransaction territory
    
    ' Component work goes here
    
    'Example:
    'Dim msg As String
    'msg = "Reference Interpreter (VB):InvokeEx" & vbCr
    'msg = msg & "  project: " & Project.Name & vbCr
    'If Not (currentobj Is Nothing) Then
    '    msg = msg & "  currentobj: " & currentobj.Name & vbCr
    'Else
    '    msg = msg & "  currentobj: Nothing" & vbCr
    'End If
    'If Not (selectedobjs Is Nothing) Then
    '    msg = msg & "  selectedobjs.Count: " & selectedobjs.Count & vbCr
    'Else
    '    msg = msg & "  selectedobjs: Nothing" & vbCr
    'End If
    'msg = msg & "  param: " & param
    'MsgBox msg
    
    Project.CommitTransaction
End Sub

Public Sub Enable(ByVal newVal As Boolean)
End Sub

Public Sub Initialize(ByVal Project As MgaProject)
End Sub

Public Sub Invoke(ByVal Project As MgaProject, ByVal selectedobjs As MgaFCOs, ByVal param As Long)
    ' This method is deprecated. Normally, GME never calls this
End Sub

