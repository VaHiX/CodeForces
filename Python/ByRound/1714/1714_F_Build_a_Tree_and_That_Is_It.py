# Problem: CF 1714 F - Build a Tree and That Is It
# https://codeforces.com/contest/1714/problem/F

"""
Construct a tree with n vertices such that:
- Distance between vertex 1 and 2 is d12
- Distance between vertex 2 and 3 is d23  
- Distance between vertex 3 and 1 is d31

Algorithm:
1. Check if a valid tree exists by verifying that the sum of all distances is even.
   If it's odd, no tree can satisfy the conditions (due to triangle inequality).
2. Calculate x, y, z which represent the number of internal nodes on paths:
   - x = (d12 + d31 - d23) / 2
   - y = (d12 + d23 - d31) / 2  
   - z = (d23 + d31 - d12) / 2
3. If any of x, y, z are negative, invalid.
4. Build the tree by connecting path segments and attaching remaining nodes to vertex 3.

Time Complexity: O(n) in worst case due to output of n-1 edges
Space Complexity: O(n) for storing the answer
"""

t = int(input())

ans = []
for _ in range(t):
    n, d12, d23, d31 = map(int, input().split())
    s = d12 + d23 + d31
    if s % 2 == 1:
        ans.append("NO")
        continue
    x = (s - 2 * d23) // 2  # Number of nodes on path 1->2 (excluding endpoints)
    y = (s - 2 * d31) // 2  # Number of nodes on path 2->3 (excluding endpoints)
    z = (s - 2 * d12) // 2  # Number of nodes on path 3->1 (excluding endpoints)
    if x < 0 or y < 0 or z < 0 or (x + y + z >= n):
        ans.append("NO")
        continue

    ans.append("YES")
    q = 4
    if x == 0:
        start = 1
    elif y == 0:
        start = 2
    elif z == 0:
        start = 3
    else:
        start = 4
        q = 5

    # Build the paths from 1, 2, 3 to each other
    for j, v in enumerate((x, y, z), 1):
        p = start
        for i in range(v - 1):
            ans.append(f"{p } {q }")
            p = q
            q += 1
        if v > 0:
            ans.append(f"{p } {j }")

    # Attach leftover nodes to vertex 3 (the last vertex in the structure)
    for i in range(q, n + 1):
        ans.append(f"{3 } {i }")

print("\n".join(ans))


# https://github.com/VaHiX/CodeForces/