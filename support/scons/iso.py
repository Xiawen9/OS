import os
import tempfile
import shutil

#
# Generate a bootable ISO image.
#
def iso_func(target, source, env):

    # Create a temporary directory.
    temp = tempfile.mkdtemp()

    # Temporary workaround for intel/pc. Place grub.cfg in /boot/grub.
    os.makedirs(temp + '/boot/grub')

    # Copy required files to temp directory.
    for s in source:
        shutil.copy(str(s), temp + '/boot')

    # Generate the ISO.
    if env.Detect('grub-mkrescue'):
        shutil.copy('config/intel/pc/grub.cfg', temp + '/boot/grub')
        os.system('grub-mkrescue -d /usr/lib/grub/i386-pc -o ' + str(target[0]) +
                  ' --modules="multiboot iso9660 biosdisk gzio" ' + temp)

    # Fallback without grub2.
    elif env.Detect('mkisofs'):
        shutil.copy('config/intel/pc/menu.lst', temp + '/boot/grub')
        shutil.copy('kernel/intel/pc/stage2_eltorito', temp)
        os.system('mkisofs -quiet -R -b stage2_eltorito -no-emul-boot ' +
                  '-boot-load-size 4 -boot-info-table -o ' + str(target[0]) +
                  ' -V "OS ' + env['VERSION'] + '" ' + temp);
    else:
        raise Exception("no ISO generation program found. Install grub-mkrescue or mkisofs")

    # Clean up temporary directory.
    shutil.rmtree(temp);

#
# String command representation for ISO builder.
#
def iso_str(target, source, env):

    return "  ISO  " + str(target[0])

#
# Add ourselves to the given environment.
#
def generate(env):

    builder = env.Builder(action  = env.Action(iso_func, iso_str))
    env.Append(BUILDERS = { 'ISO' : builder })

#
# We always exist.
#
def exists(env):
    return Env.Detect('grub-mkrescue')
