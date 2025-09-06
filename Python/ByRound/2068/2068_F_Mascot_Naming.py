# Contest 2068, Problem F: Mascot Naming
# URL: https://codeforces.com/contest/2068/problem/F

import sys

input = sys.stdin.readline

n = int(input())
ss = [input().rstrip("\n") for _ in range(n)]
frb = input().rstrip("\n")

Q, ans = [(i, 0) for i in range(n)], []
for char in frb:
    nQ = []
    add = 0
    for i, j in Q:
        end = ss[i].find(char, start=j)
        if end == -1:
            ans.append(ss[i][j:])
            continue
        ans.append(ss[i][j:end])
        add += 1
        if end + 1 < len(ss[i]):
            nQ.append((i, end + 1))
    if add:
        ans.append(char)
    Q = nQ

ans = "".join(ans)
assert len(ans) <= 1e6

k = 0
for char in ans:
    if k < len(frb) and frb[k] == char:
        k += 1
if k < len(frb):
    print("YES")
    print(ans)
else:
    print("NO")
