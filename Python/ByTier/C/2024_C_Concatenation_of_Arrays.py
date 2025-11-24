# Problem: CF 2024 C - Concatenation of Arrays
# https://codeforces.com/contest/2024/problem/C

"""
Problem: Concatenation of Arrays
Algorithm: Greedy Sorting
Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing input arrays

Approach:
- For each array, we compute the sum of its two elements.
- We sort the arrays based on this sum in ascending order.
- This greedy approach minimizes the number of inversions by placing smaller sum arrays earlier,
  which reduces the chances of creating inversions when concatenating.
"""

from sys import stdin

input = lambda: stdin.readline().rstrip()
for _ in range(int(input())):
    a = [input() for _ in range(int(input()))]
    print(*sorted(a, key=lambda x: sum(map(int, x.split()))))


# https://github.com/VaHiX/CodeForces/