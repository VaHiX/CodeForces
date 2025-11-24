# Problem: CF 2167 D - Yet Another Array Problem
# https://codeforces.com/contest/2167/problem/D

"""
Algorithm/Technique:
- The problem asks to find the smallest integer x (2 <= x <= 10^18) such that for at least one element in the array,
  gcd(a[i], x) = 1. This means x and a[i] are coprime.
- Key Insight:
  - If the GCD of all elements in the array is 1, then all numbers are coprime to each other.
    So, we can simply pick the smallest prime number (which is 2) as x, because gcd(2, 1) = 1.
  - If the overall GCD of all elements is greater than 1, say g, then any number that shares a factor with g
    will not be coprime with any element of the array. Therefore, we must find the smallest x > 1 such that
    gcd(x, g) = 1.
- Time Complexity: O(n * log(max(a))) for computing GCD of all elements, and then O(p) for checking coprime,
  where p is the smallest prime such that gcd(x, g) == 1. Worst case is O(10^18), but in practice it's fast.
- Space Complexity: O(1), only using a few variables.
"""

import sys
from math import gcd

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    arr = list(map(int, input().split()))
    g = arr[0]
    for a in arr[1:]:
        g = gcd(g, a)
    if g == 1:
        print(2)
        continue

    x = 2
    while gcd(x, g) != 1:  # Find smallest x > 1 coprime with g
        x += 1
    print(x)


# https://github.com/VaHiX/CodeForces/