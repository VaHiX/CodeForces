# Problem: CF 2110 A - Fashionable Array
# https://codeforces.com/contest/2110/problem/A

"""
Problem: Fashionable Array
Algorithm/Technique: Greedy approach with sorting and parity analysis.

The goal is to make an array "fashionable" by removing the minimum number of elements,
where a fashionable array has min + max divisible by 2.

Approach:
1. For each test case, sort the array.
2. Check if the sum of min and max (first and last elements after sorting) is divisible by 2.
3. If not, we must remove elements to reduce the array size until it's fashionable.
   - We check how many operations are needed by analyzing parity (even/odd nature).
4. The key idea: after removing some elements, we try to form a subsequence where sum of min and max is even.
   - For odd-length arrays: if we remove one element, the remaining array has two endpoints (min and max).
   - We can remove either start or end element and see if the result becomes fashionable.

Time Complexity: O(n log n) due to sorting per test case, where n <= 50
Space Complexity: O(n) for storing input array
"""

for s in [*open(0)][2::2]:  # Read every other line starting from index 2 (skip n and empty lines)
    a = [x % 2 for x in sorted(map(int, s.split()))]  # Sort and convert to parity (0 or 1)
    print(min(a.index(a[-1]), a[::-1].index(a[0])))   # Find minimum operations needed


# https://github.com/VaHiX/codeForces/