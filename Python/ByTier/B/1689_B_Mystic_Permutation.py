# Contest 1689, Problem B: Mystic Permutation
# URL: https://codeforces.com/contest/1689/problem/B

import sys 

for _ in range(int( input() )):
    n = int( input() )
    p = list(map(int, sys.stdin.readline().split()))

    if n == 1:
        print(-1)
        continue

    q = sorted(p)
    for i in range(n - 1):
        if p[i] == q[i]:
            q[i], q[i + 1] = q[i + 1], q[i]

    if p[-1] == q[-1]:
        q[-1], q[-2] = q[-2], q[-1]

    print(*q)