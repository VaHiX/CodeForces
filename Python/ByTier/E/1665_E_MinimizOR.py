# Contest 1665, Problem E: MinimizOR
# URL: https://codeforces.com/contest/1665/problem/E

import heapq
import sys, os, io

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def sparse_table(a):
    table = []
    s0, l = a, 1
    table.append(s0)
    while 2 * l <= len(a):
        s = [min(s0[i], s0[i + l]) for i in range(len(s0) - l)]
        table.append(list(s))
        s0 = s
        l *= 2
    return table


def get_min(l, r, table):
    d = (r - l + 1).bit_length() - 1
    ans = min(table[d][l], table[d][r - pow2[d] + 1])
    return ans


t = int(input())
ans = []
pow2 = [1]
for _ in range(20):
    pow2.append(2 * pow2[-1])
inf = pow(2, 30) + 1
for _ in range(t):
    n = int(input())
    a = [0] + list(map(int, input().split()))
    for i in range(1, n + 1):
        a[i] *= n + 1
        a[i] += i
    table = sparse_table(a)
    q = int(input())
    for _ in range(q):
        l, r = map(int, input().split())
        ans0 = inf
        h = []
        heapq.heappush(h, (get_min(l, r, table), l, r))
        x = []
        while len(h) and h[0][0] // (n + 1) < ans0:
            c, l, r = heapq.heappop(h)
            z = c // (n + 1)
            c %= n + 1
            for i in x:
                ans0 = min(ans0, i | z)
            x.append(z)
            if l ^ c:
                heapq.heappush(h, (get_min(l, c - 1, table), l, c - 1))
            if c ^ r:
                heapq.heappush(h, (get_min(c + 1, r, table), c + 1, r))
        ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))
