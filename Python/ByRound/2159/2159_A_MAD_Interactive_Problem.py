# Problem: CF 2159 A - MAD Interactive Problem
# https://codeforces.com/contest/2159/problem/A

"""
Interactive problem to reconstruct a secret sequence of length 2n containing each number from 1 to n exactly twice.
Uses queries to determine the MAD (Maximum Appearing Duplicate) of subsets of the sequence.

Algorithm:
- First phase: Identify unique elements by querying with single elements and checking MAD value
- Second phase: For remaining positions, query with known duplicate positions to determine values
- Time Complexity: O(n^2) - at most 3n queries needed
- Space Complexity: O(n) - for storing the result array and auxiliary data

Techniques used:
- Binary search-like approach with MAD queries
- Greedy reconstruction based on query results
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
mi = lambda: map(int, input().split())
li = lambda: list(mi())


def solve(N):
    def query(X):
        # Query the MAD value of elements at indices X (0-based) in the secret sequence
        print(f"? {len(X)}", *[x + 1 for x in X], flush=True)
        return int(input())

    def answer(A):
        # Output the reconstructed sequence
        print("!", *A, flush=True)

    unique = [0]  # Initialize list to track elements that are unique (MAD=0 when queried alone)
    A = [-1] * (2 * N)  # Result array to store the secret sequence
    all_set = []  # List of positions where we've already determined a value > 0
    
    # First pass: Try to determine which elements are unique, and build all_set with non-unique ones
    for i in range(1, 2 * N):
        c = query(unique[:] + [i])  # Query with current known unique elements plus new one
        if c == 0:
            # If MAD is 0, element at index 'i' must be unique (not appearing elsewhere)
            unique.append(i)
            continue
        else:
            # If MAD > 0, then value at position i must be the duplicate of some value
            A[i] = c
            all_set.append(i)  # Mark as needing further deduction
    
    # Second pass: For positions that are still unassigned (-1), use information from duplicates
    for i in range(2 * N):
        if A[i] == -1:
            # Determine value at position i using the all_set elements (known to contain duplicates)
            A[i] = query(all_set[:] + [i])
    
    answer(A)  # Output final result


for _ in range(int(input())):
    N = int(input())
    solve(N)


# https://github.com/VaHiX/CodeForces/