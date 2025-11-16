# Problem: CF 1109 A - Sasha and a Bit of Relax
# https://codeforces.com/contest/1109/problem/A

"""
Problem: Count "funny" pairs (l, r) where the XOR of the left half equals the XOR of the right half,
and the length r - l + 1 is even.

Algorithms/Techniques:
- Prefix XOR with hashmap for efficient lookup
- For each subarray with even length, we split it into two equal halves
- If left half XOR equals right half XOR, then overall XOR of the entire subarray is 0
- We use prefix XOR to efficiently compute XORs of ranges in O(1)
- Hashmap is used to count occurrences of prefix XOR values

Time Complexity: O(n)
Space Complexity: O(n)

This solution uses an optimization with two hashmaps (l0 and l1) to track 
prefix XORs based on the parity of their index, allowing us to count valid
pairs efficiently.
"""

import sys

input = sys.stdin.readline


def tt():
    sys.stdout.flush()


def fg():
    return int(input())


def fgh():
    return [int(xx) for xx in input().split()]


def p(ii):
    ans = 0
    while ii:
        ans += R[j][ii]
        ii -= F[ii]
    return ans


def pl(ii, x):
    while ii <= n:
        R[j][ii] += x
        ii += F[ii]


"""M = 998244353 + 10 ** 9 + 7
M1 = 10 ** 15 + 7
M2 = 655360001
d = [11, 15, 7, 13751, 13757, 13759, 13763, 13781, 29927, 29959, 29983, 29989, 2333, 2339, 2341, 2347, 2351, 9931, 9941, 9949, 9967, 9973]
F = []
for i in range(4 * 10 ** 5 + 3):
    F.append(i & (-i))
L = len(d)
n, q = fgh()
a = fgh()
for i in range(n):
    a[i] = (a[i] * M) % M1
R = [[0] * (n + 1) for i in range(L)]
for j in range(L):
    pr = [0]
    for i in range(n):
        pr.append(pr[-1] + (a[i] * d[j]) % M2)
    for i in range(1, n + 1):
        R[j][i] = pr[i] - pr[i - F[i]]
for _ in range(q):
    t = fgh()
    if t[0] == 2:
        l, r, k = t[1], t[2], t[3]
        l -= 1
        for j in range(L):
            q = p(r) - p(l)
            if q % k:
                print('No')
                break
        else:
            print('Yes')
    else:
        i, x = t[1], t[2]
        x = (x * M) % M1
        i -= 1
        for j in range(L):
            de = (x * d[j]) % M2 - (a[i] * d[j]) % M2
            pl(i + 1, de)
        a[i] = x"""

# Main part of the code implementing the actual solution for "Sasha and a Bit of Relax"

n = fg()  # Read number of elements in array
a = fgh()  # Read the array

# Two hashmaps to store prefix XOR values depending on parity of their index (0 or 1)
l0 = {}  # stores count of prefixes at even indices (0,2,4,...)
l1 = {}  # stores count of prefixes at odd indices (1,3,5,...)

ans = 0  # Result counter

# Compute prefix XOR array
pr = [0]  # Initialize with 0 for prefix sum at index 0
for i in range(n):
    pr.append(pr[-1] ^ a[i])  # XOR the current element into prefix

# Iterate through all prefix values, using parity of index to decide which hashmap to use
for i in range(n + 1):
    if i % 2:  # odd index - check l1 map for matching prefix XOR value
        if pr[i] in l0:
            ans += l0[pr[i]]  # increment result by count of such prefix values
            l0[pr[i]] += 1   # update counter in map
        else:
            l0[pr[i]] = 1    # add new entry to l0 map
    else:  # even index - check l1 map for matching prefix XOR value
        if pr[i] in l1:
            ans += l1[pr[i]]
            l1[pr[i]] += 1
        else:
            l1[pr[i]] = 1

print(ans)  # Output the number of funny pairs


# https://github.com/VaHiX/codeForces/