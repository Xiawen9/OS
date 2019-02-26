from SCons.SConf  import *
from SCons.Script import *

#
# SConf helper function.
#
def TryCompileC(context):

    # Print out a debug message.
    context.Message('Checking for ' + context.env['TRYFLAG'] + ' ... ')

    # Use the simpelest C program possible.
    source_file = "int main(int argc, char **argv)" \
		  "{" \
		  "    return 0;" \
		  "}\n"

    # Try to compile and link it.
    result = context.TryLink(source_file, '.c')

    # Return the result status.
    context.Result(result)
    return result

#
# Checks if the compiler in the given environment supports
# the given command-line CFLAGS, and unsets it if not.
#
# Thanks to loonycyborg on #scons for his help!
#
def CheckCCFlags(env):

    cflags = env['_CCFLAGS'][:]

    # Loop all CFLAGS.
    for flag in cflags:

	# Setup a temporary environment.
        conf = Configure(env.Clone(),
    			 custom_tests = { 'TryCompileC' : TryCompileC })
        conf.env.Replace(CCFLAGS   = flag)
        conf.env.Replace(LINKFLAGS = flag)
        conf.env.Replace(TRYFLAG   = flag)

	# Try to link a dummy program.
	result = conf.TryCompileC()

	# If success, append to CFLAGS
        if result:
	    env['CCFLAGS'].append(flag)

	# Done. Try next.
        conf.Finish()

#
# SConf helper function.
#
def TryCompileCXX(context):

    # Print out a debug message.
    context.Message('Checking for ' + context.env['TRYFLAG'] + ' ... ')

    # Use the simpelest C program possible.
    source_file = "int main(int argc, char **argv)" \
		  "{" \
		  "    return 0;" \
		  "}\n"

    # Try to compile and link it.
    result = context.TryCompile(source_file, '.cpp')

    # Return the result status.
    context.Result(result)
    return result

#
# Checks if the compiler in the given environment supports
# the given command-line CPPFLAGS, and unsets it if not.
#
# Thanks to loonycyborg on #scons for his help!
#
def CheckCXXFlags(env):

    cppflags = env['_CXXFLAGS'][:]

    # Loop all CPPFLAGS.
    for flag in cppflags:

	# Setup a temporary environment.
        conf = Configure(env.Clone(),
    			 custom_tests = { 'TryCompileCXX' : TryCompileCXX })
        conf.env.Replace(CXXFLAGS  = flag)
        conf.env.Replace(LINKFLAGS = flag)
        conf.env.Replace(TRYFLAG   = flag)

	# Try to link a dummy program.
	result = conf.TryCompileCXX()

	# If success, append it to CXXFLAGS
        if result:
	    env['CXXFLAGS'].append(flag)

	# Done. Try next.
        conf.Finish()
