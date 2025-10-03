# Problem: CF 2137 E - Mexification
# https://codeforces.com/contest/2137/problem/E

"""
E. Mexification

Purpose:
    Given an array of integers and a number of operations k, we perform the following procedure k times:
    For each element in the array, replace it with the MEX (minimum excluded) of all other elements in the array.
    Return the sum of the final array after all operations.

Algorithms/Techniques:
    - MEX calculation using frequency counting
    - Observation: After a few iterations, the array tends to stabilize due to repeated patterns.
    - Optimization for large k by detecting cycles or fixed points after initial operations.

Time Complexity:
    O(n) per test case, where n is the size of the array. This accounts for up to 5 iterations followed by constant time for k > 5.
    
Space Complexity:
    O(n) for storing counts and auxiliary arrays.
"""

import sys

input = sys.stdin.readline


def solve():
    n, k = map(int, input().split())
    a = [int(x) for x in input().split()]
    sm = [0] * 5      # Store sums after 1 to 5 operations
    op = [0] * 2      # Store sums for even and odd iterations beyond 5
    for j in range(5):        # Perform up to 5 operations
        cnt = [0] * (n + 2)   # Count frequency of elements
        for x in a:
            cnt[x] += 1       # Increment count for each element
        for i in range(n + 2):
            if not cnt[i]:    # Find the first missing non-negative integer (MEX)
                m = i
                break
        ac = [0] * n          # New array after this step
        for i in range(n):
            if a[i] < m and cnt[a[i]] == 1:   # If element is less than MEX and unique
                ac[i] = a[i]
            else:
                ac[i] = m                     # Otherwise set to MEX
        sm[j] = sum(ac)           # Save sum after j-th operation
        op[j % 2] = sum(ac)       # Save sum depending on even/odd step
        a = ac                    # Update array for next iteration
    if k <= 5:
        print(sm[k - 1])          # If k is small, use precomputed result
    else:
        print(op[(k & 1) ^ 1])    # For large k, use cycle detection (even/odd parity)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/codeForces/