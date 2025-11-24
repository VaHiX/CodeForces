# Problem: CF 1671 E - Preorder
# https://codeforces.com/contest/1671/problem/E
 
"""
Code Purpose:
This code calculates the number of different preorder strings that can be obtained from a perfect binary tree
by swapping children of non-leaf vertices any number of times. It uses dynamic programming to compute
the number of distinct preorder strings rooted at each node, considering that we can choose which child
to visit first (left or right) when building the preorder traversal.
 
Algorithms/Techniques:
- Dynamic Programming on Trees
- Recursion with memoization for computing subtree properties
- Tree traversal using index-based representation (2*x for left, 2*x+1 for right)
 
Time Complexity:
O(2^n), where n is the height of the tree. This is because we process each node exactly once in the recursive tree traversal.
 
Space Complexity:
O(2^n) for storing the node values and memoization arrays.
"""
 
M = 998244353
n = int(input())
a = input()
b = [""] * (1 << n)  # Stores preorder strings for each node
F = [-1] * (1 << n)  # Stores the count of distinct preorder strings for each subtree
 
 
def f(x, d):
    # Base case: if we reach a leaf node (depth n)
    if d == n:
        F[x - 1] = 1  # One way to form preorder string at leaf
        b[x - 1] = a[x - 1]  # Leaf value is just the character itself
    else:
        # Recursively process left and right subtrees
        f(2 * x, d + 1)      # Left child
        f(2 * x + 1, d + 1)  # Right child
        
        # Form the preorder string for current node:
        # s_x + min(left_preorder + right_preorder, right_preorder + left_preorder)
        # This ensures we take the lexicographically smaller string as the canonical form
        b[x - 1] = a[x - 1] + min(b[2 * x - 1] + b[2 * x], b[2 * x] + b[2 * x - 1])
        
        # Compute number of distinct preorder strings rooted at x:
        # If the two subtrees yield same preorder strings, then only 1 way to combine
        # Otherwise, there are 2 * F[2*x-1] * F[2*x] ways (choose which subtree to visit first)
        F[x - 1] = (
            F[2 * x - 1] ** 2
            if b[2 * x - 1] == b[2 * x]
            else (2 * F[2 * x - 1] * F[2 * x]) % M
        )
 
 
f(1, 1)  # Start from root (index 1)
print(F[0])  # Result is the count for the whole tree
 
 
# https://github.com/VaHiX/CodeForces/