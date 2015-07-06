
import sys
from cipherfunc import *

if '__main__' == __name__:
    if len(sys.argv) < 4:
        print("Need more parameter")
        sys.exit(-1)
    print("Decrypting %s with (%s,%s)" % (sys.argv[1], sys.argv[2], sys.argv[3]))
    DecryptFile(sys.argv[1], sys.argv[2], sys.argv[3])
    print("done")