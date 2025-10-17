# Contest 2020, Problem D: Connect the Dots
# URL: https://codeforces.com/contest/2020/problem/D

import sys
input = sys.stdin.readline


def find(par, node):
    if par[node] != node:
        par[node] = find(par, par[node])
    return par[node]


def union(par, rank, node1, node2):
    root1 = find(par, node1)
    root2 = find(par, node2)

    if root1 != root2:
        if rank[root1] > rank[root2]:
            par[root2] = root1
        elif rank[root1] < rank[root2]:
            par[root1] = root2
        else:
            par[root2] = root1
            rank[root1] += 1


for i in range(int(input())):
    n,m = list(map(int, input().split()))
    l2=[[-1 for p in range(11)] for j in range(n)]
    rank = [0] * n
    par = [j for j in range(n)]
    for j in range(m):
        a,d,k = list(map(int, input().split()))
        if k!=0:
            # union(par, rank, a, a + d)
            l2[a-1][d]=max(l2[a-1][d],k)
    for j in range(n):
        for d in range(1,11):
            if l2[j][d]>0:
                union(par,rank,j,j+d)
                l2[j+d][d]=max(l2[j+d][d],l2[j][d]-1)
    #     print(l2)
    # print(par)
    result = set(find(par, j) for j in range(n))
    print(len(result))

