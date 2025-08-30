# Contest 2053, Problem I1: Affectionate Arrays (Easy Version)
# URL: https://codeforces.com/contest/2053/problem/I1

import io, os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
for _ in range(int(input())):
    n = int(input())
    a = [int(i) for i in input().split()]
    s, l, r, cur = 0, 0, 0, n
    for i in a:
        s += i
    for i in a:
        l += i
        r += i
        l = max(l, 0)
        r = min(r, s)
        if l > r:
            l = max(0, i)
            r = s + min(0, i)
            cur += 1
    print(cur + (1 if r < s else 0))
