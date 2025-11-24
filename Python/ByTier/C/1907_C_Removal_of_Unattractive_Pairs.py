# Problem: CF 1907 C - Removal of Unattractive Pairs
# https://codeforces.com/contest/1907/problem/C

"""
Problem: Removal of Unattractive Pairs

Algorithms/Techniques: 
- Greedy approach with frequency counting
- The key insight is that we can pair up different characters
  and remove them, but if one character appears more than half
  of the total characters, it will remain unpaired.
  
Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) since there are at most 26 lowercase letters

The solution works by:
1. Counting the frequency of each character
2. Finding the maximum frequency (mc)
3. Calculating the minimum possible length based on pairing rules
"""

from collections import Counter
from sys import stdin

T = int(stdin.readline())
for t in range(T):
    n = int(stdin.readline())
    counts = Counter(stdin.readline()[:n])  # Read and count characters
    mc = max(counts.values())  # Find the maximum frequency
    # The result is the max of (mc - unpaired characters) and n % 2
    print(max(mc - (sum(counts.values()) - mc), n % 2))


# https://github.com/VaHiX/CodeForces/