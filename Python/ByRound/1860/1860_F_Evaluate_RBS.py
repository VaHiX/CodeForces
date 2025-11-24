# Problem: CF 1860 F - Evaluate RBS
# https://codeforces.com/contest/1860/problem/F

"""
Problem: Evaluate RBS
Algorithm: 
    - This problem involves determining if we can sort a set of bracket tuples such that they form a valid bracket sequence.
    - We use a geometric approach where each tuple (a, b, c) is treated as a point in a 2D plane.
    - For each pair of tuples, we compute the intersection point of their "lines" to determine orderings.
    - The approach checks valid orderings using a sweep-line like technique with coordinate compression.

Time Complexity: O(n^3 * log(n)) where n is the number of pairs of brackets (2n total tuples)
Space Complexity: O(n^2) for storing intermediate data structures
"""

import bisect
import io
import os
import sys
from collections import defaultdict

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def f(u, v, w, x):
    # Helper function to create a unique hash value for tuple (u,v,w,x)
    return u << 40 ^ v << 20 ^ w << 12 ^ x


def g(u, v):
    # Helper function to combine two indices into one value
    return u << 12 ^ v


t = int(input())
ans = []
for _ in range(t):
    n = int(input())
    a, b, c, x = [0] * (2 * n), [0] * (2 * n), [0] * (2 * n), [0] * (2 * n)
    for i in range(2 * n):
        a0, b0, c0 = input().rstrip().decode().split()
        a0, b0, c0 = int(a0), int(b0), ord(c0) & 1  # Convert char to 0 or 1
        a[i], b[i], c[i] = a0, b0, c0
        x[i] = f(a0, b0, c0, i)
    
    # Sort using custom hash and get indices
    u = [i & 0xFFF for i in sorted(x)]
    v = [0] * (2 * n)
    for i in range(2 * n):
        v[u[i]] = i
    
    # Find all intersection points of lines formed by tuples
    t1 = []
    for i in range(2 * n):
        ai, bi = a[i], b[i]
        for j in range(i + 1, 2 * n):
            aj, bj = a[j], b[j]
            if ai == aj or bi == bj:
                continue
            t0 = (ai - aj) / (bj - bi)
            if t0 > 0:
                t1.append(t0)
    
    t1.sort()  # Sort intersection points
    lt = len(t1)
    d = [0] * lt
    w = [i for i in range(lt)]
    
    # Map these intersection points to index pairs
    for i in range(2 * n):
        ai, bi = a[i], b[i]
        for j in range(i + 1, 2 * n):
            aj, bj = a[j], b[j]
            if ai == aj or bi == bj:
                continue
            t0 = (ai - aj) / (bj - bi)
            if t0 > 0:
                k = bisect.bisect_left(t1, t0)
                d[w[k]] = g(i, j)
                w[k] += 1
    
    # Precompute prefix sums for bracket counts
    s = [0] * (2 * n + 1)
    c = [c[u[i]] for i in range(2 * n)]
    for i in range(2 * n):
        s[i + 1] = s[i] + 1 if not c[i] else s[i] - 1
    
    cnt = [0] * (3 * n)
    for i in s:
        cnt[i] += 1
    
    y = [0] * (2 * n)
    ok = 0
    l = 0
    # Process each group of intersection points
    while l ^ lt and cnt[-1]:
        x = defaultdict(lambda: 0)
        r = w[l]
        for i in range(l, r):
            j, k = d[i] >> 12, d[i] & 0xFFF
            y[v[j]], y[v[k]] = j, k
            if v[j] < v[k]:
                x[v[j]] += 1
                x[v[k]] += 0
            else:
                x[v[j]] += 0
                x[v[k]] += 1
        l = r
        c1 = 0
        for i in x.keys():
            if i + 1 in x and x[i] >= x[i + 1]:
                if s[i + 1] == -1:
                    c1 += 1
            elif s[i + 1] < 0:
                c1 = -1
                break
        if c1 == cnt[-1]:
            ok = 1
            break
        st = []
        for i in sorted(x.keys()):
            st.append(y[i])
            if i + 1 in x and x[i] == x[i + 1]:
                continue
            while st:
                j = v[st.pop()]
                k = j + 1
                for _ in range(x[i]):
                    cnt[s[k]] -= 1
                    if c[j] < c[k]:
                        s[k] -= 2
                    elif c[j] > c[k]:
                        s[k] += 2
                    cnt[s[k]] += 1
                    u[j], u[k] = u[k], u[j]
                    c[j], c[k] = c[k], c[j]
                    v[u[j]], v[u[k]] = v[u[k]], v[u[j]]
                    j, k = j + 1, k + 1
    if not cnt[-1]:
        ok = 1
    ans0 = "YES" if ok else "NO"
    ans.append(ans0)
sys.stdout.write("\n".join(ans))


# https://github.com/VaHiX/CodeForces/