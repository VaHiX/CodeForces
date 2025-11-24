# Problem: CF 1725 D - Deducing Sortability
# https://codeforces.com/contest/1725/problem/D

"""
Code Purpose:
This code solves the problem of finding a sortable array A of length N with minimum sum and lexicographically smallest representation. 
It uses a specific construction method to build the array efficiently and answers queries about individual elements.

Algorithms/Techniques:
- Greedy construction of array A based on binary representation and bit manipulation
- Efficient lookup using bit operations and precomputed sizes
- Fenwick tree-like structure for efficient element queries

Time Complexity: O(N) for construction + O(Q * log N) for queries
Space Complexity: O(N) for storing array structure
"""

import sys


def print(*args, sep=" ", end="\n"):
    string = sep.join(map(str, args)) + end
    sys.stdout.write(string)


def debug(*args, sep=" ", end="\n"):
    string = "Debug: " + sep.join(map(str, args)) + end
    sys.stderr.write(string)




N, Q = map(int, input().split())
somme = 0
act = 1
i = 0
j = 1

sizes = []
while i < N:
    if i + j <= N:
        i += j
        somme += act * j
        sizes.append(j)
    else:
        break
    act += 1
    if i + j <= N:
        i += j
        somme += act * j
        sizes.append(j)
    else:
        break
    act += 1
    j += 1
sizes = sizes[::-1]  # Reverse the list to get correct order
k = len(sizes)
sizes.append(0)
for _ in range(N - i):  # Fill remaining positions
    sizes[k] += 1
    k -= 2
somme += (N - i) * act
print(somme)


def lsb(x):
    # Return the value of the least significant bit of x
    return x & (-x)


def root(x):
    # Compute root of x using bit operations
    l = lsb(x)
    return x // l + l.bit_length() - 1


def pos(k):
    # Determine position within a segment using bit manipulation
    l = lsb(k)
    x = (k // l) >> 1
    y = l.bit_length() - 1
    return x, y


shift = 0
offset = 0
for _ in range(Q):
    q = int(input())
    while True:

        k = q - offset

        gi1 = 2 * sizes[shift] - 1
        if k <= gi1:

            x, y = pos(k)
            y += shift
            y += 2 * x
            print(y + 1)
            break
        else:

            shift += 1
            offset += (gi1 + 1) // 2


# https://github.com/VaHiX/CodeForces/