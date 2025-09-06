# Contest 2040, Problem D: Non Prime Tree
# URL: https://codeforces.com/contest/2040/problem/D

from collections import defaultdict
import sys
input = sys.stdin.readline

def solve():
    n = int(input().strip())
    edges = defaultdict(list)
    for _ in range(n - 1):
        a, b = map(int, input().split())
        edges[a - 1].append(b - 1)
        edges[b - 1].append(a - 1)
    
    result = [0] * n
    val = 1
    result[0] = val
    stack = [(0, -1)]
    while stack:
        node, parent = stack.pop()
        for adj in edges[node]:
            if adj == parent:
                continue
            result[adj] = val + 1
            while (result[adj] - result[node] > 1 and
                  (result[adj] - result[node]) % 2 == 1 or result[adj] - result[node] == 2):
                result[adj] += 1
            val = result[adj]
            stack.append((adj, node))

    print(*result, sep=' ')


T = int(input().strip())
for _ in range(T):
    solve()