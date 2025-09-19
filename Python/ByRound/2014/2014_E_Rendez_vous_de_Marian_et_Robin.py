# Contest 2014, Problem E: Rendez-vous de Marian et Robin
# URL: https://codeforces.com/contest/2014/problem/E

import heapq

for _ in range(int(input())):
    n,m,h = map(int, input().split())
    a = {int(w)-1 for w in input().split()}
    assert len(a) == h
    g = [{} for _ in range(n)]
    for _ in range(m):
        u,v,w = map(int, input().split())
        g[u-1][v-1] = w
        g[v-1][u-1] = w
    q = [(0,0,1,0),(0,1,1,n-1)]
    d = set()
    r = -1
    while q:
        t,p,h,u = heapq.heappop(q)
        if (p,h,u) in d:
            continue
        d.add((p,h,u))
        if (1-p,0,u) in d or (1-p,1,u) in d:
            r = t
            break
        if u in a:
            h = 0
        for v,w in g[u].items():
            if (p,h,v) not in d:
                heapq.heappush(q, (t+w//(2-h),p,h,v))
    print(r)