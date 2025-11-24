# Problem: CF 2034 B - Rakhsh's Revival
# https://codeforces.com/contest/2034/problem/B

"""
B. Rakhsh's Revival
Algorithm: Greedy with Sliding Window
Time Complexity: O(n) per test case
Space Complexity: O(1)

Rostam needs to ensure no m consecutive 0s exist in the binary string s.
He can use "Timar" operation which strengthens a segment of length k,
changing all characters in that segment to '1'. The task is to find
the minimum number of such operations needed.

Approach:
- Traverse the string from left to right.
- When encountering a '0', check if it starts a sequence of m consecutive 0s.
- If yes, apply Timar on a segment starting at current position (or last possible position),
  and skip ahead by k positions as those are now strengthened.
- Keep count of operations.

Key observations:
- Use greedy strategy: whenever we find the beginning of an m-length sequence of 0s,
  immediately apply a Timar of size k, so that we maximize coverage.
"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, m, k = map(int, input().split())
    s = input()
    j = 0
    cnt = 0
    cur = 0
    while j < n:
        if s[j] == "1":  # If current spot is strong, reset counter
            cur = 0
            j += 1
        else:  # If current spot is weak
            cur += 1  # Increment length of consecutive 0s
            if cur == m:  # Found a sequence of m consecutive 0s
                cur = 0  # Reset the counter after applying Timar
                cnt += 1  # Increment operation count
                j += k  # Skip ahead by k positions (Timar covers them)
            else:
                j += 1  # Continue checking next position
    print(cnt)


# https://github.com/VaHiX/codeForces/