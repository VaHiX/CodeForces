# Contest 406, Problem A: Unusual Product
# URL: https://codeforces.com/contest/406/problem/A

import io, os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

n = int(input())

m = []
for _ in range(n):
    for i in list(map(int, input().split())):
        m.append(i)

prod = 0
for i in range(n):
    for j in range(n):
        prod = (prod + (m[i * n + j] * m[j * n + i]) % 2) % 2

q = int(input())
while q:
    ops = list(map(int, input().split()))
    if ops[0] == 1 or ops[0] == 2:
        prod = (prod + 1) % 2
    elif ops[0] == 3:
        print(prod, end="")
    q -= 1
print()
