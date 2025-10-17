# Contest 2005, Problem E1: Subtangle Game (Easy Version)
# URL: https://codeforces.com/contest/2005/problem/E1

import sys
import math
input = sys.stdin.readline

t = int(input())
final = []

for _ in range(t):
    
    l, n, m = map(int, input().strip().split())
    a = list(map(int, input().strip().split()))
    b = [list(map(int, input().strip().split())) for _ in range(n)]

    if n > m:
        n, m = m, n
        b = list(map(list, zip(*b)))

    idx = []
    
    for b_i in b:
        idx_i = {}
        for j, b_ij in enumerate(b_i):
            idx_i[b_ij] = j
        idx.append(idx_i)

    lb = [-1] * n
    
    for a_cur in a[:0:-1]:
    
        for i in range(n):
            idx_i = idx[i].get(a_cur, -1)
    
            if idx_i < lb[i]:
                idx_i = -1
            lb[i] = idx_i
        lb_cur = -1
    
        for i in range(n - 1, -1, -1):
            lb_i = lb[i]
            lb[i] = lb_cur
            lb_cur = max(lb_cur, lb_i)
    
    ans = 'T' if any(idx_i.get(a[0], -2) >= lb_i for lb_i, idx_i in zip(lb, idx)) else 'N'

    final.append(ans)

sys.stdout.write('\n'.join(final))
