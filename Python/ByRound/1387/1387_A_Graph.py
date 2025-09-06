# Contest 1387, Problem A: Graph
# URL: https://codeforces.com/contest/1387/problem/A

from sys import stdin
input=stdin.readline
n,m=map(int,input().split())
g=[[] for _ in range(n)]
for _ in range(m):
    u,v,w=map(int,input().split())
    u-=1
    v-=1
    g[u].append((w*2,v))
    g[v].append((w*2,u))
vis=[0]*n
val=[0]*n
k=[0]*n
b=[0]*n
for i in range(n):
    if vis[i]:
        continue
    q=[i]
    vis[i]=1
    x=0
    nx=0
    k[i]=1
    t=0
    while t<len(q):
        u=q[t]
        t+=1
        for w,v in g[u]:
            if not vis[v]:
                vis[v]=1
                k[v]=-k[u]
                b[v]=w-b[u]
                q.append(v)
            elif nx:
                if k[u]*x+b[u]+k[v]*x+b[v]!=w:
                    print("NO")
                    exit()
            else:
                if k[u]==-k[v]:
                    if b[u]+b[v]==w:
                        continue
                    else:
                        print("NO")
                        exit()
                nx=1
                x=(w-b[u]-b[v])//(k[u]+k[v])
    if not nx:
        ps=[-k[i]*b[i] for i in q]
        ps.sort()
        x=ps[len(ps)//2]
    for i in q:
        val[i]=k[i]*x+b[i]
print("YES")
print(*[i/2 for i in val])