# Problem: CF 2139 E2 - Maple and Tree Beauty (Hard Version)
# https://codeforces.com/contest/2139/problem/E2

# Flowerbox for code purpose description and complexity info:
"""
E2. Maple and Tree Beauty (Hard Version)

This problem involves a rooted tree with n vertices. Each vertex can be labeled with either 0 or 1, 
given exactly k zeros and (n - k) ones. For each vertex, we form a binary string from the root to that vertex.
The beauty is defined as the length of the longest common subsequence (LCS) among all leaf vertex names.

Approach:
- We first compute the depth (level) of each node and determine minimum depth of any leaf.
- The idea is that a prefix of length L shared by all leaves implies at least one leaf with depth L+1.
- We use dynamic programming with bitmasks over "blocks" of size `bits` to efficiently update potential LCS configurations.
- Finally, we binary search or check for the maximum valid LCS value.

Time Complexity: O(n * log n) per test case due to bitmask DP on levels and tree traversal.
Space Complexity: O(n + bits) where bits is precomputed for mask operations.
"""

from sys import stdin, stdout

input = lambda: stdin.readline().rstrip()
print = lambda *args, sep=" ", end="\n": stdout.write(sep.join(map(str, args)) + end)


def out(l):
    print(" ".join(map(str, l)))


def yes():
    print("YES")


def no():
    print("NO")


def solve():
    n, totz = map(int, input().split())
    p = [0, 0] + list(map(int, input().split()))
    adj = [[] for i in range(n + 1)]
    for i, j in enumerate(p):
        if j:
            adj[j].append(i)
    
    # Build tree using stack; compute level of nodes
    stk = [(1, 0)]
    lvl = [0] * (n + 1)
    lvl[1] = 1
    mi = n  # Minimum depth among leaves
    
    while stk:
        parent, grand_par = stk.pop()
        for child in adj[parent]:
            lvl[child] = lvl[parent] + 1
            stk.append((child, parent))
            if not adj[child]:  # is a leaf
                mi = min(mi, lvl[child])
    
    toto = n - totz  # number of ones
    tot = [0] * (mi + 1)  # how many leaves exist at each level up to mi
    for level in lvl[1:]:
        if level <= mi:
            tot[level] += 1
    nodes = sum(tot)
    extra = n - nodes  # how many non-leaf nodes exist
    if nodes <= max(totz, toto):
        print(mi)
        return

    m = (n + 1) // bits  # number of bitmasks needed
    dp = [0] * (m + 1)

    # Initialize DP for the last block with full set of numbers
    dp[0] = power[bits - 1]

    # Compute required masks for valid configurations
    blocks, blocke = max(0, totz - extra) // bits, totz // bits
    reqs, reqe = bits - (max(0, totz - extra) % bits), bits - (totz % bits + 1)

    # Traverse levels from low to high and update DP values using bitmask
    for j in tot:
        if not j:
            continue
        # Transform the index into a mask position within block bounds
        j = bits * (m + 1) - 1 - j
        block = j // bits
        req = bits - (j % bits + 1)

        # Iterate all possible previous blocks backwards to propagate information
        for i in range(m, -1, -1):
            cur = (
                (dp[block - 1] & (power[req] - 1)) * power[bits - req] if block else 0
            ) | (dp[block] // power[req])
            dp[i] |= cur
            
            # Check conditions for early termination and solution finding
            if blocks == blocke:
                if i == blocks and (dp[i] & (power[reqs] - 1)) // power[reqe]:
                    print(mi)
                    return
            elif (
                (blocks < i < blocke and dp[i])
                or (i == blocks and dp[i] & (power[reqs] - 1))
                or (i == blocke and dp[i] // power[req])
            ):
                print(mi)
                return
            
            if not block:
                break
            block -= 1
    
    print(mi - 1)  # if no better solution found, reduce by one


bits = 8192
power = [1]
for i in range(bits):
    power.append(power[-1] << 1)

for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/