# Problem: CF 1844 G - Tree Weights
# https://codeforces.com/contest/1844/problem/G

"""
Tree Weights Problem

Algorithm:
- Use DFS traversal to build a tree with parent-child relationships
- Build a segment tree for LCA queries using Euler tour technique
- Use a system of linear equations to compute edge weights
- Solve using bit-by-bit processing to avoid overflow issues

Time Complexity: O(n * log(n) + n * 60) = O(n * log(n))
Space Complexity: O(n * log(n) + n) = O(n * log(n))

This solution uses:
1. DFS-based Euler tour to represent tree structure
2. Segment tree for LCA queries
3. Bit-wise processing to solve the system of equations
4. Mathematical approach to compute edge weights based on distances between consecutive nodes
"""

import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


class segmentTree:
    def __init__(self, arr):
        self.k = len(bin(len(arr))) - 2 # Calculate log2 of array length
        self.l = [0] * ((1 << (self.k + 1)) - 1) # Initialize segment tree array
        self.c = 1 << self.k # Calculate power of 2 greater than or equal to array length
        arr += [0] * (self.c - len(arr)) # Pad array to power of 2
        # Build segment tree from bottom up
        for i in range(self.c):
            self.update(i, arr[i])

    def f(self, a, b):
        # Function to compare nodes in tree (based on order)
        if order[a] > order[b]:
            return b
        return a

    def update(self, node, value):
        # Update a node in segment tree
        i = node + self.c - 1 # Convert to leaf index
        self.l[i] = value
        while i > 0: # Propagate up
            i = (i - 1) >> 1 # Move to parent
            self.l[i] = self.f(self.l[(i << 1) + 1], self.l[(i << 1) + 2]) # Update parent

    def index(self, start, size):
        # Calculate index in segment tree for a query
        return (1 << self.k - size) - 1 + (start >> size)

    def query(self, start, end):
        # Query LCA of two nodes
        i = 0
        k = 1
        c = start
        while c != end + 1:
            while c & ((k << 1) - 1) == 0 and c + k < end:
                i += 1
                k = k << 1
            while c + k > end + 1:
                i -= 1
                k = k >> 1
            if c == start:
                ans = self.l[self.index(start, i)]
            else:
                ans = self.f(ans, self.l[self.index(c, i)])
            c += k
        return ans


n = int(input())
adj = [[] for i in range(n)]
edge = []
for i in range(n - 1):
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    edge.append((a, b))
    adj[a].append(b)
    adj[b].append(a)

# DFS traversal to build tree structure
q = [0]
l = []
parent = [-1] * n
visited = [0] * n
start = [-1] * n
end = [-1] * n
order = [-1] * n
count = 0
while len(q) > 0:
    a = q.pop()
    l.append(a)
    end[a] = len(l) - 1
    if visited[a] == 0:
        order[a] = count
        count += 1
        start[a] = len(l) - 1
        visited[a] = 1
        for i in adj[a]:
            if i != parent[a] and parent[i] == -1:
                parent[i] = a
                q.append(a)
                q.append(i)

# Build segment tree for LCA queries
s = segmentTree(l)
l1 = list(map(int, input().split()))
lca = [-1] * (n - 1)
for i in range(n - 1):
    # Get LCA of nodes i and i+1
    lca[i] = s.query(min(start[i], start[i + 1]), max(start[i], start[i + 1]))

# Solve for edge weights using bit-by-bit approach
answer = [0] * n
for i in range(60): # Process 60 bits (enough for 10^12)
    for j in range(n - 1):
        # Bit-wise propagation
        answer[j + 1] += ((answer[j] >> i) + l1[j]) % 2 * (1 << i)
    for j in range(n - 1):
        # Update residual distances
        l1[j] -= (answer[j] >> i) + (answer[j + 1] >> i) - 2 * (answer[lca[j]] >> i)
        l1[j] //= 2

# Final validation and output
if l1 == [0] * (n - 1):
    ans = []
    for i in range(n - 1):
        # Determine edge weight based on parent-child relationship
        if parent[edge[i][0]] == edge[i][1]:
            ans.append(answer[edge[i][0]] - answer[edge[i][1]])
        else:
            ans.append(answer[edge[i][1]] - answer[edge[i][0]])
    # Check if all weights are positive
    if min(ans) > 0:
        for i in ans:
            print(i)
    else:
        print(-1)
else:
    print(-1)


# https://github.com/VaHiX/CodeForces/