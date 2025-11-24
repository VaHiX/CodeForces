# Problem: CF 1797 E - Li Hua and Array
# https://codeforces.com/contest/1797/problem/E

"""
Algorithm: 
This code solves a problem involving Euler's totient function φ and range operations on an array.
It uses a segment tree with binary lifting technique to efficiently process range updates and queries.
The key idea is to precompute the number of steps needed to reduce each number to 1 using φ function,
and build a data structure to answer queries about minimum operations needed to make a range equal.

Time Complexity: O(n log n + m log^2 n)
Space Complexity: O(n log n)

Approach:
1. Precompute φ(x) for all values up to max(a) using sieve-like method
2. Build a graph to represent the φ path from each number to 1  
3. Use binary lifting (segment tree with range minimum query) for efficient range operations
4. Process update and query operations on the array

The code handles two types of operations:
- Type 1: Update elements in a range by applying φ function
- Type 2: Find minimum changes to make elements in range equal
"""
import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def make_graph():
    s = [0] * (l + 3)
    for i in range(1, n + 1):
        v = a[i]
        while v ^ 1:  # while v != 1
            s[v + 2] += 1  # count path length
            v = x[v]  # go to next in φ path
        s[v + 2] += 1
    for i in range(3, l + 3):
        s[i] += s[i - 1]  # prefix sum for indexing
    G = [0] * s[-1]  # graph array
    for i in range(1, n + 1):
        v = a[i]
        while v ^ 1:  # while v != 1
            j = v + 1
            G[s[j]] = i  # store index
            s[j] += 1  # move pointer
            v = x[v]  # move to next in φ path
        j = v + 1
        G[s[j]] = i
        s[j] += 1
    return G, s


def f(u, v):
    return u * z + v  # coordinate compression for 2D data structure


def get_sum0(i):
    s = 0
    while i > 0:
        s += tree[i]  # prefix sum in BIT
        i -= i & -i
    return s


def get_sum(s, t):
    ans = 0 if s > t else get_sum0(t) - get_sum0(s - 1)  # range sum using BIT
    return ans


def add(i, x):
    while i < len(tree):  # update BIT
        tree[i] += x
        i += i & -i


def update(i, x):
    i += l1  # update segment tree
    mi[i] = x
    i //= 2
    while i:
        mi[i] = min(mi[2 * i], mi[2 * i + 1])
        i //= 2
    return


def get_min(s, t):
    s, t = s + l1, t + l1  # get minimum in segment tree
    ans = inf
    while s <= t:
        if s % 2 == 0:
            s //= 2
        else:
            ans = min(ans, mi[s])
            s = (s + 1) // 2
        if t % 2 == 1:
            t //= 2
        else:
            ans = min(ans, mi[t])
            t = (t - 1) // 2
    return ans


def get_root(s):
    v = []
    while not s == root[s]:
        v.append(s)
        s = root[s]
    for i in v:  # path compression
        root[i] = s
    return s


def unite(s, t):
    rs, rt = get_root(s), get_root(t)
    if not rs ^ rt:  # same root
        return
    if rank[s] == rank[t]:
        rank[rs] += 1
    if rank[s] >= rank[t]:
        root[rt] = rs
        size[rs] += size[rt]
    else:
        root[rs] = rt
        size[rt] += size[rs]
    ma[get_root(s)] = max(ma[rs], ma[rt])
    return


def same(s, t):
    return True if get_root(s) == get_root(t) else False


def get_size(s):
    return size[get_root(s)]


n, m = map(int, input().split())
a = [0] + list(map(int, input().split()))
l = max(a) + 5  # max value in array + padding
x = [i for i in range(l + 1)]  # φ values
for i in range(2, l + 1):
    if x[i] ^ i:  # if x[i] != i then already processed
        continue
    for j in range(i, l, i):  # sieve-style processing
        x[j] //= i
        x[j] *= i - 1  # φ function calculation
G, s0 = make_graph()  # build graph from φ paths
dist = [-1] * (l + 1)
dist[1] = 0
for i in range(2, l + 1):
    dist[i] = dist[x[i]] + 1  # calculate depth for each number
z = max(dist) + 2  # depth limit
r0 = [-1] * (z * (n + 1))  # 2D array for binary lifting
now = [0] * (n + 1)
for i in range(1, l + 1):
    if s0[i] == s0[i + 1]:  # skip if no nodes
        continue
    st = []
    for v in range(s0[i], s0[i + 1]):  # for all nodes in current level
        st.append(G[v])
        if len(st) > 1 and st[-2] + 1 < st[-1]:  # if previous element is less than current
            for j in st[:-1]:  # update r0 for all except last
                r0[f(j, now[j])] = st[-2]
                now[j] += 1
            st = [G[v]]  # reset stack
    for j in st:
        r0[f(j, now[j])] = st[-1]
        now[j] += 1
tree = [0] * (n + 5)  # BIT for prefix sum
for i in range(1, n + 1):
    tree[i] = dist[a[i]]  # initialize BIT with depths
for i in range(1, n + 5):
    j = i + (i & -i)
    if j < n + 5:
        tree[j] += tree[i]  # BIT construction
l1 = pow(2, (n + 1).bit_length())  # segment tree size
l2 = 2 * l1
inf = pow(10, 9) + 1  # infinity
mi = [inf] * l2  # segment tree for range min
for i in range(1, n + 1):
    mi[i + l1] = dist[a[i]]  # initialize leaves
for i in range(l1 - 1, 0, -1):  # build segment tree
    mi[i] = min(mi[2 * i], mi[2 * i + 1])
root = [i for i in range(n + 1)]  # union-find structure
rank = [1 for _ in range(n + 1)]
size = [1 for _ in range(n + 1)]
ma = [i for i in range(n + 1)]  # max index in component
for i in range(1, n):
    if a[i] == a[i + 1] == 1:  # if value is 1, union them
        unite(i, i + 1)
ans = []
for _ in range(m):
    t, l, r = map(int, input().split())
    if t == 1:  # update operation
        if a[l] == 1:
            l = ma[get_root(l)] + 1
        while l <= r:
            a[l] = x[a[l]]  # apply φ function
            add(l, -1)  # BIT update
            update(l, dist[a[l]])  # segment tree update
            if a[l] == 1:  # if result is 1
                for i in [l - 1, l + 1]:  # union with nearby 1s
                    if 0 < i <= n and a[i] == 1:
                        unite(i, l)
            if l < n and a[l + 1] == 1:  # if next element is 1, skip it
                l = ma[get_root(l + 1)] + 1
            else:
                l += 1
    else:  # query operation
        d = 0
        while r <= r0[f(l, d + 1)]:  # binary search for depth
            d += 1
        d = min(d, get_min(l, r))  # minimum depth in range
        ans0 = get_sum(l, r) - (r - l + 1) * d  # calculate result
        ans.append(ans0)
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/