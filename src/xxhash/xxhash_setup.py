from distutils.core import setup, Extension

def genModule():
	from platform import system
	extra_ca = ["/EHsc"]  #Originated for MSVC++
	if 'Windows' != system():
		extra_ca = []
	module1 = Extension('PyXxhashMod',
		sources = ['py3xxhashmod.cc',
                     'xxhash.c'
                     ],
              #include_dirs= ["C:/Boost/include/boost-1_57"],
              #      define_macros = [("WIN32",None),
              #      			("WPCAP",None),
              #      			("HAVE_REMOTE",None)],
              #library_dirs = ["F:/Develop/WpdPack4.1.2/Lib/x64"],
              #libraries = ["wpcap","ws2_32","iphlpapi"],
              extra_compile_args = extra_ca
	)              
	return module1

setup (name = 'PyXxhashMod:Faster binary stream hash(python wrapper for xxhash)',
       version = '1.0',
       description = "You may be gone, but you're never over",
       author = 'Eminem',
       author_email = 'hai.bai.cn@gmail.com',
       ext_modules = [genModule()])
