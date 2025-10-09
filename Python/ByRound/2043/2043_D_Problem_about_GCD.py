# Problem: CF 2043 D - Problem about GCD
# https://codeforces.com/contest/2043/problem/D

"""
D. Problem about GCD

Given three integers l, r, and G, find two integers A and B (l ≤ A ≤ B ≤ r) such that their greatest common divisor (GCD) equals G and the distance |A−B| is maximized.
If there are multiple such pairs, choose the one where A is minimized. If no such pairs exist, output "-1 -1".

Algorithm:
- For each test case, first scale down the range [l, r] by G to reduce the problem size.
- Use a nested loop approach to find the pair (a, b) with GCD = G and maximum |b - a|.
- Since we want maximum distance, iterate from largest possible n down to 0.
- For each n, iterate over all possible starting points i in valid range.
- Return first valid pair found (which will be minimal A due to iteration order).

Time Complexity: O(r/G) where r can be up to 10^18. In practice, since we iterate from largest differences down, and check GCD once per candidate, it's effectively bounded by a small constant in most cases.
Space Complexity: O(1), no extra space used beyond input storage and temporary variables.

Input Format:
- First line contains t (number of test cases)
- Each test case has three integers l, r, G

Output Format:
- For each test case, output A B if valid pair exists else "-1 -1"
"""

import math
import sys

input = sys.stdin.buffer.readline


def solve():
    l, r, g = map(int, input().split())
    # Scale down the range by G to simplify computation
    l = (l + g - 1) // g
    r //= g
    # Try decreasing differences from largest possible down to zero
    for n in range(r - l, -1, -1):
        # Iterate through all valid starting points for a given difference n
        for i in range(r - l - n + 1):
            a, b = (l + i) * g, (l + i + n) * g
            # If the GCD of the scaled values is 1, then original values have GCD = g
            if math.gcd(a, b) == g:
                return f"{a} {b}"
    return "-1 -1"


ans = []
for t in range(int(input())):
    ans.append(solve())
print("\n".join(ans))


# https://github.com/VaHiX/codeForces/