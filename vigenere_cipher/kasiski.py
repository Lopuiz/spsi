#
# Task 3: Implement a program to attack the Vigenère cipher. Kasiski examination
#
# Subject: Security and Protection in Computer Systems
# Degree of computer science
# Author: Eva López Ruiz
#

import argparse

def obtain_duplicates(message):
    """
    Search duplicated sequences in the message.

    Return dictionary which contains substring as key and a list of distances as value.
    """
    size_msg = len(message)
    result = dict()

    i = 0
    while i < size_msg-3:
        j = i+2
        while j < size_msg:
            k = 3
            is_equal = False

            while i+k <= j and j+k <= size_msg:
                if message[i:i+k] == message[j:j+k]:
                    is_equal = True
                    k+=1
                else:
                    break

            if is_equal:
                k-=1
                subsecuence = message[i:i+k]
                if subsecuence in result.keys():
                    result[subsecuence].append(j-i)
                else:
                    result[subsecuence] = [j-i]
                i+=k

            j+=1
        i+=1

    return result


def mcd(number_list):
    """
    Get the MCD from a list of numbers
    """
    if number_list == []:
        return None

    min_value = min(number_list)

    r = min_value
    while 1<= r:
        obtained = True

        for n in number_list:
            if n%r != 0: obtained = False

        if obtained:
            return r

        r-=1


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="""Search the key size of a message encrypted using Vigenere cipher.
                                                    The method to use is the Kasiski Algorithm.""",
                                     epilog='Exercise implemented for the SPSI subject')

    parser.add_argument('--message', action='store', type=str, required=True, help='Message to decrypt')
    args = parser.parse_args()

    seqs_duplicated = obtain_duplicates(args.message.upper())
    print("The sequences duplicated are: {0}".format(seqs_duplicated))

    number_list = []
    for i in seqs_duplicated:
        for j in seqs_duplicated[i]:
            number_list.append(j)

    value = mcd(number_list)
    print("Key size:{}".format(value))
