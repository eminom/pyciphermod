
import sys
from cipherfunc import *

if '__main__' == __name__:
    if len(sys.argv) < 4:
        print("Need more parameter <path key signature>")
        sys.exit(-1)
    path, key, sig = sys.argv[1], sys.argv[2], sys.argv[3]
    #print("Decrypting %s with (%s,%s)" % (path, key, sig))
    DecryptFileInplace(path, key, sig)
    print("decryption done.")