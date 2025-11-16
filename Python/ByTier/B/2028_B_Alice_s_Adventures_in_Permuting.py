# Problem: CF 2028 B - Alice's Adventures in Permuting
# https://codeforces.com/contest/2028/problem/B

# B. Alice's Adventures in Permuting
# Purpose: Given an array defined by a[i] = b * (i - 1) + c, determine the minimum number of operations
# to transform it into a permutation of [0, ..., n-1]. Each operation replaces the leftmost maximum element
# with the MEX (minimum excludant) of the array.
# Algorithms/Techniques: Mathematical analysis and simulation logic based on properties of arithmetic sequences
# Time Complexity: O(1) per test case
# Space Complexity: O(1)

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, a, b = map(int, input().split())
    # If a is 0 and b is less than n-2, it's impossible to form a permutation
    if a == 0 and b < n - 2:
        print(-1)
        continue
    # If a is 0, check how many steps are needed to reduce b to make all values unique
    if a == 0:
        if b < n:
            print(n - 1)
        else:
            print(n)
        continue
    # General case: compute based on formula derived from arithmetic progression properties
    print(n - max(0, (n - 1 - b) // a + 1))


# https://github.com/VaHiX/codeForces/