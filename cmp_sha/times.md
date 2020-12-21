# SHA in C vs SHA in Python 3

It is a exercise to compare the execution times of the diferents SHA algorithms.

Both programs (`calculate_sha.c` and `calculate_sha.py`) generate the SHA of a file content.


## SHA1

| File size |  C POC | Python POC |
|:---------:|:------:|:----------:|
|   929 KB  | 0.004s |   0.055s   |
|    9 MB   | 0.015s |   0.069s   |
|   95 MB   | 0.081s |   0.209s   |
|   991 MB  | 0.735s |   1.521s   |
|    2 GB   | 1.506s |   3.660s   |


## SHA224

| File size |  C POC | Python POC |
|:---------:|:------:|:----------:|
|   929 KB  | 0.004s |   0.058s   |
|    9 MB   | 0.014s |   0.070s   |
|   95 MB   | 0.088s |   0.205s   |
|   991 MB  | 0.766s |   1.564s   |
|    2 GB   | 1.600s |   3.145s   |


## SHA256

| File size |  C POC | Python POC |
|:---------:|:------:|:----------:|
|   929 KB  | 0.004s |   0.057s   |
|    9 MB   | 0.019s |   0.071s   |
|   95 MB   | 0.086s |   0.206s   |
|   991 MB  | 0.763s |   1.549s   |
|    2 GB   | 1.566s |   3.066s   |


## SHA384

| File size |  C POC | Python POC |
|:---------:|:------:|:----------:|
|   929 KB  | 0.007s |   0.058s   |
|    9 MB   | 0.030s |   0.087s   |
|   95 MB   | 0.186s |   0.355s   |
|   991 MB  | 1.806s |   3.110s   |
|    2 GB   | 3.877s |   6.195s   |


## SHA512

| File size |  C POC | Python POC |
|:---------:|:------:|:----------:|
|   929 KB  | 0.008s |   0.056s   |
|    9 MB   | 0.030s |   0.084s   |
|   95 MB   | 0.188s |   0.357s   |
|   991 MB  | 1.810s |   3.136s   |
|    2 GB   | 3.698s |   6.138s   |
