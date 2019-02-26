import os
import binascii

#
# Produces an C symbol from a given binary.
#
def binary_func(target, source, env):

    # Open source and target files.
    fin  = open(str(source[0]), "r")
    fout = open(str(target[0]), "w")

    # Read input file.
    data   = binascii.hexlify(fin.read())
    symbol = os.path.basename(str(source[0]))
    symbol = symbol.replace(".", "_")

    # Output header.
    fout.write("/*\n" +
	       " * This file is auto-generated from " + str(source[0]) + "\n" +
	       " */\n"
	       "\n"
	       "unsigned char __attribute__((aligned(4096))) " +
	                     "__attribute__((__section__(\".binary\"))) " +
	        symbol + "[] = { ")

    # Loop data.
    i = 0
    while i < len(data):
	fout.write("0x" + data[i] + data[i+1])

	if i < len(data) - 2:
	    fout.write(",")
	i += 2

    #for i in range(0, len(data)):
#
#	fout.write(data[i])
#
#	if i < len(data) - 1:
#	    fout.write(",")

    # Output footer.
    fout.write("};\n\n")

    # All done.
    fin.close()
    fin.close()

def binary_str(target, source, env):

    return "  GEN " + str(target[0])

#
# Add ourselves to the given environment.
#
def generate(env):

    builder =  env.Builder(action  = env.Action(binary_func, binary_str))
    env.Append(BUILDERS = { 'Binary' : builder })

#
# We always exist.
#
def exists(env):

    return True
