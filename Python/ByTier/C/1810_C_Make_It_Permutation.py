# Problem: CF 1810 C - Make It Permutation
# https://codeforces.com/contest/1810/problem/C

"""
Algorithm: Greedy with Sorting
Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the array

Approach:
- We want to transform the array into a permutation of length k (1 to k).
- For each possible length k of the permutation, calculate the cost:
  - Remove all elements not in range [1, k] (cost = count of such elements * c)
  - Insert missing elements (cost = count of missing elements * d)
- We iterate through sorted array and try to form a permutation of size k starting from each unique element.
- Use sliding window approach to efficiently compute removal and insertion costs.

Key observations:
- If all elements are unique and form a valid permutation, cost is 0.
- Otherwise, we can either remove elements or insert elements to get a permutation.
- Try all possible sizes and find the minimum cost.
"""

import sys

input = sys.stdin.readline

for t in range(int(input())):
    n, c, d = map(int, input().split())
    A = sorted(list(map(int, input().split())))
    result = n * c + d  # Worst case: remove all and insert one

    consec = 0
    for i in range(n):
        # Count consecutive duplicates
        if i > 0 and A[i] == A[i - 1]:
            consec += 1
        # Calculate cost for permutation of length (n - 1 - i + consec)
        # Remove all elements after index i that are not needed
        # Remove duplicates from start
        cur = (n - 1 - i + consec) * c + (A[i] - (i + 1 - consec)) * d
        result = min(result, cur)
    print(result)


# https://github.com/VaHiX/CodeForces/