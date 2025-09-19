# Contest 2068, Problem C: Ads
# URL: https://codeforces.com/contest/2068/problem/C

import sys

input = sys.stdin.readline

for i in range(int(input())):
    n, k = map(int, input().split())
    d = sorted(list(map(int, input().split())))
    if d[0] >= k:
        print(n - 1)
        continue

    i = 0
    j = n - 1
    cnt = 0
    lft = n
    flag = False
    while i < j:
        while d[i] + d[j] >= k and i < j:
            j -= 1
        if i >= j:
            break
        d[i] = -1
        d[j] = -1
        cnt += 1
        i += 1
        j -= 1
        lft -= 2
        if lft <= cnt:
            break
    i = 0
    if lft > cnt:
        for i in range(n):
            if 0 < d[i] < k:
                cnt += 1
                lft -= 1
                if lft <= cnt:
                    break
    if lft < cnt:
        print(cnt - 1)
    else:
        print(lft - 1)
