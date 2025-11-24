# Problem: CF 1883 G2 - Dances (Hard Version)
# https://codeforces.com/contest/1883/problem/G2

"""
Algorithm: Two-pointer technique with preprocessing
Time Complexity: O(n * log(n)) due to sorting
Space Complexity: O(1) not counting input storage

This code solves the problem of finding the minimum number of operations to make 
a[i] < b[i] for all valid i after reordering arrays a and b. For each test case, 
we compute the result for m different pairs of arrays where the first element of a 
is varied from 1 to m, and then multiply the result by m.
"""

import sys


def solute():
    n, m = map(int, sys.stdin.readline().strip().split())
    a = list(map(int, sys.stdin.readline().split()))
    b = list(map(int, sys.stdin.readline().split()))
    a.sort()
    b.sort()
    i, j = 0, 0
    res = 0
    removed = 1
    # Use two pointers to match elements from sorted arrays
    # If a[i] < b[j], we can pair them and increment both pointers
    # Otherwise, we must remove b[j] and increment only j
    while i < n - 1 and j < n:
        if a[i] < b[j]:
            i += 1
            j += 1
            res += 1
        else:
            removed = max(removed, b[j])
            j += 1
    # Calculate how many elements from a remain unmatched
    res1 = n - res
    # If we haven't processed all elements in b, update removed
    if j < n:
        removed = b[n - 1]
    # The final result is total operations needed multiplied by m
    print(res1 * m - min(removed - 1, m))


t = int(sys.stdin.readline().strip())
for _ in range(t):
    solute()


# https://github.com/VaHiX/CodeForces/