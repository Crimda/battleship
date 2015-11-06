#!/usr/bin/env python
# encoding: utf-8
files = [
	"src/gm.cpp",
	"src/gm.h",
	"src/main.cpp",
	"src/map.cpp",
	"src/map.h",
	"src/ship.cpp",
	"src/ship.h",
	"src/types.cpp",
	"src/types.h",
	"src/ui.cpp",
	"src/ui.h",
	"src/util.cpp",
	"src/util.h",
	"lineCount.py"
]

lineCount = 0

for fname in files:
	fp = open(fname, "r")
	count = len(fp.readlines())
	print("%s: %d" %(fname, count))
	lineCount += count
	fp.close()

print("")
print("Total line count (estimated): %d" %(lineCount))
