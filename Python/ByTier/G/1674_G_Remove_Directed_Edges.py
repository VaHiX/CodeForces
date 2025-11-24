# Problem: CF 1674 G - Remove Directed Edges
# https://codeforces.com/contest/1674/problem/G
 
"""
Algorithm: Topological Sorting with Dynamic Programming
Time Complexity: O(n + m)
Space Complexity: O(n + m)
 
This solution finds the maximum size of a "cute" set in a directed acyclic graph (DAG).
A cute set is a set of vertices where for any two vertices in the set, there's a path
between them using the remaining edges (after removing some edges). The removal rules
require that for each vertex, either its in-degree or out-degree decreases, or both are zero.
 
The key idea is to use topological sorting and dynamic programming:
1. Build the graph and calculate initial in-degrees and out-degrees.
2. Initialize a DP array where dp[i] represents the maximum size of a cute set ending at vertex i.
3. Process vertices in topological order, updating DP values based on conditions:
   - If both in-degree and out-degree of current and next vertex are > 1, extend the cute set.
4. Track the maximum DP value encountered, which corresponds to the answer.
 
The algorithm works by considering that in a DAG, if we remove edges strategically,
we can create a structure where the maximum "cute" set forms a chain of vertices
with appropriate degrees.
"""
 
import queue
from sys import stdin
 
MAXN = 200010
 
 
def solve():
 
    n, m = map(int, stdin.readline().split())
    G = [[] for i in range(MAXN)]  # Adjacency list representation of the graph
    indeg, outdeg, cur = [[0 for i in range(MAXN)] for j in range(3)]  # in-degrees, out-degrees, and current degrees
    
    for i in range(m):
        x, y = map(int, stdin.readline().split())
        G[x].append(y)
        indeg[y] += 1
        outdeg[x] += 1
        cur[y] += 1  # Copy of in-degrees used for topological sort tracking
 
    dp = [1] * MAXN  # dp[i] stores max size of cute set ending at vertex i
    ans = 1
    q = queue.Queue()  # Queue for topological sort
    
    # Initialize queue with vertices having no incoming edges
    for i in range(1, n + 1):
        if cur[i] == 0:
            q.put(i)
            
    while not q.empty():
        now = q.get()  # Get vertex from topological order
        ans = max(ans, dp[now])  # Update maximum cute set size found so far
        
        # Process neighbors of current vertex
        for x in G[now]:
            cur[x] -= 1  # Decrease the current in-degree counter
            if cur[x] == 0:
                q.put(x)  # If in-degree becomes zero, add to queue
            
            # If both in-degree and out-degree are greater than 1,
            # it is possible to extend the cute set
            if outdeg[now] > 1 and indeg[x] > 1:
                dp[x] = max(dp[x], dp[now] + 1)
                
    print(ans)
 
solve()
 
 
# https://github.com/VaHiX/CodeForces/