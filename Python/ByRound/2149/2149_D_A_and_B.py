# Problem: CF 2149 D - A and B
# https://codeforces.com/contest/2149/problem/D

"""
Problem: Min Swaps to Group Same Characters
Algorithm: Two-pointer technique with median minimization
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing positions

This solution evaluates the minimum swaps needed to group all 'a's or all 'b's together.
It computes the cost of making a block of one character type by finding optimal placement
using median of adjusted positions. The key insight is that for a contiguous block,
if we have k characters of a certain type at positions pos[0], ..., pos[k-1],
then their "adjusted" positions (pos[i] - i) should be minimized around the median.
"""

def min_swaps(s, ch):
    # Find all indices where character 'ch' occurs
    pos = [i for i, c in enumerate(s) if c == ch]
    k = len(pos)
    if k <= 1:
        return 0  # No swaps needed if 0 or 1 character
    # Adjust positions by subtracting index to find optimal alignment
    adjusted = [pos[i] - i for i in range(k)]
    adjusted.sort()
    # Find median of adjusted positions to minimize total distance
    median = adjusted[k // 2]
    # Calculate total swaps using Manhattan distances from median
    return sum(abs(x - median) for x in adjusted)


t = int(input())
for _ in range(t):
    n = int(input())
    s = input().strip()
    print(min(min_swaps(s, "a"), min_swaps(s, "b")))


# https://github.com/VaHiX/CodeForces/