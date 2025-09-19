# Problem: CF 2138 C1 - Maple and Tree Beauty (Easy Version)
# https://codeforces.com/contest/2138/problem/C1

"""
Problem: C1. Maple and Tree Beauty (Easy Version)

Purpose:
This code solves the problem of maximizing the beauty of a rooted tree,
where beauty is defined as the length of the longest common subsequence (LCS)
of all leaf node names. Each node is labeled with either 0 or 1, with exactly
k zeros and n-k ones. The node names are formed by concatenating the labels along
the path from the root to that node.

Algorithms/Techniques:
- Tree traversal to compute level sizes (bfs-like process)
- Dynamic programming using bit manipulation for efficient state tracking
- Preprocessing of previous greater element and next smaller element with stack

Time Complexity: O(N^2) in worst case due to dynamic programming over levels, 
                  where N is the number of nodes.
Space Complexity: O(N) for storing adjacency list, level data, stacks, and DP states.

Input Format:
First line contains number of test cases t
For each test case:
  - First line: n (number of nodes), k (number of zeros)
  - Second line: parent array p2, p3, ..., pn

Output:
For each test case: maximum possible beauty (length of LCS of leaf names)

"""

import sys

input = lambda: sys.stdin.readline().rstrip("\r\n")
rint = lambda: int(input())
rlist = lambda: list(map(int, input().split()))
rgrid = lambda n: [list(map(int, input().split())) for _ in range(n)]
fmax = lambda x, y: x if x > y else y
fmin = lambda x, y: x if x < y else y
inf = float("inf")


def prev_greater_left(A):
    """Precompute previous greater element to the left using stack."""
    N = len(A)
    left = [-1] * N
    stack = []
    for i in range(N):
        while stack and A[stack[-1]] <= A[i]:
            stack.pop()
        left[i] = stack[-1] if stack else -1
        stack.append(i)
    return left


def next_smaller_right(A):
    """Precompute next smaller element to the right using stack."""
    N = len(A)
    right = [N] * N
    stack = []
    for i in range(N - 1, -1, -1):
        while stack and A[stack[-1]] >= A[i]:
            stack.pop()
        right[i] = stack[-1] if stack else N
        stack.append(i)
    return right


def solve():
    N, K = rlist()
    P2 = rlist()  # Parent array for vertices 2 to n
    adj = [[] for _ in range(N)]
    for u, p in enumerate(P2, 1):
        p -= 1  # Convert to 0-based index
        adj[p].append(u)
    
    # Compute level sizes using BFS-like traversal
    lengths = []
    frontier = [0]  # Start with root node 0
    while frontier:
        lengths.append(len(frontier))
        queue = frontier
        frontier = []
        saw_leaf = 0  # Flag to check if any leaf exists in current level
        for u in queue:
            if not adj[u]:
                saw_leaf = 1  # Found a leaf
            for v in adj[u]:
                frontier.append(v)
        if saw_leaf:
            break  # Stop when first leaf is encountered
    
    # Dynamic programming using bitset-like approach to track possible LCS lengths
    dp = 0b1  # Initially only length 0 possible (empty string)
    ans = T = 0  # T tracks total prefix length; ans stores maximum valid level
    
    for cur, L in enumerate(lengths, 1):  # Iterate through each level
        dp |= dp << L  # Shift and update DP with new possible lengths
        T += L  # Total length so far
        
        # Compute range of valid indices to check
        lo = max(0, T - N + K)
        hi = K
        
        for x in range(lo, hi + 1):
            if dp >> x & 1:
                ans = cur
                break
    
    return ans


TT = 1
TT = rint()
for tc in range(TT):
    ans = solve()
    print(ans)


# https://github.com/VaHiX/codeForces/