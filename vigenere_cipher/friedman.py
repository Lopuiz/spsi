#
# Task 3: Implement a program to attack the Vigenère cipher. Friedman test
#
# Subject: Security and Protection in Computer Systems
# Degree of computer science
# Author: Eva López Ruiz
#


import argparse


ALPHABET = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
            'Ñ', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']

KAPPA_P = 0.0744
KAPPA_R = 0.037037
KAPPA_P_ENG = 0.0685
KAPPA_R_ENG = 0.0385


def ic(message):
    """
    Calculate the index of coincidence
    """
    num_chars = len(message)
    num_diff_chars = 0
    alp_counter = dict()
    result = 0

    for i in ALPHABET:
        if i in message: num_diff_chars += 1
        alp_counter[i] = message.count(i)

    for i in alp_counter:
        fi = alp_counter.get(i)
        result += (fi*(fi-1))/(num_chars*(num_chars-1))
    
    return result


def key_size(coincidence):
    """
    Obtain the key size of a message encrypted using its index of coincidence.
    """
    return (KAPPA_P - KAPPA_R) / (coincidence - KAPPA_R)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="""Search the key size of a message encrypted using Vigenere cipher.
                                                    The method to use is the Friedman test.""",
                                     epilog='Exercise implemented for the SPSI subject')

    parser.add_argument('--message', action='store', type=str, required=True, help='Message to encrypt/decrypt')
    args = parser.parse_args()

    message = args.message.upper()
    coincidence = ic(message)
    sizek = key_size(coincidence)

    print("\nThe index of coincidence is {}".format(coincidence))
    print("The size of the key is a number close to {}".format(sizek))
