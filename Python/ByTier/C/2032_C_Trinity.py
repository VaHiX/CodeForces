# Problem: CF 2032 C - Trinity
# https://codeforces.com/contest/2032/problem/C

"""
C. Trinity

Algorithm/Technique: Two Pointers, Sorting

Time Complexity: O(n log n) per test case due to sorting; overall O(t * n log n)
Space Complexity: O(1) additional space (not counting input/output)

The problem asks us to make an array such that every triplet of distinct indices forms a non-degenerate triangle.
A non-degenerate triangle satisfies the triangle inequality for all three sides.
By sorting the array, we can use a two-pointer approach:
- We iterate through the sorted array and try to find elements that can form valid triangles.
- If for any index j, the sum of elements at positions i and i+1 is less than or equal to a[j],
  then we must increase i, meaning we need to change more elements to satisfy the triangle inequality.
- The final value of i represents how many operations are needed.
"""

from sys import stdin

input = lambda: stdin.readline().rstrip()
for test in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    a.sort()  # Sort the array to simplify triangle inequality checks
    i = 0     # Pointer to track how many changes we need to make
    for j in range(n):
        # If sum of two smallest elements (at i and i+1) is <= current element at j,
        # we must move i forward to include larger values
        if a[i] + a[i + 1] <= a[j]:
            i += 1
    print(i)


# https://github.com/VaHiX/codeForces/