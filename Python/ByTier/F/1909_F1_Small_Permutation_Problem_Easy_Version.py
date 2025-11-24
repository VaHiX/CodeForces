# Problem: CF 1909 F1 - Small Permutation Problem (Easy Version)
# https://codeforces.com/contest/1909/problem/F1

"""
Algorithm: Dynamic Programming with Mathematical Observations
Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem asks to count the number of "good" permutations of [1,2,...,n] such that
for each position i, the number of elements <= i in the prefix p[1..i] equals a[i].

Key insights:
1. For a valid permutation, a[i] must be in range [0, i] because we can have at most i elements
   in the first i positions.
2. The idea is to process positions incrementally and use dynamic programming to track
   how many valid ways there are to place elements.
3. When a[i+1] == a[i], it means we're not adding any new elements <= i+1,
   so we can continue with same count.
4. When a[i+1] == a[i]+1, we add one new element <= i+1. This introduces a factor of 
   (2*(i - a[i]) + 1) possibilities.
5. When a[i+1] == a[i]+2, it means two new elements are added, resulting in 
   (i - a[i])^2 possibilities (this happens when 2 elements are inserted between previous
   i elements and current element).
6. If any step violates a[i] <= i for any i, then answer is 0.
7. In the end, we check that a[n] == n (all elements up to n are present).

Note: We're using a[0] = 0 to simplify indexing.
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
    n, a = readInt(), [0] + readList()  # Add sentinel 0 at start for easier indexing
    dp = 1  # Starting number of ways, initialized to 1
    for i in range(n):
        if a[i] > i:
            return 0
        if a[i + 1] == a[i]:
            continue  # No change in count, continue
        elif a[i + 1] == a[i] + 1:
            # One new element added <= i+1
            # There are 2*(i - a[i]) + 1 ways to insert this new element
            dp *= 2 * (i - a[i]) + 1
            dp %= m
        elif a[i + 1] == a[i] + 2:
            # Two new elements added <= i+1
            # There are (i - a[i])^2 ways to place these
            dp *= (i - a[i]) ** 2
            dp %= m
        else:
            return 0  # Invalid increment, return 0
    # At the end, all elements must be covered
    return dp if a[-1] == n else 0


m = 998244353
for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/CodeForces/