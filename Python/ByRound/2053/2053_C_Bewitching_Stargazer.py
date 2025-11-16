# Problem: CF 2053 C - Bewitching Stargazer
# https://codeforces.com/contest/2053/problem/C

"""
C. Bewitching Stargazer
Algorithm: Simulate the recursive star observation process where Iris splits segments based on parity of length,
            and accumulates a "lucky value" by observing the middle star when segment length is odd.
            The key insight is to simulate the process using bit manipulation.

Time Complexity: O(log n) per test case, as we halve n in each iteration.
Space Complexity: O(1), only using a few variables.

The algorithm mimics how Iris observes stars:
- When observing segment [l,r] with length r-l+1:
  - If even: split into [l,m] and [m+1,r]
  - If odd: observe middle star m, add m to lucky value, then split into [l,m-1] and [m+1,r]
- Observation stops when segment length < k.

We simulate this using bit representation of n.
"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, k = map(int, input().split())
    v = n + 1
    seg, cnt = 1, 0
    while n >= k:  # While the current segment length is at least k
        cnt += seg * (n % 2)  # If n is odd, we add the contribution of this step to the lucky value
        n //= 2  # Move to next level by halving the segment size
        seg *= 2  # Double the contribution weight for next level
    print(cnt * v // 2)


# https://github.com/VaHiX/codeForces/