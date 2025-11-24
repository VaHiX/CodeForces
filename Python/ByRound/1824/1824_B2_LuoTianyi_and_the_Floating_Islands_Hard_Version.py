# Problem: CF 1824 B2 - LuoTianyi and the Floating Islands (Hard Version)
# https://codeforces.com/contest/1824/problem/B2

"""
Code Purpose:
This code computes the expected number of good islands when k people are randomly placed on n distinct islands of a tree structure.
A good island is defined as one that minimizes the sum of distances to all k people. 
The approach uses tree DFS traversal and combinatorics to count valid configurations where a node is a good island.

Algorithms/Techniques:
- Tree DFS traversal with in-out time and subtree size tracking
- Combinatorial mathematics using precomputed factorials and modular inverse for binomial coefficients
- Modular arithmetic for handling large numbers and modular inverse using Fermat's little theorem

Time Complexity: O(n)
Space Complexity: O(n)

"""

import sys

input = sys.stdin.readline


class Binom:
    def __init__(self, n, mod):
        self.n = n
        self.mod = mod
        self.fact = [1, 1]        # Factorial values
        self.factinv = [1, 1]     # Inverse factorial values
        self.inv = [0, 1]         # Modular inverse values
        self._calc(n, mod)

    def _calc(self, n, mod):
        # Precompute factorials and their modular inverses
        for i in range(2, n + 1):
            self.fact.append((self.fact[-1] * i) % mod)
            self.inv.append((-self.inv[mod % i] * (mod // i)) % mod)
            self.factinv.append((self.factinv[-1] * self.inv[-1]) % mod)

    def comb(self, n, r):
        # Compute combination C(n, r) mod mod
        return (
            self.fact[n] * self.factinv[r] % self.mod * self.factinv[n - r] % self.mod
        )

    def perm(self, n, r):
        # Compute permutation P(n, r) mod mod
        return self.fact[n] * self.factinv[n - r] % self.mod


mod = 10**9 + 7
n, k = map(int, input().split())
graph = [[] for i in range(n + 1)]  # Adjacency list representation of the tree
for i in range(n - 1):
    u, v = map(int, input().split())
    graph[u].append(v)
    graph[v].append(u)

cnt = [0] * (n + 1)  # cnt[i] stores the number of people in subtree rooted at i
binom = Binom(n + 10, mod)  # Precompute binomial coefficients
ans = binom.comb(n, k)  # Total number of ways to choose k people from n islands
div = pow(binom.comb(n, k), mod - 2, mod)  # Modular inverse of total ways


def dfs(root, n):
    global ans
    par = [-1] * (n + 1)  # Parent of each node
    que = [~root, root]   # Stack for DFS traversal
    in_time = [-1] * (n + 1)  # Entry time for DFS
    out_time = [-1] * (n + 1)  # Exit time for DFS
    tour = []   # DFS traversal order
    now = -1    # Current time
    while que:
        crr = que.pop()
        now += 1
        if crr >= 0:
            # Process node entry
            tour.append(crr)
            cnt[crr] += 1  # Increment count for the node
            if in_time[crr] == -1:
                in_time[crr] = now
            # Add all children to stack
            for nxt in graph[crr]:
                if par[crr] == nxt:
                    continue
                par[nxt] = crr
                que.append(~nxt)
                que.append(nxt)
        else:
            # Process node exit
            out_time[~crr] = now
            # Accumulate children's count to parent
            cnt[par[~crr]] += cnt[~crr]
            # Check if cutting at this edge (partition) makes the current node a good island
            if cnt[~crr] >= k // 2 and (n - cnt[~crr]) >= k // 2:
                # Add number of ways to select k//2 from cnt[~crr] and k//2 from (n - cnt[~crr])
                ans += (
                    binom.comb(cnt[~crr], k // 2)
                    * binom.comb(n - cnt[~crr], k // 2)
                    % mod
                )
                ans %= mod  # Apply modulo to prevent overflow
            if par[~crr] == -1:
                continue
            tour.append(par[~crr])  # Process parent
    return


if k % 2 == 0:
    dfs(1, n)  # Start DFS from root node

# Final result is the expected value
print(ans * div % mod)  # Multiply by modular inverse of total combinations to get expected value


# https://github.com/VaHiX/CodeForces/