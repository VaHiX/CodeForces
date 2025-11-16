# Problem: CF 1079 A - Kitchen Utensils
# https://codeforces.com/contest/1079/problem/A

"""
Problem: Minimum Stolen Utensils

Given n utensils remaining after a dinner with k guests, determine the minimum number of 
utensils that could have been stolen. Every guest ate the same number of dishes, and each 
dish was served with a complete set of utensils (all different types). 

Algorithms/Techniques:
- Count frequencies of each utensil type
- For each utensil type, calculate how many complete sets must have existed
  based on the number of guests (k) and current count
- Sum up total required utensils across all types
- Subtract original count to find stolen utensils

Time Complexity: O(n) where n is the number of remaining utensils
Space Complexity: O(n) for storing counter of utensil types

Input:
- First line: n (number of remaining utensils), k (number of guests)
- Second line: n integers representing utensil types

Output:
- Minimum number of stolen utensils
"""

import collections
import sys

input = sys.stdin.readline

fmin = lambda x, y: x if x < y else y
fmax = lambda x, y: x if x > y else y


def solve(N, K, arr):
    needed = 0
    max_count = collections.Counter()  # Count frequency of each utensil type
    for x in arr:
        max_count[x] += 1  # Increment count for each utensil type
    for key, count in max_count.items():
        # Calculate minimum number of utensils required for this type
        # ((count + K - 1) // K) computes how many complete sets are needed
        # Multiply by K to get total utensils needed for this type
        needed = fmax(needed, ((count + K - 1) // K) * K)
    # Total required utensils minus original count gives stolen utensils
    return needed * len(set(arr)) - len(arr)


N, K = list(map(int, input().strip().split(" ")))
arr = list(map(int, input().strip().split(" ")))
result = solve(N, K, arr)
print(result)


# https://github.com/VaHiX/codeForces/