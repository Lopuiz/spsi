#
# Task 1: e(a,b) = a**b
#
# e(a,b) = e(a^2, b/2) if b is odd
#        = e(a^2, (b-1)/2) if b is even
#        = 1 if b is 0
#
# Subject: Security and Protection in Computer Systems
# Degree of computer science
# Author: Eva López Ruiz
#


import argparse
from math import pow


def e(a, b):
    """
    e(a,b) = a**b
    """

    # Check b is positive
    if b < 0:
        return None

    # Calculate the result
    if b == 0:
        return 1
    elif b % 2 == 0:
        return pow(a**2, (b/2))
    else:
        return pow(a**2, (b-1)/2)*a


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='e(a,b) = a**b',
                                     epilog='Exercise implemented for the SPSI subject')

    parser.add_argument('--a', action='store', type=float, required=True, help='The element a of the function')
    parser.add_argument('--b', action='store', type=float, required=True, help='The element b of the function')

    args = parser.parse_args()

    result = e(args.a, args.b)
    if result != None:
        print("The result is: {0}\n".format(result))
    else:
        print("Bad arguments. They must be numbers, and b must be possitive")
