# Contest 1710, Problem A: Color the Picture
# URL: https://codeforces.com/contest/1710/problem/A

import sys
from array import array

input = lambda: sys.stdin.buffer.readline().decode().strip()
out = []


def calc(r, c):
    for i in range(k - 1, -1, -1):
        if a[i] // r > 1:
            c -= a[i] // r
        if c == 1 and (a[-1] // r < 3 or max(a[:i], default=0) // r < 2):
            return 0

    return c < 1


for _ in range(int(input())):
    n, m, k = map(int, input().split())
    a = array("i", sorted([int(x) for x in input().split()]))
    out.append("Yes" if calc(n, m) or calc(m, n) else "No")
print("\n".join(out))
