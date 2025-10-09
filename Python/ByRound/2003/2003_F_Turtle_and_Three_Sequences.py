# Contest 2003, Problem F: Turtle and Three Sequences
# URL: https://codeforces.com/contest/2003/problem/F

import random
import sys, os, io
input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

def f(u, v):
    return u << m ^ v

def g(u, v):
    return u << 20 ^ v

def update(i, j, x):
    while i < n + 1:
        tree[f(i, j)] = max(tree[f(i, j)], x)
        i += i & -i
    return

def get_max(i, j, k):
    ans = 0
    while i > 0:
        ans = max(ans, tree[f(i, j)])
        i -= i & -i
    ans = ans & 0xfffff if ans >> 20 == k else -inf
    return ans

n, m = map(int, input().split())
a = list(map(int, input().split()))
b = list(map(int, input().split()))
c = list(map(int, input().split()))
pow2 = [1]
for _ in range(m):
    pow2.append(2 * pow2[-1])
l = pow2[m]
x = [0] * (n + 1)
inf = pow(10, 9) + 1
ans = -inf
tree = [0] * ((n + 1) << m)
for w in range(1, 123):
    for i in range(1, n + 1):
        x[i] = pow2[random.randint(0, m - 1)]
    update(1, 0, g(w, 0))
    for i, j, k in zip(a, b, c):
        u = x[j]
        for v in range(l):
            if u & v:
                continue
            ma = get_max(i, v, w) + k
            p = tree[f(i, u ^ v)] & 0xfffff if tree[f(i, u ^ v)] >> 20 == w else -inf
            if 0 <= ma > p:
                update(i, u ^ v, g(w, ma))
    ans = max(ans, get_max(n, l - 1, w))
ans = max(ans, -1)
print(ans)