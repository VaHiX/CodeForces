# Problem: CF 2133 C - The Nether
# https://codeforces.com/contest/2133/problem/C

"""
C. The Nether

Interactive problem to find the longest path in a directed acyclic graph (DAG) by querying.

Approach:
- Use binary search or greedy approach to determine the longest path.
- First, query for each node the longest path starting from that node using all nodes.
- Then, construct a path greedily, always moving to a node with maximum path length found so far.
- The key insight is to build a path step by step by querying pairs of nodes.

Time Complexity: O(n^2) per test case
Space Complexity: O(n) for storing the list of nodes grouped by path lengths

Algorithms/Techniques:
- Interactive problem with queries
- Graph theory: DAG, longest path
- Greedy selection based on query results
"""

for _ in range(int(input())):
    n = int(input())
    S = [[] for i in range(n + 1)]  # S[i] stores all nodes that have longest path of length i
    all_n = " ".join([str(k) for k in range(1, n + 1)])  # String of all nodes
    m = 0  # max path length found so far
    
    # Query each node with all nodes to find the longest path starting from that node
    for v in range(1, n + 1):
        print("?", v, n, all_n)  # Query the longest path starting from v using all nodes
        ans = int(input())  # Get the result of query
        S[ans].append(v)  # Group nodes by their longest path lengths
        m = max(ans, m)  # Keep track of maximum path length

    # Start building the path with the first node that has maximum path length
    x = [S[m][0]]  # Initialize path with any node having longest path
    
    # Extend the path from longest to shortest by querying pairs
    for i in range(m - 1, 0, -1):  # From max path length down to 1
        for next_x in S[i]:  # For each node with path length i
            print("?", x[-1], 2, x[-1], next_x)  # Query if we can go from last node in x to next_x
            ans = int(input())  # Get the result
            if ans == 2:  # If we can extend path
                x.append(next_x)  # Add next_x to the path
                break  # Break inner loop to move to next shorter path length
    
    # Print final result
    print("!", len(x), *x)


# https://github.com/VaHiX/codeForces/