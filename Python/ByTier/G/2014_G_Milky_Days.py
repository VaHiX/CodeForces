# Contest 2014, Problem G: Milky Days
# URL: https://codeforces.com/contest/2014/problem/G

import sys
input = sys.stdin.readline
for _ in range(int(input())):
    n,m,k = map(int,input().split())
    S = 0
    day = 0
    mon = []
    for q in range(n+1):
        rem = 0
        if q < n:
            d,a = map(int,input().split())
        else:
            d = int(1e9)
            a = 0
        while mon and day < d:
            assert (rem < m)
            exp,num = mon.pop()
            if day >= exp:continue
            num += rem
            mi = min(d-day, max(0,exp-day), num // m)
            S += mi
            day += mi
            num -= m * mi
            if day < d:
                if exp <= day:continue
                if mon:
                    rem = num
                else:
                    #mon.append((exp,num))
                    break
            else:
                if exp <= day:continue
                mon.append((exp,num))

        mon.append((d+k,a))
        day = d
    print(S)