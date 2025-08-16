# Contest 2127, Problem B: Hamiiid, Haaamid... Hamid?
# URL: https://codeforces.com/contest/2127/problem/B

import sys
input = sys.stdin.readline

for _ in range(int(input())):
    n, x = map(int, input().split())
    s = input()
    x -= 1
    if x == 0 or x == n - 1:
        print(1)
        continue
    jl, jr = x, x
    while jl >= 0 and s[jl] == '.':
        jl -= 1
    while jr < n and s[jr] == '.':
        jr += 1
    ansl = min(x + 1, 1 + n - jr)
    ansr = min(n - x, jl + 2)
    print(max(ansl, ansr))
    
