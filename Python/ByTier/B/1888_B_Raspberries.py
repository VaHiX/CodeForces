# Problem: CF 1888 B - Raspberries
# https://codeforces.com/contest/1888/problem/B

"""
Purpose: 
This code solves the problem of making the product of array elements divisible by a given number k with minimum operations.
Each operation allows incrementing any element by 1. 
The approach uses modular arithmetic to determine the minimal increments needed.

Algorithms/Techniques:
- Modular arithmetic to analyze remainders when dividing by k
- Greedy logic to minimize operations:
  - If any element is already divisible by k, no operations needed
  - For k=4, special cases for even numbers and pairs
  - For other k, find the smallest remainder to make product divisible

Time Complexity: O(n) per test case, where n is array size
Space Complexity: O(k) for storing frequency of remainders
"""

import sys

input = sys.stdin.readline


def readList():
    return list(map(int, input().split()))


def readInt():
    return int(input())


def readInts():
    return map(int, input().split())


def readStr():
    return input().strip()


def solve():
    n, k = readInts()
    arr = readList()
    freq = [0] * k
    for v in arr:
        freq[v % k] += 1
    if freq[0]:  # If any element is divisible by k
        return 0
    elif k == 4:
        if freq[2] >= 2:  # If there are 2 or more even numbers
            return 0
        elif freq[2] == freq[3] == 0:  # If there are no 2s and no 3s
            return 2
        else:
            return 1
    else:
        for i in range(k - 1, 0, -1):  # Search from largest remainder to smallest
            if freq[i]:
                return k - i
    return


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/CodeForces/