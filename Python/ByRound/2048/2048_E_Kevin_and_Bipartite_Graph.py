# Contest 2048, Problem E: Kevin and Bipartite Graph
# URL: https://codeforces.com/contest/2048/problem/E

import sys

input = sys.stdin.read
data = input().split()
t = int(data[0])
results = []
index = 1
for i in range(t):
    n, m = map(int, data[index : index + 2])
    index += 2
    if m >= 2 * n:
        results.append("NO")
    else:
        results.append("YES")
        coloring = []
        for i in range(2 * n):
            row = []
            for j in range(m):
                row.append(((i + j) % (2 * n)) // 2 + 1)
            coloring.append(" ".join(map(str, row)))
        results.extend(coloring)

sys.stdout.write("\n".join(results) + "\n")
