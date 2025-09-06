# Contest 930, Problem A: Peculiar apple-tree
# URL: https://codeforces.com/contest/930/problem/A

import sys
input = sys.stdin.buffer.readline 

def process(n, A):
    depth = [0 for i in range(n+1)]
    depth[1] = 0
    for i in range(2, n+1):
        pi = A[i-2]
        depth[i] = depth[pi]+1
    d = {}
    for i in range(1, n+1):
        x = depth[i]
        if x not in d:
            d[x] = 0
        d[x] = (d[x]+1) % 2
    return sum(d.values())

n = int(input())
A = [int(x) for x in input().split()]
print(process(n, A))
        