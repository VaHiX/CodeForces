# Problem: CF 2096 B - Wonderful Gloves
# https://codeforces.com/contest/2096/problem/B

"""
B. Wonderful Gloves

Purpose:
This code solves the problem of finding the minimum number of gloves to draw from a drawer to guarantee 
at least k matching pairs of gloves with different colors. Each glove has a color and a type (left or right).
A matching pair consists of one left and one right glove of the same color.

Algorithm:
- For each color, calculate the minimum of left and right gloves (this gives the number of possible pairs).
- Sort these minimums in ascending order.
- Use greedy approach to determine how many gloves need to be drawn in worst-case scenario.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the list of minimum pairs

Techniques:
- Greedy algorithm
- Sorting
- Worst-case analysis
"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, k = map(int, input().split())  # Read n (colors) and k (required pairs)
    l = list(map(int, input().split()))  # Left gloves per color
    r = list(map(int, input().split()))  # Right gloves per color
    a = sorted([min(l[j], r[j]) for j in range(n)])  # Sort min pairs for each color
    # Calculate minimum gloves needed to guarantee k pairs:
    # Sum of all left + right gloves minus sum of worst (n-k) pairs + 1 for the last necessary pair
    print(sum(l) + sum(r) - sum(a[: n - k]) - a[n - k] + 1)


# https://github.com/VaHiX/codeForces/