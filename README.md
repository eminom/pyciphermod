#! /usr/local/bin/ruby

cur_path = File.dirname(__FILE__.encode("UTF-8"))
cur_path = File.absolute_path(cur_path)

def run_dir(start_path)
	exec = "/Users/eminom/test/python/pyciphermod/encrypt.py"   #This is where you put this.
	key = "some-key-as-you-know"
	sig = "some-special-string-very-special"

	Dir.glob("#{start_path}/**/*.lua") do |file|
		if not system("python3 #{exec} #{file} #{key} #{sig}") then
			puts $?
			exit
		end
	end
end

run_dir("#{cur_path}/../src")
puts "ecryption done."

# The encryption is done with inplace style. 
