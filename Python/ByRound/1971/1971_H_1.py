# Problem: CF 1971 H - ±1
# https://codeforces.com/contest/1971/problem/H

"""
Algorithm: 2-SAT (2-Satisfiability) using graph coloring approach
Purpose: Determine if Alice can choose values for a[i] (either 1 or -1) such that 
         after sorting each column, the middle row of the resulting grid is all 1s.

Time Complexity: O(n^2) where n is the number of columns.
Space Complexity: O(n^2) for storing the graph representation.

This problem reduces to a 2-SAT satisfiability problem:
- Each variable a[i] can be either 1 or -1
- For each column, we deduce constraints based on what values of a[i] lead to 1 in the middle row
- We build an implication graph and check if a valid assignment exists using 2-SAT solving technique
"""

from sys import stdin


def is_solvable(field):
    n = len(field[0])
    # Build implication graph for 2-SAT
    # graph[i] contains variables that must be false if i is true
    graph = [[] for i in range(2 * n + 1)]
    
    # Process triplets of values from each column of the grid
    for a, b, c in zip(*field):
        # Add constraints: if a is true, then b and c must be false
        # And if b is true, then a and c must be false
        # And if c is true, then a and b must be false
        graph[a].extend((-b, -c))
        graph[b].extend((-a, -c))
        graph[c].extend((-a, -b))
    
    # Status array to track assignment
    # 0: unvisited, 1: true, -1: false
    status = [0] * len(graph)

    # DFS-based 2-SAT solver using implication graph
    def try_fill(i):
        traversal = [i]  # Stack for DFS
        status[i] = 1    # Mark as true
        status[-i] = -1  # Mark negation as false
        processed = 0
        while processed < len(traversal):
            v = traversal[processed]
            processed += 1
            # For each neighbor in implication graph
            for u in graph[v]:
                # If u is already assigned to conflict with current assignment
                if status[u] == -1:
                    # Conflict found, backtrack
                    for w in traversal:
                        status[w] = 0
                        status[-w] = 0
                    return False
                # If u is unassigned, assign it
                if status[u] == 0:
                    status[u] = 1
                    status[-u] = -1
                    traversal.append(u)
        return True

    # Try to assign all variables using 2-SAT
    for i in range(1, n + 1):
        if status[i] != 0:
            continue
        # Try assigning i as true first
        if not (try_fill(i) or try_fill(-i)):
            return "NO"
    return "YES"


n_tests = int(stdin.readline())
for test_id in range(n_tests):
    n = int(stdin.readline())
    field = []
    for i in range(3):
        field.append(list(map(int, stdin.readline().split())))
    print(is_solvable(field))


# https://github.com/VaHiX/CodeForces/