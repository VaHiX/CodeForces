# Problem: CF 1882 C - Card Game
# https://codeforces.com/contest/1882/problem/C

"""
Card Game - Maximum Score Problem

Algorithm/Technique:
- Greedy approach with case analysis
- The key insight is that we can choose odd-indexed cards to add their values to score,
  and even-indexed cards to remove without adding to score.
- We analyze the first few cards to determine optimal strategy.
- Time Complexity: O(n) - single pass through array
- Space Complexity: O(1) - only using constant extra space

Approach:
1. Calculate maximum possible score by taking all positive numbers (greedy)
2. Analyze cases based on first two elements:
   - If only one card or first card non-negative or second card negative,
     just return the sum of positive numbers
   - Otherwise, consider two options:
     a) Take first card (add to score) and continue
     b) Skip first card (remove it) and take second card (subtract from score)
"""

t = input()
t = int(t)
for i in range(0, t):
    n = int(input())
    arr = list(map(int, input().split()))
    s = max(0, sum(i for i in arr if i > 0))
    if n == 1 or arr[0] >= 0 or arr[1] < 0:
        print(s)
    else:
        print(max(s + arr[0], s - arr[1]))


# https://github.com/VaHiX/CodeForces/