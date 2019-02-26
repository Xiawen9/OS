from SCons.Script import *
import subprocess
import multiprocessing
import shlex
import sys
import os
import os.path

def timeoutChecker(proc, timeout):
    time.sleep(timeout)
    print "Timeout occured (" + str(timeout) + " sec) -- aborting"
    proc.terminate()
    sys.exit(1)

def writeTap(testname, data, env):
    """
    Write TAP test output
    """
    outfile = env['BUILDROOT'] + '/tap/' + testname + '.tap'

    try:
        os.makedirs(os.path.dirname(outfile))
    except Exception as e:
        pass

    f = open(outfile, 'w')
    f.write(data)
    f.close()

def runTester(target, source, env):
    """
    Run the OS autotester and collect TAP results.
    """

    # Needed to workaround SCons problem with the pickle module.
    # See: http://stackoverflow.com/questions/24453387/scons-attributeerror-builtin-function-or-method-object-has-no-attribute-disp
    import imp

    del sys.modules['pickle']
    del sys.modules['cPickle']

    sys.modules['pickle'] = imp.load_module('pickle', *imp.find_module('pickle'))
    sys.modules['cPickle'] = imp.load_module('cPickle', *imp.find_module('cPickle'))

    import pickle
    import cPickle

    # Launch process
    proc = subprocess.Popen(shlex.split(env['TESTCMD']), stdout=subprocess.PIPE, stdin=subprocess.PIPE)

    # Launch a timeout process which will send a SIGTERM
    # to the process after a certain amount of time
    ch = multiprocessing.Process(target = timeoutChecker, args=(proc, 60 * 3))
    ch.start()

    # Give input to the OS /bin/login and start the autotester.
    proc.stdin.write("root\n/test/run /test --tap\n")

    # Buffer TAP output
    tap=""

    while True:
        line = proc.stdout.readline()
        if line == '':
            break

        line = line.strip()

        print line

        if line.startswith('# Finish') and line.endswith('/test/run'):
            proc.terminate()
            ch.terminate()
            return

        elif "# Start" in line:
            tap=line + "\n"

        elif line.startswith("# Finish"):
            writeTap(line[9:], tap, env)
            tap=""
        else:
            tap += line + "\n"

    print "Unexpected end of test output"
    proc.terminate()
    ch.terminate()
    sys.exit(1)

#
# Run the OS autotester inside qemu
#
def AutoTester(env, **kw):

    # Generate an environment, if not given.
    if not env:
        env = DefaultEnvironment()

    # Make sure to pass the whole environment to the command.
    env.Append(ENV = os.environ)

    # Register SCons builder which always needs to run
    for target,action in kw.items():
        env.Append(TESTCMD = action)
        env.AlwaysBuild(env.Alias(target, [], runTester))

#
# Add ourselves to the given environment.
#
def generate(env):
    env.AddMethod(AutoTester)

#
# We always exist.
#
def exists(env):
    return True
