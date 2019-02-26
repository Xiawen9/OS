import os
import build

#
# Modifies the dependency list by parsing boot image config.
#
def boot_image_emitter(target, source, env):

    # Open boot configuration.
    f = open(str(source[0]))

    # Loop all lines.
    for line in f.readlines():

	# Skip comments, empty lines and subtrees.
	if len(line.strip()) <= 0 or \
	       line.find('=') != -1 or \
	       line[0] == '{' or \
	       line[0] == '}' or \
	       line[0] == '#':
	    continue

	# Make us depend on the program.
	source.append('#' + env['BUILDROOT'] + '/' + line.strip())

    # We also depend on the mkimage utility.
    source.append('#' + build.host['BUILDROOT'] + '/bin/img/img')

    # All done.
    f.close()
    return target, source

#
# Generate a boot image.
#
def boot_image_func(target, source, env):

    # Invoke the mkimage utility to generate a boot image.
    image_out, ext  = os.path.splitext(str(target[0]))
    d = os.getcwd()

    os.chdir(env['BUILDROOT'])
    os.system("'" + d + "/" + build.host['BUILDROOT'] + "/bin/img/img' '" +
                    d + "/" + str(source[0]) + "' '" +
                    d + "/" + image_out + "'")
    os.system("gzip -c '" + d + "/" + image_out + "' > '" + d + "/" + image_out + ".gz'")
    os.chdir(d)

def boot_image_str(target, source, env):

    return "  IMG  " + str(target[0])

#
# Add ourselves to the given environment.
#
def generate(env):

    builder =  env.Builder(action  = env.Action(boot_image_func, boot_image_str),
			   emitter = boot_image_emitter)
    env.Append(BUILDERS = { 'BootImage' : builder })

#
# We always exist.
#
def exists(env):
    return True
