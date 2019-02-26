import hashlib
import os

#
# Calculate an MD5 or SHA1 checksum for a given file.
#
def Checksum(target, source, env):

    # Read source contents
    content = open(source).read()
    sum     = None

    # Retrieve extension.
    file, ext = os.path.splitext(target)

    # Process checksum request.
    if   ext == ".md5":
	print "  MD5 %s" % target
	sum = hashlib.md5(content).hexdigest()

    elif ext == ".sha1":
	print "  SHA %s" % target
	sum = hashlib.sha1(content).hexdigest()

    # Write to output file.
    out = open(target, "w")
    out.write(sum + "  " + source + "\n")
    out.close()

