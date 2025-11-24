# Problem: CF 2143 D2 - Inversion Graph Coloring (Hard Version)
# https://codeforces.com/contest/2143/problem/D2

"""
D2. Inversion Graph Coloring (Hard Version)
Algorithm: Fenwick Tree (Binary Indexed Tree) with dynamic programming
Time Complexity: O(n^2 * log n)
Space Complexity: O(n^2)

This problem computes the number of "good" subsequences in a given array.
A subsequence is good if we can color its elements red or blue such that 
for every pair where an element is greater than another, they have different colors.
This is equivalent to saying the sequence has no decreasing subsequence of length > 1
that violates the coloring constraint, which corresponds to counting valid subsequences
using dynamic programming and a Fenwick Tree for efficient updates.

The solution uses DP with a 2D Fenwick Tree to count valid subsequences ending at each position.
Each element is processed in order, updating the tree to track prefix sums for color assignments,
and using modular arithmetic to avoid overflow.
"""

def solution():
    n = int(input())
    u = n + 2
    f = [[0] * u for _ in range(u)]
    res = 1   # Start with 1 to account for empty subsequence
    i = 1
    while i < u:
        f[i][1] += 1   # Initialize the Fenwick tree
        i += -i & i    # Move to next node using bit trick
    
    for x in map(int, input().split()):
        x += 1   # Convert to 1-based indexing
        
        t = [0] * u   # Temporary array to store intermediate values
        
        i = x
        while i:  # Query operation on Fenwick Tree for prefix sums
            fi = f[i]
            for j in range(1, i + 1):
                t[j] += fi[j]  # Accumulate from smaller indices
            for j in range(x + 1, u):
                t[j] += fi[j]  # Accumulate from larger indices
            i -= -i & i    # Move to parent node in Fenwick Tree
            
        for i in range(u):
            t[i] %= 1000000007  # Keep result mod 10^9 + 7
            
        res += sum(t) % 1000000007  # Add current count to total
        
        i = x
        while i < u:  # Update operation on Fenwick Tree
            fi = f[i]
            for j in range(1, x):
                fi[j] += t[j]     # Update lower indices
            for j in range(i + 1, u):
                fi[j] += t[j]     # Update higher indices
            i += -i & i           # Move to next node
            
        # Update additional parts of Fenwick Tree for cross-index handling
        for i in range(1, x):
            f[i][x] += t[i]
            j = i + (-i & i)
            if j < x:
                t[j] += t[i]   # Propagate update
                
        for i in range(x + 1, u):
            f[i][x] += t[i]
            j = i + (-i & i)
            if j < u:
                t[j] += t[i]   # Propagate update
                
    print(res % 1000000007)  # Print final result mod 10^9 + 7

for _ in range(int(input())):
    solution()


# https://github.com/VaHiX/codeForces/