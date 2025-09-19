# Contest 1852, Problem A: Ntarsis' Set
# URL: https://codeforces.com/contest/1852/problem/A

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n, k = map(int, input().split())
    arr = tuple(map(int, input().split()))
    if arr[0] != 1:
        print(1)
        continue
    ans = 1
    increaser = 1
    curr_idx = 1
    while k > 0:
        if (curr_idx) < n and (ans + increaser >= arr[curr_idx]):
            increaser += 1
            curr_idx += 1
            continue
        ans += increaser
        k -= 1

    print(ans)
