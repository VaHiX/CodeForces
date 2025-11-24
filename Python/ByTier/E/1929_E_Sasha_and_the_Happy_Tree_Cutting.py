# Problem: CF 1929 E - Sasha and the Happy Tree Cutting
# https://codeforces.com/contest/1929/problem/E

"""
Algorithm: Minimum Edge Cover for Tree Paths
Techniques: DFS traversal, bit manipulation, dynamic programming

Time Complexity: O(n + 2^k * k) where n is number of vertices and k is number of pairs
Space Complexity: O(n + 2^k) for storing parent information, tmp array and DP table

This solution uses a tree DFS traversal to compute the XOR of bits for each node,
representing which pairs have their path passing through that node. Then it uses
bitmask dynamic programming to find the minimum number of edges needed to cover
all pairs.
"""

def II():
    return int(input())
def GMI():
    return map(lambda x: int(x) - 1, input().split())

def main():
    n = II()
    # Build adjacency list representation of tree
    path = [[] for _ in range(n)]
    for _ in range(n - 1):
        u, v = GMI()  # Convert to 0-indexed
        path[u].append(v)
        path[v].append(u)

    # DFS to find parent and order of nodes
    parent = [-1] * n
    order = []
    stack = [0]  # Start from root node 0
    while stack:
        u = stack.pop()
        for v in path[u]:
            if parent[u] != v:  # Avoid going back to parent
                parent[v] = u
                stack.append(v)
                order.append(v)  # Keep track of visit order

    # Initialize tmp array to store bitmasks for each node
    tmp = [0] * n
    k = II()
    # For each query pair, set corresponding bit in start and end nodes
    for i in range(k):
        val = 1 << i  # Bitmask for current pair
        u, v = GMI()  # Convert to 0-indexed
        tmp[u] ^= val  # Toggle bit for start node
        tmp[v] ^= val  # Toggle bit for end node

    # Propagate bits up the tree using parent information
    for u in reversed(order):  # Process nodes in reverse DFS order
        tmp[parent[u]] ^= tmp[u]  # Accumulate bits from children to parent

    # Convert to set to get unique bitmasks
    tmp = set(tmp)
    # DP table where dp[i] represents minimum edges to cover all pairs represented by bits in i
    dp = [k + 1] * (1 << k)  # Initialize with large value
    dp[0] = 0  # No edges needed for no pairs

    # Dynamic programming: for each unique bitmask, update all combinations
    for x in tmp:
        for i in range(1 << k):  # Iterate through all possible masks
            dp[i | x] = min(dp[i | x], dp[i] + 1)  # Update minimum edges needed
    
    print(dp[-1])  # Answer is when all pairs are covered (full mask)
    return


t = II()

for _ in range(t):
    main()


# https://github.com/VaHiX/CodeForces/