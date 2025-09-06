# Contest 2090, Problem E2: Canteen (Hard Version)
# URL: https://codeforces.com/contest/2090/problem/E2

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    if sum(a) <= k:
        print(0)
        continue
    for i in range(n):
        d = min(a[i], b[i])
        a[i] -= d
        b[i] -= d
    if sum(a) <= k:
        print(1)
        continue
    pref = [0]
    for i in range(n):
        pref.append(pref[-1] + a[i] - b[i])
    ex = pref.index(min(pref))
    a = a[ex:] + a[:ex]
    b = b[ex:] + b[:ex]
    pref = [0]
    for i in range(n):
        pref.append(pref[-1] + a[i] - b[i])
    lo = 0
    hi = n
    while hi - lo > 1:
        aa = a[:]
        mid = (lo + hi) // 2
        need = 0
        st = []
        l = n - 1
        for r in range(n):
            st.append(r)
            x = b[r]
            while x and st and r - st[-1] < mid:
                d = min(aa[st[-1]], x)
                x -= d
                aa[st[-1]] -= d
                if aa[st[-1]] == 0:
                    st.pop()
        need = sum(aa)
        if need <= k:
            hi = mid
        else:
            lo = mid
    print(hi)
