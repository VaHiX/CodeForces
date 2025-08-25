# Contest 2074, Problem F: Counting Necessary Nodes
# URL: https://codeforces.com/contest/2074/problem/F

import sys

I = input = sys.stdin.readline
for _ in range(int(I())):
    l, r, d, u = map(int, I().split())
    ans = (r - l) * (u - d)
    for i in range(1, min(r - l, u - d).bit_length()):
        s = 1 << i
        ans -= 3 * (r // s - (l + s - 1) // s) * (u // s - (d + s - 1) // s)
    sys.stdout.write(f"{ans}\n")
