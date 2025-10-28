# Problem: CF 1991 F - Triangle Formation
# https://codeforces.com/contest/1991/problem/F

"""
Problem: Triangle Formation
Purpose: Determine if 2 non-degenerate triangles can be formed from a subarray of sticks.
Algorithms/Techniques: 
- Sorting the subarray to simplify triangle inequality checks
- Greedy approach for forming first triangle
- Brute-force check for second triangle using combinations of 6 elements
Time Complexity: O(n log n + q * n) where n is number of sticks and q is number of queries
Space Complexity: O(n) for storing the array and sorting temporary subarrays
"""

from sys import *

input = stdin.readline
inputlist = lambda: map(int, stdin.readline().split())


def solve():
    l, r = inputlist()
    if r - l + 1 >= 48:
        return "YES"
    else:
        # Sort the subarray to simplify triangle checks
        array = sorted(a[l - 1 : r])
        count = 0
        i = 0
        # Try to form first triangle using greedy approach
        # If three consecutive elements form a valid triangle, we consider it as such
        while i < len(array) - 2:
            if array[i] + array[i + 1] > array[i + 2]:
                count += 1
                i += 3  # Move to next potential triangle after current one
            else:
                i += 1
            if count >= 2:
                return "YES"
        # Check all combinations of choosing 6 sticks to form 2 triangles
        # Enumerate all possible pairs of triangles using 6 indices
        for i in range(len(array) - 5):
            # Triangle 1: indices i, i+1, i+2; Triangle 2: indices i+3, i+4, i+5
            if (
                array[i] + array[i + 2] > array[i + 3]
                and array[i + 1] + array[i + 4] > array[i + 5]
            ):
                return "YES"
            # Triangle 1: indices i, i+1, i+3; Triangle 2: indices i+2, i+4, i+5
            if (
                array[i] + array[i + 3] > array[i + 4]
                and array[i + 1] + array[i + 2] > array[i + 5]
            ):
                return "YES"
            # Triangle 1: indices i, i+1, i+4; Triangle 2: indices i+2, i+3, i+5
            if (
                array[i] + array[i + 4] > array[i + 5]
                and array[i + 1] + array[i + 2] > array[i + 3]
            ):
                return "YES"
    return "NO"


n, q = inputlist()
a = list(inputlist())
for _ in range(q):
    print(solve())


# https://github.com/VaHiX/CodeForces/