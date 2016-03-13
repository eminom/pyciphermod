
import sys
import os
from PyXxhashMod import xxhash

if '__main__' == __name__:
	if len(sys.argv) < 3:
		print("Need more parameter <path key>")
		sys.exit(-1)
	path, key = sys.argv[1], sys.argv[2]
	with open(path, 'rb') as fin:
		org = fin.read()
		hashed = xxhash(org, int(key))
	#print(type(hashed))
	print(hashed)
