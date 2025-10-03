# Contest 1662, Problem M: Bottle Arrangements
# URL: https://codeforces.com/contest/1662/problem/M

from itertools import islice
from sys import stdin

lines = map(lambda line: map(int, line.split()), stdin.readlines()[1:])

for n, m in lines:
    max_r = max_w = 0
    for r, w in islice(lines, m):
        max_r, max_w = max(max_r, r), max(max_w, w)
    if max_r + max_w > n:
        print("IMPOSSIBLE")
    else:
        print(f"{'R' * max_r}{'W' * (n - max_r)}")
