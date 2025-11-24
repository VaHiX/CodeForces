# Problem: CF 1889 D - Game of Stacks
# https://codeforces.com/contest/1889/problem/D

"""
Algorithm: Stack Simulation with Memoization
Techniques: 
  - Stack simulation with path compression 
  - Memoization to avoid recomputation
  - Depth-first-like traversal with backtracking

Time Complexity: O(n + sum(ki)) where ki is the number of elements in stack i
Space Complexity: O(n) for the flat and pos arrays plus O(sum(ki)) for stacks storage

This solution simulates the init/get functions for each stack, using memoization to 
store results and avoid redundant computation. It tracks visited positions and uses 
a stack to simulate the call path, updating results as it backtracks.
"""

import sys

input = lambda: sys.stdin.readline().strip()
n = int(input())
# Read stacks and convert to 0-based indexing
stacks = [list(map(lambda s: int(s) - 1, input().split()))[1:] for _ in range(n)]
# flat[i] stores the result of init(i) for memoization
flat = [-1] * n
# pos[i] stores the position in the current path where node i was visited, -1 if not visited
pos = [-1] * n
for i in range(n):
    if flat[i] != -1:
        continue
    # Stack to simulate the path of recursion
    st = [i]
    pos[i] = 0
    while True:
        # If current stack is empty or already computed, resolve the path
        if len(stacks[st[-1]]) == 0 or flat[st[-1]] != -1:
            if flat[st[-1]] == -1:
                flat[st[-1]] = st[-1]
            # Update all nodes in the current path with the final result
            for x in st:
                flat[x] = flat[st[-1]]
            # Reset positions for all nodes in the path
            for x in st:
                pos[x] = -1
            break
        # Get the next position to visit
        loc = stacks[st[-1]][-1]
        # If we've seen this node in the current path, we found a cycle
        if pos[loc] != -1:
            # Pop the last element from the stack we're about to access
            stacks[loc].pop()
            # Backtrack and remove elements that are not part of the final computed path
            while len(st) > 1 + pos[loc]:
                stacks[st[-1]].pop()
                pos[st.pop()] = -1
            continue
        # Mark the node and continue the path
        pos[loc] = len(st)
        st.append(loc)
# Output the 1-based indexed results
print(*[x + 1 for x in flat])


# https://github.com/VaHiX/CodeForces/