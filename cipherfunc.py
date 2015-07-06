
import CipherMod

def EncryptOne(path, key, signature):
    with open(path, 'rb') as fin:
        return CipherMod.encrypt(fin.read(), key)

def DecryptOne(path, key, signature):
    with open(path, 'rb') as fin:
        return CipherMod.decrypt(fin.read(), key)

def EncryptFile(path, key, signature):
    with open(path + ".out", 'wb') as fout:
        fout.write(EncryptOne(path, key, signature))

def DecryptFile(path, key, signature):
    with open(path + ".de", 'wb') as fout:
        fout.write(DecryptOne(path, key, signature))

if '__main__' == __name__:
    print("This is module only")