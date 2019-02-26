import os
import os.path
from SCons.Action import *

def linnfs_generate(target, source, env):
    """
    Generate an LinnFS filesystem image.
    """
    rootfs_path = env.Dir(env['ROOTFS']).srcnode().path

    os.system("build/host/server/filesystem/linn/create '" + str(target[0]) + "' -s -n 16384 -d '" + rootfs_path + "'")

#
# Prints out a user friendly command-line string.
#
def linnfs_string(target, source, env):
    return "  LINN " + str(target[0])

#
# Add ourselves to the given environment.
#
def generate(env):
    builder = env.Builder(action = env.Action(linnfs_generate, linnfs_string))
    env.Append(BUILDERS = { 'LinnImage' : builder })

#
# We always exist.
#
def exists(env):
    return True
