# Contest 2043, Problem D: Problem about GCD
# URL: https://codeforces.com/contest/2043/problem/D

import sys, math

input = sys.stdin.buffer.readline


def solve():
    l, r, g = map(int, input().split())
    l = (l + g - 1) // g
    r //= g
    for n in range(r - l, -1, -1):
        for i in range(r - l - n + 1):
            a, b = (l + i) * g, (l + i + n) * g
            if math.gcd(a, b) == g:
                return f"{a} {b}"
    return "-1 -1"


ans = []
for t in range(int(input())):
    ans.append(solve())

print("\n".join(ans))
