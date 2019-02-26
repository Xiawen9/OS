import sys

sys.path.insert(1, './support/scons')

from build import *
from archive import *

#
# Target build
#
build_env = target
Export('build_env')
build_env.Append(CCFLAGS='-m32 -Wno-cpp -Wno-unused-variable -Wno-sign-compare')

# Build programs, libraries and servers.
VariantDir(target['BUILDROOT'] + '/lib', '#lib', duplicate = 0)
VariantDir(target['BUILDROOT'] + '/bin', '#bin', duplicate = 0)
VariantDir(target['BUILDROOT'] + '/server', '#server', duplicate = 0)
VariantDir(target['BUILDROOT'] + '/kernel', '#kernel', duplicate = 0)

# Install files to the target RootFS
target.TargetInstall('VERSION')
target.TargetInstall('build.conf', target['etc'])
target.TargetInstall('build.host.conf', target['etc'])
target.TargetInstall(target['BUILDROOT'] + '/include/Config.h', target['etc'])
target.TargetInstall('config/' + target['ARCH'] + '/' + target['SYSTEM'] + '/init.sh', target['etc'])

SConscript(target['BUILDROOT'] + '/lib/SConscript')
SConscript(target['BUILDROOT'] + '/bin/SConscript')
SConscript(target['BUILDROOT'] + '/server/SConscript')
SConscript(target['BUILDROOT'] + '/kernel/' + target['ARCH'] + '/' + target['SYSTEM'] + '/SConscript')

#
# Host build
#
build_env = host
Export('build_env')

# Build programs and libraries.
VariantDir(host['BUILDROOT'] + '/lib', '#lib', duplicate = 0)
VariantDir(host['BUILDROOT'] + '/bin', '#bin', duplicate = 0)
VariantDir(host['BUILDROOT'] + '/server', '#server', duplicate = 0)
SConscript(host['BUILDROOT'] + '/lib/SConscript')
SConscript(host['BUILDROOT'] + '/bin/SConscript')
SConscript(host['BUILDROOT'] + '/server/SConscript')

#
# Boot Image
#
target.BootImage('#${BUILDROOT}/boot.img.gz', '#config/' + target['ARCH'] + '/' + target['SYSTEM'] + '/boot.imgdesc')

#
# RootFS
#
Import('rootfs_files')
target.LinnImage('#${BUILDROOT}/rootfs.linn', rootfs_files)
target.Depends('#${BUILDROOT}/rootfs.linn', '#build/host')
