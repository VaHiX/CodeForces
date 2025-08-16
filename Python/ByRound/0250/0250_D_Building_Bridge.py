# Contest 250, Problem D: Building Bridge
# URL: https://codeforces.com/contest/250/problem/D

from math import sqrt

n, m, a, b = [int(i) for i in input().split(' ')]
y = [int(i) for i in input().split(' ')]
z = [int(i) for i in input().split(' ')]
p = [int(i) for i in input().split(' ')]
bi, bj = 0, 0
d = lambda yi, zj: sqrt((yi - zj) ** 2 + (b - a) ** 2) + sqrt(a ** 2 + yi ** 2)
for j in range(m):
    l, r = 0, n - 1
    while l < r:
        m = (l + r) // 2
        d1 = d(y[m], z[j])
        d2 = d(y[m+1], z[j])
        if d2 > d1:
            r = m
        else:
            l = m + 1
    for c in [l-1, l, l+1]:
        if 0 <= c < n and d(y[c], z[j]) + p[j] < d(y[bi], z[bj]) + p[bj]:
            bi, bj = c, j
print(bi + 1, bj + 1)

	     		  		 				 		  		   	