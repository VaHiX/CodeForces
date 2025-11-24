# Problem: CF 1934 D1 - XOR Break --- Solo Version
# https://codeforces.com/contest/1934/problem/D1

from sys import stdin, stdout

t = int(stdin.readline())

for _ in range(t):
    n, m = [int(x) for x in stdin.readline().split()]

    # If m can be reached directly by XORing n with some y < n such that n^y < n
    if n ^ m < n:
        stdout.write("1\n")
        stdout.write("{} {}\n".format(n, m))

    else:
        # Convert n to binary string without '0b' prefix
        n_b = bin(n)[2:]
        # Find the position of the first '1' bit from left (most significant bit)
        for i in range(1, len(n_b) + 1):
            if i == len(n_b):
                break

            elif n_b[i] == "1":
                break

        # If no '1' bit was found after the first bit (shouldn't happen for valid input)
        if i == len(n_b):
            stdout.write("-1\n")

        else:
            # Compute the maximum value that can be generated using the first i bits
            # This is effectively 2^(len(n_b)-i) - 1 which is the largest number with that many bits
            k = 2 ** (len(n_b) - i) - 1

            # If m is smaller than k, use 2 operations: n -> k -> m
            if m < k:
                stdout.write("2\n")
                stdout.write("{} {} {}\n".format(n, k, m))

            else:
                stdout.write("-1\n")


# https://github.com/VaHiX/CodeForces/