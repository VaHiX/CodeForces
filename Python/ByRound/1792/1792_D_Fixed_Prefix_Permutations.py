# Problem: CF 1792 D - Fixed Prefix Permutations
# https://codeforces.com/contest/1792/problem/D

"""
Code Purpose:
This code solves the problem of finding the maximum "beauty" of permutations resulting from multiplying each permutation 
in a set with every other permutation in the set. Beauty is defined as the largest k such that the first k elements of the 
resulting permutation match the sequence 1, 2, ..., k.

The approach involves:
1. Converting each permutation into its inverse (to efficiently compute the product).
2. Using a hashing technique to store and check for unique permutation patterns.
3. For each permutation, compute a hash value to determine the maximum beauty by checking how many initial elements align with the pattern 1,2,...,k.

Algorithms/Techniques:
- Permutation inverse computation
- Hashing to store unique permutation patterns
- Brute-force check for maximum beauty

Time Complexity: O(n * m^2)
Space Complexity: O(n * m)
"""

import sys

input = sys.stdin.readline


def fg():
    return int(input())


def fgh():
    return [int(xx) for xx in input().split()]


def yes():
    print("YES")


def no():
    print("NO")


M = 10**18
for _ in range(fg()):
    n, m = fgh()

    a = [fgh() for i in range(n)]

    b = []

    used = dict()

    # Preprocessing: compute inverse permutations and hash them
    for i in range(n):
        pp = [0] * m

        # Compute inverse permutation: pp[a[i][j] - 1] = j + 1
        for j in range(m):
            pp[a[i][j] - 1] = j + 1

        b.append(pp)

        h = 0
        # Hash the inverse permutation to detect uniqueness
        for j in range(m):
            h += b[i][j] * (m**j)
            h %= M
            used[h] = True

    ans = [0] * n
    # For each permutation, compute its hash and determine maximum beauty
    for i in range(n):
        h = 0
        # Hash the original permutation
        for j in range(m):
            h += a[i][j] * (m**j)
            h %= M

            # If current hash is not in used set, update beauty
            if not used.get(h, False):
                ans[i] = j
                break
        else:
            # All elements matched, so beauty is m
            ans[i] = m
    print(*ans)


# https://github.com/VaHiX/CodeForces/