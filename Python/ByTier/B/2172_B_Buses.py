# Problem: CF 2172 B - Buses
# https://codeforces.com/contest/2172/problem/B

"""
Code Purpose:
This code solves the problem of determining the minimum time for each person to reach the end of a road, 
considering that they can either walk or take buses that move at a constant speed. The solution uses a 
sweep line technique where we process events (people's positions and bus start/end positions) in order.

Approach:
1. For each person, we calculate the minimum time to reach the end by either:
   - Walking the entire distance
   - Taking a bus (if available at their current position), riding until the bus destination, and then walking the rest.
2. We use a sweep line technique by sorting all relevant positions and processing them.
3. We maintain the minimum time to reach the end from a given position and update this information as we process events.

Time Complexity: O((n + m) * log(n + m)) due to sorting the events and processing them once.
Space Complexity: O(n + m) for storing bus information, positions, and the sweep line events.
"""

import sys


def inp():
    return sys.stdin.readline().strip()


def inin(x=1):
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
    n, m, L, x, y = inin(5)
    bus = dict()
    while n:
        n -= 1
        l, r = inin(2)
        if l in bus:
            bus[l] = max(bus[l], r)  # Keep the maximum destination for the same start point
        else:
            bus[l] = r
    ps = [inin() for _ in range(m)]
    hmm = sorted(ps + list(bus.keys()))  # Sweep line events
    mi = L + 2  # Initialize minimum time, larger than any possible time
    ans = dict()
    for i in hmm:
        if i in bus:
            # If this is a bus start point, update the minimum possible time from here
            # Calculate time to reach end if we take this bus, get off at its destination, and then walk
            mi = min(mi, (L - bus[i]) / y + (bus[i] - i) / x)
        ans[i] = min(mi, (L - i) / y)  # Minimum time from this point considering either walking or taking a bus (if possible)
    for x in ps:
        pr(ans[x])


test(inin(0))


# https://github.com/VaHiX/CodeForces/