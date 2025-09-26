# Contest 2070, Problem F: Friends and Pizza
# URL: https://codeforces.com/contest/2070/problem/F

import sys

input = lambda: sys.stdin.readline()[:-1]
ni = lambda: int(input())
na = lambda: list(map(int, input().split()))
yes = lambda: print("yes")
Yes = lambda: print("Yes")
YES = lambda: print("YES")
no = lambda: print("no")
No = lambda: print("No")
NO = lambda: print("NO")
#######################################################################


def popcount(n):
    c = (n & 0x5555555555555555) + ((n >> 1) & 0x5555555555555555)
    c = (c & 0x3333333333333333) + ((c >> 2) & 0x3333333333333333)
    c = (c & 0x0F0F0F0F0F0F0F0F) + ((c >> 4) & 0x0F0F0F0F0F0F0F0F)
    c = (c & 0x00FF00FF00FF00FF) + ((c >> 8) & 0x00FF00FF00FF00FF)
    c = (c & 0x0000FFFF0000FFFF) + ((c >> 16) & 0x0000FFFF0000FFFF)
    c = (c & 0x00000000FFFFFFFF) + ((c >> 32) & 0x00000000FFFFFFFF)
    return c


n, m = na()
S = input().split()
A = 0
B = 0
a = na()
for i in range(n):
    if a[i] % 2 == 1:
        A += 1 << i
    else:
        B += 1 << i
b = [0] * (1 << n)
T = []
for i in range(m):
    r = 0
    for x in S[i]:
        r += 1 << (ord(x) - 65)
    T.append(r)
    b[r] += 1

s = n + 1
popcnt = [popcount(A & i) for i in range(1 << n)]


# print(popcnt)
def subset_convolution(a, b):
    n = 0
    while 1 << n < max(len(a), len(b)):
        n += 1
    N = n + 1

    bufA = [0] * (N << n)
    for i, x in enumerate(a):
        bufA[popcnt[i] + i * N] = x
    for w in range(1, (1 << n) + 1):
        d = 0
        while not 1 << d & w:
            W = N * (w - (1 << d))
            dd = N << d
            for i in range(N * (w - (2 << d)), W):
                bufA[i + dd] = bufA[i + dd] + bufA[i]
            d += 1
    bufB = [0] * (N << n)
    for i, x in enumerate(b):
        bufB[popcnt[i] + i * N] = x
    for w in range(1, (1 << n) + 1):
        d = 0
        while not 1 << d & w:
            W = N * (w - (1 << d))
            dd = N << d
            for i in range(N * (w - (2 << d)), W):
                bufB[i + dd] = bufB[i + dd] + bufB[i]
            d += 1
    for i in range(1 << n):
        I = i * N
        Q = [0] * N
        for ja in range(popcnt[i] + 1):
            x = min(n - ja, popcnt[i])
            for jb in range(popcnt[i] - ja, x + 1):
                Q[ja + jb] = Q[ja + jb] + bufA[ja + I] * bufB[jb + I]
        bufA[I : len(Q) + I] = Q
    for w in range(1, (1 << n) + 1):
        d = 0
        while not 1 << d & w:
            W = N * (w - (1 << d))
            dd = N << d
            for i in range(N * (w - (2 << d)), W):
                bufA[i + dd] = bufA[i + dd] - bufA[i]
            d += 1
    return [bufA[popcnt[i] + i * N] for i in range(1 << n)]


# g[x] = {x = i | j, i & j & A = 0} a[i] * b[j]
# rank(x) = popcount(x & A)
# x & y & A == 0 <==> rank(x) + rank(y) == rank(x|y)
# print(b)
ans = subset_convolution(b, b)
# print(*ans)

# print(ans)
# print(T)
for i in range(m):
    if T[i] & A == 0:
        ans[T[i]] -= 1

res = [0] * (sum(a) + 1)

for i in range(1 << n):
    s = 0
    for j in range(n):
        if i >> j & 1 ^ 1:
            s += a[j]
    res[s] += ans[i]


print(*[x // 2 for x in res])
