# Problem: CF 2149 B - Unconventional Pairs
# https://codeforces.com/contest/2149/problem/B

"""
B. Unconventional Pairs

Algorithm/Technique: Greedy approach with sorting.

The problem asks to pair up elements in such a way that the maximum difference
among all pairs is minimized. To achieve this, we sort the array and pair adjacent elements,
which ensures the differences are as small as possible.

Time Complexity: O(n log n) per test case due to sorting.
Space Complexity: O(1) additional space (not counting input storage).
"""

t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    a.sort()  # Sort the array to enable greedy pairing
    b = [a[i + 1] - a[i] for i in range(0, n, 2)]  # Pair adjacent elements and compute differences
    print(max(b) if b else 0)  # Output the maximum difference among pairs


# https://github.com/VaHiX/CodeForces/