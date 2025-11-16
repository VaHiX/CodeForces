# Problem: CF 2039 A - Shohag Loves Mod
# https://codeforces.com/contest/2039/problem/A

"""
Problem: Shohag Loves Mod
Algorithm/Technique: Greedy construction
Time Complexity: O(n) per test case
Space Complexity: O(1) extra space

The solution constructs a sequence by selecting odd numbers starting from 1.
For any two indices i < j, we have a_i % i and a_j % j. Since all elements are odd,
a_i % i will always be odd for i > 1. Similarly for a_j % j. This ensures that
the remainders are distinct for all pairs (i,j) where i < j.
"""

for s in [*open(0)][1:]:
    for i in range(1, 2 * int(s) + 1, 2):
        print(i, end=" ")
    print()


# https://github.com/VaHiX/CodeForces/