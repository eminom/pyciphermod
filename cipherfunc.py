
import CipherMod

def EncryptOne(path, key, signature):
    with open(path, 'rb') as fin:
        org = fin.read()
        if org[:len(signature)] == signature:
            return org
        return signature + CipherMod.encrypt(org, key)

def DecryptOne(path, key, signature):
    with open(path, 'rb') as fin:
        org = fin.read()
        lsz = len(signature)
        if org[:lsz] != signature:
            return org
        return CipherMod.decrypt(org[lsz:], key)

"""
def EncryptFile(path, key, signature):
    key = bytes(key, 'utf8')
    signature = bytes(signature, 'utf8')
    with open(path + ".out", 'wb') as fout:
        fout.write(EncryptOne(path, key, signature))

def DecryptFile(path, key, signature):
    key = bytes(key, 'utf8')
    signature = bytes(signature, 'utf8')
    with open(path + ".de", 'wb') as fout:
        fout.write(DecryptOne(path, key, signature))
"""

def EncryptFileInplace(path, key, signature):
    #key = bytes(key, 'utf8')
    signature = bytes(signature, 'utf8')
    bin = EncryptOne(path, key, signature)
    with open(path, 'wb') as fout:
        fout.write(bin)

def DecryptFileInplace(path, key, signature):
    #key = bytes(key, 'utf8')
    signature = bytes(signature, 'utf8')
    bin = DecryptOne(path, key, signature)
    with open(path, 'wb') as fout:
        fout.write(bin)

if '__main__' == __name__:
    print("This is module only")