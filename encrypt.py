
import sys
from cipherfunc import *

if '__main__' == __name__:
    if len(sys.argv) < 4:
        print("Need more")
        sys.exit()
    print("Encrypting %s >>>" % (sys.argv[1]))
    EncryptFile(sys.argv[1], sys.argv[2], sys.argv[3])
    print("done")
