# Problem: CF 1854 A1 - Dual (Easy Version)
# https://codeforces.com/contest/1854/problem/A1

"""
Algorithm: Dual (Easy Version)
Purpose: Transform an array into a non-decreasing sequence using at most 50 operations.
Each operation adds an element to another element (a[i] := a[i] + a[j]).

Approach:
1. Identify the first positive element from the left (start).
2. Identify the last negative element from the right (last).
3. Process elements from start to end to ensure non-decreasing order.
4. Process elements from last to start to ensure non-decreasing order.
5. Use double operations to increase values where needed.

Time Complexity: O(n^2) in worst case due to nested loops and while conditions,
                 but limited to at most 50 operations per test case.
Space Complexity: O(n) for storing the array and operations list.

This solution works under the constraint of n <= 20 and maximum 50 operations.
"""

import sys

input = sys.stdin.readline


def calc(i, j):
    # Add operation to the list of operations
    ANS.append((i, j))
    # Perform the actual addition
    A[i] += A[j]


t = int(input())
for tests in range(t):
    n = int(input())
    A = list(map(int, input().split()))

    ANS = []
    # Find the first positive element from the left
    start = n
    for i in range(n):
        if A[i] > 0:
            start = i
            break

    last = -1
    # Find the last negative element from the right
    for j in range(start - 1, -1, -1):
        if A[j] < 0:
            last = j
            break

    # Process elements from start to end if there are any positive elements
    if start != n:
        # Double the value at start until it's at least 20 to prevent overflow
        while A[start] < 20:
            calc(start, start)

        # Ensure the array is non-decreasing from start to end
        for i in range(start, n - 1):
            while A[i] > A[i + 1]:
                calc(i + 1, i)

    # Process elements from last back to start if there are any negative elements
    if last != -1:
        # Double the value at last until it's at least -20 to prevent overflow
        while A[last] > -20:
            calc(last, last)

        # Ensure the array is non-decreasing from last back to start
        for i in range(last, 0, -1):
            while A[i] < A[i - 1]:
                calc(i - 1, i)

    # Output the number of operations
    print(len(ANS))
    # Output each operation
    for x, y in ANS:
        print(x + 1, y + 1)


# https://github.com/VaHiX/CodeForces/