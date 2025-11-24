# Problem: CF 1823 F - Random Walk
# https://codeforces.com/contest/1823/problem/F

"""
Algorithm: Tree Dynamic Programming with Expected Value Calculation
Approach:
- This is a random walk problem on a tree where we compute expected values of counters at each node.
- We perform a topological traversal of the tree, starting from the target node t.
- For each node, we compute two values:
  - a[u]: The expected number of times we visit node u during the walk, given that we start from node u.
  - b[u]: The expected number of times we visit node u during the walk, given that we start from parent of u.
- These values are used recursively to build the solution backwards.

Time Complexity: O(n)
Space Complexity: O(n)

The key idea is to model this as a system of linear equations and solve using topological ordering.
"""

import sys

input = sys.stdin.readline

MOD = 998244353

def inv(n):
    if n == 0:
        return 0
    return pow(n, -1, MOD)

tc = 1
for _ in range(tc):

    n, s, t = map(int, input().split())

    adj = [[] for i in range(n + 1)]
    for i in range(n - 1):
        u, v = map(int, input().split())
        adj[u].append(v)
        adj[v].append(u)
    
    # Arrays to store the expected values for each node
    a = [0] * (n + 1)
    b = [0] * (n + 1)
    
    # Topological order traversal
    topo = []
    par = [0] * (n + 1)
    st = [t]
    while st:
        at = st.pop()
        topo.append(at)
        for nb in adj[at]:
            if nb == par[at]:
                continue
            par[nb] = at
            st.append((nb))
    
    # Reverse to get correct topological order
    topo = topo[::-1]
    
    # Compute a and b arrays using bottom-up dynamic programming
    for at in topo:
        p = par[at]
        xa = 0
        xb = 0
        if at == s:
            xb = 1
        for nb in adj[at]:
            if nb == p:
                continue
            # Accumulate contributions to xa and xb
            xa += (inv(len(adj[nb])) * a[nb]) % MOD
            xb += (inv(len(adj[nb])) * b[nb]) % MOD
        
        xa = (1 - xa) % MOD  # Subtract from 1 to get the correct contribution
        
        if p != 0:
            a[at] = inv(xa) * inv(len(adj[p]))
        a[at] %= MOD
        b[at] = inv(xa) * xb
        b[at] %= MOD

    # Backtrack to calculate final answer
    topo = topo[::-1]
    ans = [0] * (n + 1)
    for u in topo:
        p = par[u]
        ans[u] = a[u] * ans[p] + b[u]
        ans[u] %= MOD
    
    # Set the target node's answer to 1
    ans[t] = 1
    print(*ans[1:])


# https://github.com/VaHiX/CodeForces/