# Problem: CF 2007 E - Iris and the Tree
# https://codeforces.com/contest/2007/problem/E

"""
Code Purpose:
This code solves the problem of a rooted tree with unknown edge weights, where the sum of all edge weights is given.
The goal is to process a series of events where specific edge weights are set, and after each event,
compute the maximum possible sum of distances between consecutive vertices in a cyclic manner.

Algorithms/Techniques:
- Tree traversal and preprocessing of depth and subtree sizes
- Efficient updates using difference arrays
- Mathematical optimization to compute maximum distances

Time Complexity: O(n) per test case, where n is the number of vertices
Space Complexity: O(n) for storing tree information and arrays
"""

def solve():
    n, W = map(int, input().split())
    fa = [0] * (n + 1)  # Parent array
    dep = [0] * (n + 1)  # Depth array
    siz = [1] * (n + 1)  # Subtree size array
    dist = [0] * (n + 1)  # Distance array for tracking maximum distances
    
    fa_list = list(map(int, input().split()))
    for i in range(2, n + 1):
        fa[i] = fa_list[i - 2]  # Set parent of vertex i
        dep[i] = dep[fa[i]] + 1  # Set depth of vertex i
    
    # Compute subtree sizes (bottom-up)
    for i in range(n, 1, -1):
        siz[fa[i]] += siz[i]
    
    # Precompute distances for all consecutive vertices
    dist[n] = dep[n]
    for i in range(1, n):
        dist[i] = dep[i] + dep[i + 1] - 2 * dep[fa[i + 1]]
    
    s = 0  # Sum of known edge weights so far
    cnt = n  # Count of vertices with non-zero contribution to distance
    result = []  # Store results after each event
    
    # Process each event
    for _ in range(1, n):
        x, w = map(int, input().split())  # Get vertex x and edge weight w
        s += w  # Add weight w to the sum of known weights
        
        # Update dist array - adjust contribution of vertex x-1
        dist[x - 1] -= 1
        if dist[x - 1] == 0:
            cnt -= 1  # Decrease count if contribution becomes zero
        
        # Update dist array - adjust contribution of the last vertex in subtree of x
        dist[x + siz[x] - 1] -= 1
        if dist[x + siz[x] - 1] == 0:
            cnt -= 1  # Decrease count if contribution becomes zero
        
        # Compute and store the result: 2*s (sum of known weights) + (W-s)*cnt (max possible weights)
        result.append(s * 2 + (W - s) * cnt)
    
    print(" ".join(map(str, result)))


def main():
    t = int(input())
    for _ in range(t):
        solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/