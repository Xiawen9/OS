from SCons.Script import *
from checksum import *
import os, os.path
import fnmatch
import tarfile, zipfile
import phony
import build

#
# Recursively find files in path matching include patterns list
# and not matching exclude patterns
#
def Files (path, include = ['*'],  exclude= []):

    files = []
    for filename in os.listdir (path):
        included = False
        excluded = False
        for pattern in include:
            if fnmatch.fnmatch (filename, pattern):
                included = True
                for pattern in exclude:
                    if fnmatch.fnmatch (filename, pattern):
                        excluded = True
                        break
                break
        if included and not excluded:
            fullname = os.path.join (path, filename)
            if os.path.isdir (fullname):
                files.extend (Files (fullname, include, exclude))
            else:
                files.append (fullname)
    return files

#
# Make an archive from sources
#
def Archive (target, source, env):

    print '  TAR %s' % target

    path = os.path.basename (target)
    type = os.path.splitext (path)[-1]

    if type == '.tgz' or type == '.gz':
        archive = tarfile.open (path, 'w:gz')
        path    = path.split('.tar')[0]
    elif type == '.bz2':
        archive = tarfile.open (path, 'w:bz2')
        path    = path.split('.tar')[0]
    elif type == '.zip':
        archive = zipfile.ZipFile (path, 'w')
        archive.add = archive.write
        path    = path.split('.zip')[0]
    else:
        print "Unknown archive type (%s)" % type
        return

    src = [str(s) for s in source if str(s) != path]
    for s in src:
        archive.add (s, os.path.join (path, s))
    archive.close()

#
# Make a OS source distribution in tar.gz and tar.bz2 format.
#
def ReleaseAction(target, source, env):

    inc_list = ['*']
    exl_list = ['*~', '.*', '*.o', '*.pyc', '*.tar.gz',
		'*.tar.bz2', '*.zip', 'build']

    Archive ('OS-' + build.target['VERSION'] + '.tar.gz',
	      Files ('.', include = inc_list, exclude = exl_list), env)
    Archive ('OS-' + build.target['VERSION'] + '.tar.bz2',
	      Files ('.', include = inc_list, exclude = exl_list), env)
    Checksum('OS-' + build.target['VERSION'] + '.tar.gz.md5',
	     'OS-' + build.target['VERSION'] + '.tar.gz', env)
    Checksum('OS-' + build.target['VERSION'] + '.tar.gz.sha1',
	     'OS-' + build.target['VERSION'] + '.tar.gz', env)
    Checksum('OS-' + build.target['VERSION'] + '.tar.bz2.md5',
	     'OS-' + build.target['VERSION'] + '.tar.bz2', env)
    Checksum('OS-' + build.target['VERSION'] + '.tar.bz2.sha1',
	     'OS-' + build.target['VERSION'] + '.tar.bz2', env)

#phony.Targets(release = SCons.Action.Action(ReleaseAction, None))

