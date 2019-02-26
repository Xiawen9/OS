from SCons.Script import *
import os

#
# Always execute the given commands as SCons targets.
#
# @author GregNoel
# @see http://www.scons.org/wiki/PhonyTargets
#
def Targets(env, **kw):

    # Generate an environment, if not given.
    if not env: env = DefaultEnvironment()

    # Make sure to pass the whole environment to the command.
    env.Append(ENV = os.environ)

    # Execute all targets
    for target,action in kw.items():
        env.AlwaysBuild(env.Alias(target, [], action))

#
# Add ourselves to the given environment.
#
def generate(env):
    env.AddMethod(Targets)

#
# We always exist.
#
def exists(env):
    return True
