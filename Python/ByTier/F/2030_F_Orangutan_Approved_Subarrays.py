# Contest 2030, Problem F: Orangutan Approved Subarrays
# URL: https://codeforces.com/contest/2030/problem/F

import sys, os, io

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def update(i, x):
    i ^= l1
    tree[i] = x
    i >>= 1
    while i:
        tree[i] = max(tree[i << 1], tree[i << 1 ^ 1])
        i >>= 1
    return


def get_max(s, t):
    s, t = s ^ l1, t ^ l1
    ans = 0
    while s <= t:
        if s & 1:
            ans = max(ans, tree[s])
            s += 1
        s >>= 1
        if not t & 1:
            ans = max(ans, tree[t])
            t -= 1
        t >>= 1
    return ans


t = int(input())
ans = []
for _ in range(t):
    n, q = map(int, input().split())
    a = [0] + list(map(int, input().split()))
    nx, u = [0] * (n + 1), [0] * (n + 1)
    for i in range(n, 0, -1):
        j = a[i]
        if u[j]:
            nx[i] = u[j]
        u[j] = i
    l1 = pow(2, (n + 1).bit_length())
    l2 = 2 * l1
    tree = [0] * l2
    ng = [0] * (n + 1)
    for l in range(1, n + 1):
        if not nx[l]:
            continue
        r = nx[l]
        ng[r] = get_max(l + 1, r - 1)
        update(r, l)
    for i in range(1, n + 1):
        ng[i] = max(ng[i], ng[i - 1])
    for _ in range(q):
        l, r = map(int, input().split())
        ans0 = "YES" if ng[r] < l else "NO"
        ans.append(ans0)
sys.stdout.write("\n".join(ans))
