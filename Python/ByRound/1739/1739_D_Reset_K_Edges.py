# Problem: CF 1739 D - Reset K Edges
# https://codeforces.com/contest/1739/problem/D

"""
Algorithm: Binary search on the answer + greedy tree traversal
Approach:
- We binary search on the possible height of the tree.
- For a given height `mid`, we calculate how many operations are needed to reduce the tree to that height.
- This is done by traversing the tree from leaves to root and greedily deciding when to "reset" a subtree to be a child of the root.
- Time Complexity: O(n * log n) per testcase, since we do binary search over height (up to n) and for each height we process all nodes once.
- Space Complexity: O(n), to store parent array and height array.
"""
R, G = lambda: map(int, input().split()), range
(t,) = R()
for _ in G(t):
    n, k = R()
    p = [-1, 0] + [*R()]  # p[i] is parent of vertex i, index 0 unused
    l, r = 1, n - 1  # Binary search bounds for height
    while l <= r:
        mid = (l + r) // 2  # Midpoint of current binary search range
        c = 0  # Count of operations needed for current mid height
        h = [0] * (n + 1)  # h[i] stores the height of subtree rooted at i
        for i in G(n, 1, -1):  # Traverse nodes from n down to 2
            if h[i] == mid - 1 and p[i] != 1:  # If current node's height is mid-1 and not rooted at 1
                c += 1  # Need to move this subtree to root
            else:
                h[p[i]] = max(h[p[i]], h[i] + 1)  # Update parent's height
        if c <= k:  # If operations needed are within allowed k
            r = mid - 1  # Try to reduce height
        else:
            l = mid + 1  # Need more operations, increase height
    print(l)


# https://github.com/VaHiX/CodeForces/