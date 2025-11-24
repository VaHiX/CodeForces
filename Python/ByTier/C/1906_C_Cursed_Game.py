# Problem: CF 1906 C - Cursed Game
# https://codeforces.com/contest/1906/problem/C

"""
Cursed Game Solver

Algorithm:
This is a game-solving problem where we need to determine the location of holes in a 3x3 secret grid by querying a larger N×N grid. 
The key insight is to use XOR properties and strategic queries to identify which cells have holes.

Approach:
1. For N=3, randomly generate a 3x3 grid and query until we get a "CORRECT" response. This works because the secret grid is fixed and we're trying to identify it.
2. For N>3:
   - First, we query a grid where only the bottom-right cell (3,3) is black.
   - The result tells us which 3x3 subregions of the secret grid have holes (based on how many black cells are visible).
   - Then, we strategically construct a new grid to determine the exact positions of the holes using XOR operations.
   
Time Complexity: O(N^2) per round on average, where N is the size of the query grid.
Space Complexity: O(N^2) for storing the grids.

The algorithm works by treating the problem as a system of linear equations in GF(2) and using queries to solve it.
"""

import random
import sys

MAXN = 45
n = 0
a = [[0] * MAXN for _ in range(MAXN)]
b = [[0] * MAXN for _ in range(MAXN)]
ans = [[0] * 5 for _ in range(5)]


def query():
    global n, a, b
    # Output the current query grid
    for i in range(1, n + 1):
        sys.stdout.write("".join(str(a[i][j]) for j in range(1, n + 1)) + "\n")
    sys.stdout.flush()
    s = sys.stdin.readline().strip()
    if not s:
        return True
    if s[0] == "C":
        return True
    # Read the binary result grid from the demon
    for i in range(1, n - 1):
        s = sys.stdin.readline().strip()
        for j in range(1, n - 1):
            b[i][j] = ord(s[j - 1]) - 48
    return False


def main():
    global n, a, b
    random.seed(998244353)
    for t in range(1, 334):
        line = sys.stdin.readline().strip()
        if not line:
            return
        n = int(line)
        if n == 3:
            # For N=3, we can simply try random guesses until we get a CORRECT response
            while True:
                for i in range(1, 4):
                    for j in range(1, 4):
                        a[i][j] = random.getrandbits(1)
                if query():
                    break
            continue
        # For N>3, we use a more systematic approach
        for i in range(1, n + 1):
            for j in range(1, n + 1):
                a[i][j] = 0
        # Set only the bottom-right cell to 1 to identify the pattern
        a[3][3] = 1
        if query():
            continue
        # Collect positions of holes based on the result
        v = []
        for i in range(1, 4):
            for j in range(1, 4):
                # If the value is 1, it suggests a hole at position (i-1,j-1) relative to the top-left of the secret grid
                if b[4 - i][4 - j]:
                    v.append((i - 1, j - 1))
        # Reset the grid
        for i in range(MAXN):
            for j in range(MAXN):
                a[i][j] = 0
        # Use the collected information to reconstruct the final answer
        for i in range(1, n - 1):
            for j in range(1, n - 1):
                tmp = 0
                for x, y in v:
                    tmp ^= a[i + x][j + y]
                x, y = v[-1]
                # Apply XOR to set the corresponding bit to 1 if needed
                if not tmp:
                    a[i + x][j + y] ^= 1
        query()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/