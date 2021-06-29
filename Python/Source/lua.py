# -*- coding: UTF-8 -*-
"""
2020.03.28
Convert Py Dict to Lua Table
get TableString or Save into File

dictToLuaString(dict)
"""

import io
import sys
import json
import types

def formatLuaString(s):
	s = s.replace('\\', '\\\\')
	s = s.replace('\n', '\\n')
	s = s.replace('\t', '\\t')
	return "'" + s + "'"

def formatLuaBoolean(b):
	if b:
		return 'true'
	else:
		return 'false'

def formatLuaValue(v):
	vtype = type(v)
	if vtype is types.StringTypes or vtype is str or vtype is types.UnicodeType:
		return formatLuaString(v)
	elif vtype is types.BooleanType:
		return formatLuaBoolean(v)
	elif vtype is types.IntType or vtype is types.LongType or vtype is types.FloatType:
		return str(v)
	else:
		print vtype, 'is error'
		return None

def formatDictKey(k):
	if type(k) is types.IntType:
		return '[' + str(k) + ']'
	else:
		return k
		# return '[\"' + formatLuaString(k) + '\"]'

def dictToLuaString(data, head = ''):
	dtype = type(data)
	if dtype is types.ListType:
		s = "{\n"
		for v in data:
			s += head + '\t' + dictToLuaString(v, head + '\t') + ',\n'
		s += head + '}'
		return s

	elif dtype is types.DictType:
		s = "{\n"
		for k, v in data.items():
			s += head + '\t' + formatDictKey(k) +  ' = ' + dictToLuaString(v, head + '\t') + ',\n'
		s += head + '}'
		return s

	else:
		return formatLuaValue(data)

def jsonToLua(jsonfile, luafile):
	f1 = io.open(jsonfile, 'r', encoding = 'utf-8')
	data = json.load(f1)

	luastr = 'return ' + dictToLuaString(data)

	f2 = io.open(luafile, 'w', encoding = 'utf-8')
	f2.write(luastr)
	f2.close()
