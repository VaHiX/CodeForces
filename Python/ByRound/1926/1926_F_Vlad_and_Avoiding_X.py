# Problem: CF 1926 F - Vlad and Avoiding X
# https://codeforces.com/contest/1926/problem/F

"""
Algorithm: Dynamic Programming with Memoization (DFS)
Approach: 
- The problem is to eliminate all black cells that have all four diagonal neighbors also black.
- This is done by trying all combinations of flipping cells in a bipartite manner (based on parity of (i+j)).
- States are represented as bitmasks of which cells are black.
- For each state, we determine the minimum number of flips needed by recursively trying to resolve conflicts.
- Time Complexity: O(2^49) which is too large for direct computation, but due to pruning from memoization and small grid, it's manageable.
Space Complexity: O(2^49) in worst case for memoization.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
memo = {}


def solve():
    s = []
    for _ in range(7):
        s.append(input())

    def dfs(state, parity):
        # Base case: no more conflicts
        if state == 0:
            return 0
        # Memoization
        if (state, parity) in memo:
            return memo[(state, parity)]
        # Collect all conflicting cells based on parity
        t = []
        for i in range(7):
            for j in range(7):
                if (i + j) % 2 == parity:
                    data = [0, 0]
                    # Check for all diagonal neighbors including current
                    for x, y in [
                        (i - 1, j - 1),
                        (i - 1, j + 1),
                        (i + 1, j - 1),
                        (i + 1, j + 1),
                        (i, j),
                    ]:
                        # If in bounds and black cell
                        if 0 <= 7 * x + y < 49 and state & 1 << (7 * x + y):
                            data[0] += 1
                            data[1] |= 1 << (7 * x + y)
                    if data[0] > 0:
                        t.append(data.copy())
        # Sort to try more impactful moves first
        t.sort(reverse=True)
        res = 212  # Large number to represent infinity
        for cnt, cancel in t:
            # Try flipping one of the conflicting cells
            res = min(res, 1 + dfs(state ^ cancel, parity))
        memo[(state, parity)] = res
        return res

    # Build initial state (bitmask for each parity group)
    state = [0, 0]
    for i in range(1, 6):
        for j in range(1, 6):
            # If it's a black cell with all four diagonal neighbors also black
            if (
                s[i][j] == "B"
                and s[i - 1][j - 1] == "B"
                and s[i + 1][j - 1] == "B"
                and s[i + 1][j + 1] == "B"
                and s[i - 1][j + 1] == "B"
            ):
                state[(i + j) % 2] |= 1 << (7 * i + j)
    
    # Calculate minimal operations for both parity groups
    res = dfs(state[0], 0) + dfs(state[1], 1)
    print(res)
    return


T = int(input())
for _ in range(T):
    solve()


# https://github.com/VaHiX/CodeForces/