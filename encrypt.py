
import sys
from cipherfunc import *

if '__main__' == __name__:
    if len(sys.argv) < 4:
        print("Need more <path key signature>")
        sys.exit()
    path, key, sig = sys.argv[1], sys.argv[2], sys.argv[3]
    #print("Encrypting %s with (%s, %s) >>>" % (path, key, sig))
    EncryptFileInplace(path, key, sig)
    print("done")
