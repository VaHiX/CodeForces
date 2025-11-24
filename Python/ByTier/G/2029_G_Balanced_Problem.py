# Problem: CF 2029 G - Balanced Problem
# https://codeforces.com/contest/2029/problem/G

"""
Algorithm: Dynamic Programming with Sliding Window Technique
Time Complexity: O(n * V^2)
Space Complexity: O(V^2)

The problem involves maximizing the beauty of an array after performing prefix/suffix additions.
We use a difference array to track how many times each position was incremented by operations.
Then we compress consecutive equal values and use dynamic programming to compute the maximum beauty
for each value v from 1 to V.

Key techniques:
1. Difference array to efficiently apply prefix/suffix operations
2. Compression of consecutive equal values
3. Dynamic programming with states tracking maximum beauty for each value
4. Sliding window updates for efficiency
"""

import sys


def solve(it):
    inf = 10**18
    n = int(next(it))
    m = int(next(it))
    V = int(next(it))
    c = [int(next(it)) for _ in range(n)]
    a = [0] * n
    for _ in range(m):
        o = next(it)
        x = int(next(it))
        if o == b"L":  # Prefix addition
            a[0] += 1
            if x < n:
                a[x] -= 1
        else:  # Suffix addition
            x -= 1
            a[x] += 1
    # Convert difference array to actual values
    for i in range(1, n):
        a[i] += a[i - 1]
    # Cap values at V+1 to avoid overflow
    for i in range(n):
        if a[i] > V + 1:
            a[i] = V + 1
    # Compress consecutive equal values
    na = []
    nc = []
    l = 0
    while l < n:
        r = l
        s = 0
        while r < n and a[r] == a[l]:
            s += c[r]
            r += 1
        if a[l] <= V:
            na.append(a[l])
            nc.append(s)
        l = r
    a = na
    c = nc
    n = len(a)
    # Initialize answer array
    ans = [0] * (V + 1)
    # Set up DP tables - f[i][j] represents max beauty when value is i and total operations applied is j
    W = 2 * V + 1
    f = [[-inf] * W for _ in range(V + 1)]
    g = [[-inf] * W for _ in range(V + 1)]
    for i in range(V + 1):
        f[i][i] = 0
        g[i][i] = 0
    x = 0  # Current value in the processed segment
    for i in range(n):
        # Update x to match current segment value a[i]
        while x < a[i]:
            x += 1
            prev = f[x - 1]
            cur = f[x]
            for j in range(1, W):
                v = prev[j - 1]
                if v > cur[j]:
                    cur[j] = v
        while x > a[i]:
            x -= 1
            nxt = g[x + 1]
            cur = g[x]
            for j in range(1, W):
                v = nxt[j - 1]
                if v > cur[j]:
                    cur[j] = v
        # Process current segment
        row_f = f[a[i]]
        row_g = g[a[i]]
        for j in range(W):
            gj = row_g[j]
            if gj > row_f[j]:
                row_f[j] = gj
            if row_f[j] > -inf:
                row_f[j] += c[i]
            dpj = row_f[j]
            if dpj > -inf:
                # Calculate target value v based on current state
                u = (j + a[i] + 1) // 2
                if u <= V:
                    if dpj > ans[u]:
                        ans[u] = dpj
        for j in range(W):
            v = row_f[j]
            if v > g[a[i]][j]:
                g[a[i]][j] = v  # Update g with new values
    # Propagate results backwards
    out = []
    for v in range(1, V + 1):
        if ans[v - 1] > ans[v]:
            ans[v] = ans[v - 1]
        out.append(str(ans[v]))
    sys.stdout.write(" ".join(out) + "\n")


if __name__ == "__main__":
    data = sys.stdin.buffer.read().split()
    it = iter(data)
    t = int(next(it))
    for _ in range(t):
        solve(it)


# https://github.com/VaHiX/CodeForces/