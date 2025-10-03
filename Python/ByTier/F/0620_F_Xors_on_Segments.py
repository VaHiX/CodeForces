# Contest 620, Problem F: Xors on Segments
# URL: https://codeforces.com/contest/620/problem/F

import sys, os, io

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v, w):
    return (u * z + v) * z + w


def update1(x, c):
    i = x ^ l1
    tree1[i], color1[i] = x, c
    i >>= 1
    for _ in range(w):
        j, k = i << 1, i << 1 ^ 1
        if color1[j] ^ c:
            tree1[i] = tree1[k]
        elif color1[k] ^ c:
            tree1[i] = tree1[j]
        else:
            tree1[i] = min(tree1[j], tree1[k])
        color1[i] = c
        i >>= 1
    return


def update2(x, c):
    i = x ^ l1
    tree2[i], color2[i] = x, c
    i >>= 1
    for _ in range(w):
        j, k = i << 1, i << 1 ^ 1
        if color2[j] ^ c:
            tree2[i] = tree2[k]
        elif color2[k] ^ c:
            tree2[i] = tree2[j]
        else:
            tree2[i] = max(tree2[j], tree2[k])
        color2[i] = c
        i >>= 1
    return


def xor_max1(x, r, c):
    i = 1
    if color1[i] ^ c or not tree1[i] < r:
        return 0
    for _ in range(w):
        j, k = i << 1, i << 1 ^ 1
        if color1[j] ^ c:
            f0 = 1
        elif color1[k] ^ c:
            f0 = 0
        elif tree1[k] < r and x ^ x0[tree1[j]] < x ^ x0[tree1[k]]:
            f0 = 1
        else:
            f0 = 0
        i = i << 1 ^ f0
    return x ^ x0[i ^ l1]


def xor_max2(x, l, c):
    i = 1
    if color2[i] ^ c or not tree2[i] > l:
        return 0
    for _ in range(w):
        j, k = i << 1, i << 1 ^ 1
        if color2[j] ^ c:
            f0 = 1
        elif color2[k] ^ c:
            f0 = 0
        elif tree2[j] > l and x ^ x0[tree2[k]] < x ^ x0[tree2[j]]:
            f0 = 0
        else:
            f0 = 1
        i = i << 1 ^ f0
    return x ^ x0[i ^ l1]


n, m = map(int, input().split())
a = list(map(int, input().split()))
x0 = [0] * (max(a) + 5)
for i in range(1, len(x0)):
    x0[i] = x0[i - 1] ^ i
l0, r0 = [0] * m, [0] * m
m1 = 876
m2 = n // m1 + 3
q = []
s0 = [0] * (m2 + 1)
ans = [0] * m
z = max(m, n) + 5
for i in range(m):
    l, r = map(int, input().split())
    l, r = l - 1, r - 1
    if l // m1 == r // m1:
        ans0 = 0
        for j in range(l, r + 1):
            u = a[j]
            for k in range(j, r + 1):
                v = a[k]
                ans1 = x0[u - 1] ^ x0[v] if u <= v else x0[u] ^ x0[v - 1]
                ans0 = max(ans0, ans1)
        ans[i] = ans0
        continue
    l0[i], r0[i] = l, r
    x = l // m1
    q.append(f(x, r, i))
    s0[x + 1] += 1
ma = [0] * n
for i in range(n):
    mai, u = 0, a[i]
    for j in range(i, min(i // m1 * m1 + m1, n)):
        v = a[j]
        maj = x0[u - 1] ^ x0[v] if u <= v else x0[u] ^ x0[v - 1]
        mai = max(mai, maj)
    ma[i] = mai
for i in range(n - 2, -1, -1):
    if (i + 1) % m1:
        ma[i] = max(ma[i], ma[i + 1])
for i in range(1, m2 + 1):
    s0[i] += s0[i - 1]
w = (max(a) + 1).bit_length()
l1 = pow(2, w)
l2 = 2 * l1
inf = pow(10, 9) + 1
tree1, color1 = [inf] * l2, [-1] * l2
tree2, color2 = [-inf] * l2, [-1] * l2
q.sort()
for c in range(m2):
    if s0[c] == s0[c + 1]:
        continue
    r = (c + 1) * m1
    c10, c11, c20, c21 = inf, inf, -inf, -inf
    ans0 = 0
    for i in range(s0[c], s0[c + 1]):
        j = q[i] % z
        ll, rr = l0[j], r0[j]
        while r <= rr:
            ar = a[r]
            x1, x2 = x0[ar], x0[ar - 1]
            if x1 > 1:
                update2(ar, c)
            elif x1 == 0:
                c20 = max(c20, ar)
            elif x1 == 1:
                c21 = max(c21, ar)
            if x2 > 1:
                update1(ar - 1, c)
            elif x2 == 0:
                c10 = min(c10, ar - 1)
            elif x2 == 1:
                c11 = min(c11, ar - 1)
            ans0 = max(ans0, xor_max1(x1, ar, c), xor_max2(x2, ar - 1, c))
            if c10 < ar:
                ans0 = max(ans0, x1)
            if c11 < ar:
                ans0 = max(ans0, x1 ^ 1)
            if ar - 1 < c20:
                ans0 = max(ans0, x2)
            if ar - 1 < c21:
                ans0 = max(ans0, x2 ^ 1)
            r += 1
        ans1 = max(ma[ll], ans0)
        for l in range(ll, (c + 1) * m1):
            al = a[l]
            x1, x2 = x0[al], x0[al - 1]
            ans1 = max(ans1, xor_max1(x1, al, c), xor_max2(x2, al - 1, c))
            if c10 < al:
                ans1 = max(ans1, x1)
            if c11 < al:
                ans1 = max(ans1, x1 ^ 1)
            if al - 1 < c20:
                ans1 = max(ans1, x2)
            if al - 1 < c21:
                ans1 = max(ans1, x2 ^ 1)
        ans[j] = ans1
sys.stdout.write("\n".join(map(str, ans)))
