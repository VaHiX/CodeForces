# Problem: CF 1872 C - Non-coprime Split
# https://codeforces.com/contest/1872/problem/C

"""
Non-coprime Split

Algorithm:
- The problem asks to find two positive integers a and b such that:
  1. l <= a + b <= r
  2. gcd(a, b) != 1 (i.e., they are not coprime)

Approach:
- If r < 4, then there's no valid pair since the minimum possible sum is 2 (1+1), and 1+1=2, but we need to reach at least l.
- If r is even, we can always choose a=2, b=r-2 (since 2 and r-2 are not coprime if r is even because they share factor 2).
- If r is odd and greater than l, we can try a=2, b=r-3. This works because 2 and r-3 are not coprime if r is odd, since 2 shares a factor of 2.
- If r is odd and r == l we look for a small factor of r.
- Time complexity: O(sqrt(r)) in worst case due to the loop checking factors.
- Space complexity: O(1) - constant extra space.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
sint = lambda: int(input())
mint = lambda: map(int, input().split())
ints = lambda: list(map(int, input().split()))


def solve() -> None:
    l, r = mint()
    if r < 4:
        print(-1)
    elif r % 2 == 0:
        print(2, r - 2)
    elif r > l:
        print(2, r - 3)
    else:
        d = 2
        while d * d <= r:
            if r % d == 0:
                k = r // d
                print(d, d * (k - 1))
                return
            d += 1
        print(-1)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/