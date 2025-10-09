# Contest 2045, Problem L: Buggy DFS
# URL: https://codeforces.com/contest/2045/problem/L

K = int(input())
if K % 2 == 1 and K <= 9:
    print(-1, -1)
    exit()

if K % 2 == 0:
    odd = False
    nk = K
else:
    odd = True
    nk = K - 11

L = 31630
from math import isqrt


def output(N, edge):
    print(N, len(edge))
    for i, j in edge:
        print(i + 1, j + 1)
    return


if nk <= 2 * L:
    N = nk // 2 + 1
    edge = []
    for i in range(N - 1):
        edge.append((i, i + 1))
    if odd:
        edge.append((0, N + 1))
        edge.append((0, N + 2))
        edge.append((N + 1, N + 2))
        edge.append((N, N + 1))
        N += 3
    output(N, edge)
    exit()

A = []
nk -= 2 * L
while nk > 0:
    a = isqrt(nk)
    if a * (a + 1) <= nk:
        A.append(a)
        nk -= a * (a + 1)
    else:
        A.append(a - 1)
        nk -= a * (a - 1)

N = L + 1 + len(A)
edge = []
edge.append((0, len(A) + 1))
for i in range(L - 1):
    edge.append((len(A) + 1 + i, len(A) + 2 + i))
for i in range(len(A)):
    ai = A[i]
    for j in range(ai):
        edge.append((i + 1, len(A) + j + 1))

if odd:
    edge.append((0, N + 1))
    edge.append((0, N + 2))
    edge.append((N + 1, N + 2))
    edge.append((N, N + 1))
    N += 3

output(N, edge)
