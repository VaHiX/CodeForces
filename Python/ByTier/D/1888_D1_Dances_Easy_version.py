# Problem: CF 1888 D1 - Dances (Easy version)
# https://codeforces.com/contest/1888/problem/D1

"""
Algorithm: Two Pointers / Greedy Approach
Time Complexity: O(n * log(n)) due to sorting
Space Complexity: O(n) for storing the arrays

The problem asks to find the minimum number of operations to make a_i < b_i for all valid i,
where we can reorder elements in both arrays before performing operations.
We use a greedy approach:
1. Sort both arrays.
2. For each element in the sorted array 'a', find the smallest element in the sorted array 'b'
   such that b[j] > a[i]. If such element exists, we pair them and move to the next element.
   Otherwise, all remaining elements of 'a' must be matched with the remaining elements of 'b'.

The key insight is to use two pointers to avoid redundant checks.
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
    n, m = readInts()
    a, b = sorted([1] + readList()), sorted(readList())  # Create c[i] by prepending 1 to a
    j = 0  # Pointer for array b
    for i in range(n):  # Pointer for array a
        # Move j forward until b[j] > a[i]
        while j < n and b[j] <= a[i]:
            j += 1
        if j == n:  # No suitable element left in b
            return n - i  # All remaining elements in a must be paired
        j += 1  # Move to next element in b
    return 0  # All elements successfully paired


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/CodeForces/