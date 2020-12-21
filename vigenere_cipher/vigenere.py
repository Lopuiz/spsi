#
# Task 2: Implement Vigenère cipher
#
# Subject: Security and Protection in Computer Systems
# Degree of computer science
# Author: Eva López Ruiz
#


import argparse


ALPHABET = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
            'Ñ', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']

ALPHABET_SIZE = len(ALPHABET)


def encrypt(key, message):
    """
    Encode message using key
    """
    result = ""
    key_index = 0
    key = key.upper()
    message = message.upper()

    for c in message:
        try:
            alp_index = ALPHABET.index(c)
            alp_index += ALPHABET.index(key[key_index])
            alp_index %= ALPHABET_SIZE
            result += ALPHABET[alp_index]
        except:
            result += c

    result = result.replace(" ", "")

    return result


def decrypt(key, message):
    """
    Decode message using key

    Note the difference with encrypt function is line 57,
    which subtract instead of add.
    """
    result = ""
    key_index = 0
    key = key.upper()
    message = message.upper()

    for c in message:
        try:
            alp_index = ALPHABET.index(c)
            alp_index -= ALPHABET.index(key[key_index])
            alp_index %= ALPHABET_SIZE
            result += ALPHABET[alp_index]
        except:
            result += c

    return result


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Vigenere Cryptosystem',
                                     epilog='Exercise implemented for the SPSI subject')

    parser.add_argument('--action', action='store', type=str, required=True, help='Actions: encrypt or decrypt')
    parser.add_argument('--key', action='store', type=str, required=True, help='Key to encrypt/decrypt')
    parser.add_argument('--message', action='store', type=str, required=True, help='Message to encrypt/decrypt')

    args = parser.parse_args()

    if args.action == 'decrypt':
        result = "Message decrypted is:\n"
        result += decrypt(args.key, args.message)
        print(result)
    elif args.action == 'encrypt':
        result = "Message encrypted is:\n"
        result += encrypt(args.key, args.message)
        print(result)
    else:
        print("Failure to process your request")
