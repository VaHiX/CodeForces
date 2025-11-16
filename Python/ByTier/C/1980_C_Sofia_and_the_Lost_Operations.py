# Problem: CF 1980 C - Sofia and the Lost Operations
# https://codeforces.com/contest/1980/problem/C

"""
Purpose: Determine if a sequence of modification operations can transform array 'a' into array 'b'.
         Each operation assigns a value from 'd' to some index in the array.
         The indices for the operations are unknown, but we must check if a valid assignment exists.

Algorithms/Techniques:
- Greedy approach to match values in 'b' with values in 'd'
- Sort the values in 'd' and the distinct values in 'b' that differ from 'a'
- Match elements greedily from sorted lists

Time Complexity: O(n log n + m log m) where n is size of arrays a/b and m is size of d
Space Complexity: O(n + m) for storing extra arrays and sorted versions
"""

import sys

input = sys.stdin.readline


def solve(a, b, d, n, m):
    # If the last value in d is not present in b, it's impossible to complete transformation
    if d[m - 1] not in b:
        return False
    
    # Sort the modification values
    d_sorted = sorted(d)
    new = []

    # Collect all values in b that are different from a (these are the values that must be assigned)
    for i in range(n):
        if a[i] != b[i]:
            new.append(b[i])

    # Sort the distinct values to be assigned
    l = len(new)
    new = sorted(new)

    # Two pointers to match values in new (values to assign) with sorted d values
    i = 0  # pointer for values in new
    j = 0  # pointer for sorted d values
    
    while i < l and j < m:
        if new[i] == d_sorted[j]:
            # If values match, move to next value to assign
            i += 1
            j += 1
        elif new[i] < d_sorted[j]:
            # If current value in new is smaller than d_sorted[j], impossible to match
            return False
        else:
            # Skip d_sorted[j] as it's larger (greedy matching)
            j += 1

    # All values in new must be matched
    return i == l


t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    m = int(input())
    d = list(map(int, input().split()))
    if solve(a, b, d, n, m):
        print("YES")
    else:
        print("NO")


# https://github.com/VaHiX/CodeForces/