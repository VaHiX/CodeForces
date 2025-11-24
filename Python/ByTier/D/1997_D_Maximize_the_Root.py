# Problem: CF 1997 D - Maximize the Root
# https://codeforces.com/contest/1997/problem/D

"""
Algorithm: Dynamic Programming on Tree
Time Complexity: O(n)
Space Complexity: O(n)

The problem involves maximizing the value at the root of a tree by performing operations
that transfer value from a vertex to its descendants. The key insight is to use a 
post-order traversal to compute the minimum value that can be "reserved" at each node
to ensure non-negativity of all values during operations. 

For each node, we calculate the minimum value that must be preserved at that node 
so that all its descendants can be reduced to non-negative values, then compute what 
can be transferred to the parent.
"""

import sys


def inp():
    return sys.stdin.readline().strip()


def inin(x):
    if not x:
        return not x
    if x == 1:
        return int(inp())
    else:
        return map(int, inp().split())


def intarr():
    return list(inin(2))


def chrarr():
    return list(inp().split())


def lines(m):
    lines = [""] * m
    for i in range(m):
        lines[i] = list(inp().split())
    return lines


def intlines(m):
    lines = [0] * m
    for i in range(m):
        lines[i] = intarr()
    return lines


def pr(*a, sep=" ", end="\n", **d):
    h = list(d.keys())
    print(*a, *h, sep=sep, end=end)


def no(*a):
    pr("NO", *a)


def yes(*a):
    pr("YES", *a)


def No(*a):
    pr("No", *a)


def Yes(*a):
    pr("Yes", *a)


def ali(*a):
    pr("Alice", *a)


def bob(*a):
    pr("Bob", *a)


def pas(*a):
    pr("PASS", *a)


def pref(x):
    y = x.copy()
    for i in range(1, len(x)):
        y[i] += y[i - 1]
    return y


def suff(x):
    return pref(x[::-1])[::-1]


def binexp(a, b, res=1, mod=0):
    while b:
        if b & 1:
            res *= a
        a *= a
        b >>= 1
        if mod:
            a %= mod
            res %= mod
    return res


def test(t):
    while t:
        solve(t)
        t -= 1


def solve(t):
    n = inin(1)
    val = [0] + intarr()  # val[0] is dummy
    par = [0, 0] + intarr()
    edges = [list() for _ in range(n + 1)]
    for i in range(2, n + 1):
        x = par[i]
        edges[x].append(i)
    minn = [10**10] * (n + 1)
    stack = [1]
    mark = [0] * (n + 1)
    while stack:
        node = stack[-1]
        if mark[node]:
            stack.pop()
            if edges[node] == []:
                minn[node] = val[node]  # Leaf node
            else:
                Min = min(minn[child] for child in edges[node])
                if node == 1:
                    # Root node, we can transfer all excess to it
                    minn[node] = Min + val[node]
                    continue
                # For non-root, half of the excess can be passed to parent
                minn[node] = (Min + val[node]) // 2 if val[node] < Min else Min
        else:
            mark[node] = True
            for child in edges[node]:
                stack.append(child)
    pr(minn[1])


test(inin(1))


# https://github.com/VaHiX/CodeForces/