#!/usr/bin/env python

import sys
import os
import os.path

def xmlTidy(filePath):
	f = open(filePath, 'r')
	l = f.readline()
	lNo = 1;
	while (l):
		cNo = 1
		for c in l:
			if ord(c) > 127:
				print ">>>", filePath
				print "    Invalid character at line %d, column %d: %c" % (lNo, cNo, c)
			cNo = cNo + 1
		l = f.readline()
		lNo = lNo + 1
			
def visitFolder(arg, dirName, fileNames):
	for fileName in fileNames:
		fileExt = os.path.splitext(fileName)[1] 
		if (fileExt in (".xml", ".xme")):
			filePath = os.path.join(dirName, fileName)
			xmlTidy(filePath)
	
rootFolder = os.getcwd()
rootFile = None
if len(sys.argv) == 2:
	if os.path.isfile(sys.argv[1]):
		rootFile = sys.argv[1]
	else:
		rootFolder = sys.argv[1]

if rootFile is not None:
	print "Processing file:", rootFile
	xmlTidy(rootFile)
else:
	print "Processing folder:", rootFolder
	os.path.walk(rootFolder, visitFolder, None)
	
