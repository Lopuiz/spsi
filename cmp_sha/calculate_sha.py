#
# Obtain SHA of a content file
#


import hashlib
import argparse

BLOCK_SIZE = 2048


def create_object_sha(type_sha):
    """
    Create the required SHA object
    """
    if type_sha == "sha1":
        return hashlib.sha1()
    elif type_sha == "sha224":
        return hashlib.sha224()
    elif type_sha == "sha256":
        return hashlib.sha256()
    elif type_sha == "sha384":
        return hashlib.sha384()
    elif type_sha == "sha512":
        return hashlib.sha512()
    else:
        return None


def sha(path, sha_obj):
    """
    Obtains the sha of the content of a file
    """
    result = None

    with open(path, "rb") as f:

        buffer = f.read(BLOCK_SIZE)
        while(buffer):
            sha_obj.update(buffer)
            buffer = f.read(BLOCK_SIZE)

        result = sha_obj.hexdigest()

    return result


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Calculate the SHA of the content of a file',
                                     epilog='Exercise implemented for the SPSI subject')

    parser.add_argument('--file', action='store', type=str, required=True, help='File to generate SHA')
    parser.add_argument('--algorithm', action='store', type=str, required=True, help='SHA algorithm')

    args = parser.parse_args()

    sha_obj = create_object_sha(args.algorithm)
    if sha_obj == None:
        print("Invalid SHA value")

    result = sha(args.file, sha_obj)
    if result:
        print("SHA: {0}\n".format(result))
    else:
        print("Unable to calculate SHA")
