# Contest 588, Problem A: Duff and Meat
# URL: https://codeforces.com/contest/588/problem/A

import sys
n = int(sys.stdin.readline().strip())
mi  =  float("inf")
ans= 0
for _ in range(n):
    a, b  = map(int, sys.stdin.readline().strip().split())
    mi = min(mi, b)
    ans += (a*mi)
print(ans)