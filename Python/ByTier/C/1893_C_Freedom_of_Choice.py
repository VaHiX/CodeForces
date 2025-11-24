# Problem: CF 1893 C - Freedom of Choice
# https://codeforces.com/contest/1893/problem/C

"""
Algorithm: Greedy with Prefix Sum and Map
Purpose: Minimize the anti-beauty (number of occurrences of the size of the multiset) 
         when selecting elements from multiple multisets under constraints.

Time Complexity: O(sum of n_i) where sum of n_i <= 10^5
Space Complexity: O(sum of n_i) for storing maps and sums

This solution uses a greedy approach where for each element in a multiset, 
we compute how many times it can be selected in order to minimize the final anti-beauty. 
It tracks the minimum number of occurrences of each element across all possible selections.

The key idea is to use a greedy selection strategy that ensures minimal overlap 
in the count of elements in final multiset.
"""

from collections import defaultdict


def run():
    m = int(input())
    M = defaultdict(int)  # Tracks how many times each element is added
    q = defaultdict(int)  # Tracks the max possible selections for each element 
    L = 0  # Total minimum selections across all multisets
    R = 0  # Total maximum selections across all multisets
    N = 0  # Total number of distinct elements across all multisets
    for _ in range(m):
        n, l, r = [int(x) for x in input().split()]  # n: size of multiset, l,r: range of selections
        N += n
        L += l
        R += r
        x = [int(x) for x in input().split()]  # Distinct elements
        c = [int(x) for x in input().split()]  # Count of each element
        s = sum(c)  # Total count of elements in this multiset
        for i in range(n):
            # Compute min number of times we must include this element
            a = max(r - (s - c[i]), 0)
            M[x[i]] += a  # Add to overall count
            q[x[i]] += min(a, r - l)  # Update max possible count for element
    # If total required elements exceed total distinct elements, anti-beauty is 0
    if R - L > N:
        A = 0
    else:
        A = float("inf")
        # For each possible total size of multiset, calculate min anti-beauty
        for i in range(L, R + 1):
            A = min(A, M[i] - min(R - i, q[i]))
    print(A)


for _ in range(int(input())):
    run()


# https://github.com/VaHiX/CodeForces/