# Problem: CF 2152 F - Triple Attack
# https://codeforces.com/contest/2152/problem/F

"""
Algorithm: Dynamic Programming with Binary Lifting
Purpose: For each query interval [l, r], find the maximum size of a subset of timestamps that is "safe"
         (no three timestamps form a triplet with max - min <= z).

Time Complexity: 
- Preprocessing: O(n * log(n))  
- Each Query: O(log(n))
- Overall: O(n * log(n) + q * log(n)) where q is number of queries

Space Complexity: O(n * log(n))
"""

LOG = 18
for _ in range(int(input())):
    n, z = [int(t) for t in input().split()]
    a = [int(t) for t in input().split()]

    # nxt[i]: smallest index j such that a[j] > a[i] + z
    R = 0
    nxt = []
    for L in range(n):
        while R < n and a[R] <= a[L] + z:
            R += 1
        nxt.append(R)
    nxt.append(n)

    # Binary lifting for jump table
    jump = [nxt]
    for _ in range(LOG):
        last = jump[-1]
        jump.append([last[last[i]] for i in range(n + 1)])

    # depth[i]: depth of node i in the tree
    depth = [0] * (n + 1)
    for i in range(n - 1, -1, -1):
        depth[i] = depth[nxt[i]] + 1

    # dist(i, R): find number of steps needed to reach R from i using jump
    def dist(i, R):
        if i >= R:
            return 0
        x = 1
        for j in range(LOG - 1, -1, -1):
            if jump[j][i] < R:
                i = jump[j][i]
                x += 1 << j
        return x

    # lca(i, j): find LCA of two nodes in the tree
    def lca(x, y):
        if depth[x] < depth[y]:
            x, y = y, x
        for j in range(LOG - 1, -1, -1):
            if depth[jump[j][x]] >= depth[y]:
                x = jump[j][x]
        if x == y:
            return y
        for j in range(LOG - 1, -1, -1):
            if jump[j][x] != jump[j][y]:
                x = jump[j][x]
                y = jump[j][y]
        return nxt[x]

    # dub[i]: index of first node after i that is not in the same safe region
    # gain[i]: total gain up to index i
    dub = [n] * (n + 1)
    gain = [0] * (n + 1)
    for i in range(n - 1, -1, -1):
        m = lca(i, i + 1)
        dub[i] = m
        gain[i] = gain[m] + dist(i, m) + dist(i + 1, m)

    # Binary lifting for fast queries
    fast = [dub]
    for _ in range(LOG):
        last = fast[-1]
        fast.append([last[last[i]] for i in range(n + 1)])

    for _ in range(int(input())):
        l, r = [int(t) for t in input().split()]
        l -= 1
        if r - l <= 2:
            print(r - l)
            continue

        # Find optimal point to stop using binary lifting
        t = l
        for j in range(LOG - 1, -1, -1):
            if fast[j][t] < r:
                t = fast[j][t]
        # Calculate and output the answer
        ans = gain[l] - gain[t] + dist(t, r) + dist(t + 1, r)
        print(ans)


# https://github.com/VaHiX/CodeForces/