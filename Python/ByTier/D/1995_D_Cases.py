# Problem: CF 1995 D - Cases
# https://codeforces.com/contest/1995/problem/D

"""
D. Cases
Algorithm: Sliding window + Dynamic Programming
Time Complexity: O(n * c + 2^c)
Space Complexity: O(2^c)

The problem asks to find the minimum number of cases in a language where each case corresponds to a unique ending letter.
We use a sliding window approach to consider all substrings of length k and track which letters appear.
Then we use dynamic programming on bitmasks to determine what combinations of letters can be present,
and find the minimal number of cases by counting unset bits in the final DP state.

Steps:
1. Use sliding window to calculate masks for each substring of length k
2. Use DP with bitmask to propagate possible letter combinations
3. Find minimum number of unset bits in the final DP state (corresponds to minimum number of cases)
"""

from sys import *

input = stdin.readline
inputlist = lambda: map(int, stdin.readline().split())


def solve():
    n, c, k = inputlist()
    s = input().strip()
    masks = []
    count = [0 for _ in range(c)]
    current = 0
    # Build initial mask for first k characters
    for i in range(k):
        bit = ord(s[i]) - ord("A")
        current |= 1 << bit
        count[bit] += 1
    masks.append(current)
    # Slide window and update mask
    for i in range(n - k):
        removebit = ord(s[i]) - ord("A")       # Bit to remove from mask
        newbit = ord(s[i + k]) - ord("A")      # Bit to add to mask
        count[removebit] -= 1
        count[newbit] += 1
        if not count[removebit]:
            current ^= 1 << removebit  # Remove bit from current mask if count becomes 0
        current |= 1 << newbit         # Add new bit to mask
        masks.append(current)
    
    dp = [0 for _ in range(1 << c)]    # DP array for all possible masks
    for mask in masks:
        dp[mask] = 1                   # Mark reachable masks
    
    # Ensure the last character is considered
    dp[1 << (ord(s[-1]) - ord("A"))] = 1
    
    # Propagate all possible combinations using DP
    for mask in range(len(dp)):
        if dp[mask]:
            for i in range(c):
                dp[mask | (1 << i)] = 1   # Add each letter to existing mask
    
    smallest = c
    # Find the minimal number of unset bits among all unreachable masks
    for mask in range(len(dp)):
        if not dp[mask]:
            smallest = min(smallest, c - mask.bit_count())
    return smallest


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/codeForces/