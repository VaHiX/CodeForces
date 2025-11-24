# Problem: CF 1787 D - Game on Axis
# https://codeforces.com/contest/1787/problem/D

"""
Algorithm: Game on Axis
Purpose: To determine the number of valid (x,y) pairs such that replacing a[x] with y results in a finite game.
Approach:
- For each starting point, simulate the game to detect cycles or exit conditions.
- Identify which positions lead to finite paths (i.e., end in valid exit) or infinite loops.
- Use DFS-like traversal to compute the number of valid replacements for each position.
- Apply mathematical formula to count valid pairs without explicitly checking all.

Time Complexity: O(n) amortized due to path compression in traversal.
Space Complexity: O(n) for storing data and visit tracking.

The algorithm uses a state tracking approach:
- If we reach an index less than 0 or greater than or equal to n, we exit (finite path).
- If we revisit an index in a current traversal, we're in a cycle.
- If we have already computed the result for a node during traversal, we use it.

The final result is calculated based on:
- Total possible valid pairs: n * (2 * n + 1)
- Subtracting invalid configurations based on how many paths end or loop.
"""

import sys

input = sys.stdin.readline
rounds = int(input())
for ii in range(rounds):
    out = 0
    length = int(input())
    arr = list(map(int, input().split()))
    data = [0] * length  # Stores computed data for each index: 
                         # - Negative value means finite path with negative steps
                         # - Positive value < 10^10 means steps to end
                         # - >= 10^10 means loop detected
    for l in range(length):
        if data[l] != 0:
            continue  # Already computed
        start = l
        visit = set()  # Tracks current path
        visit.add(start)
        while True:
            start += arr[start]
            if start < 0 or start >= length:
                # Reached boundary - finite path
                if l == 0:
                    # For start = 0, store path lengths
                    cnt = len(visit)
                    for v in visit:
                        data[v] = cnt
                        cnt -= 1
                else:
                    # All nodes in path are marked as finite with negative value
                    for v in visit:
                        data[v] = -1
                break
            if data[start] != 0:
                # Already computed result for this node
                for v in visit:
                    data[v] = data[start]
                break
            if start in visit:
                # Loop detected
                if l != 0:
                    # Not starting at index 0, so mark all nodes in cycle
                    for v in visit:
                        data[v] = 10**10
                else:
                    # Starting at index 0, so we know how many steps to loop
                    ll = len(visit)
                    for v in visit:
                        data[v] = 10**10 + ll
                break
            visit.add(start)

    loop = 0
    end = 0
    for d in data:
        if d > 0 and d < 10**10:
            end += d
        elif d >= 10**10:
            loop += 1
    
    if data[0] < 10**10:
        # Not in loop, calculate total valid pairs
        ans = length * (2 * length + 1)
        ans -= data[0] * loop
        ans -= end
    else:
        # We are in a loop starting at 0, compute adjustment
        data[0] -= 10**10
        ans = data[0] * (2 * length - (loop - 1))
    print(ans)


# https://github.com/VaHiX/CodeForces/