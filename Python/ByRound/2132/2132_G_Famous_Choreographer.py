"""
Problem: CF2132G - Famous Choreographer

This program finds the minimum number of additional cells needed to extend a grid
such that it contains both the original grid and its 180-degree rotation.
The solution uses 2D rolling hashing with two different bases to efficiently
compare grid patterns.

Approach:
1. Generate random bases for hashing to minimize collision probability
2. Precompute prefix hashes for both original and rotated grids
3. Use double hashing for collision resistance
4. Check all possible shifts of the rotated grid against the original

Time Complexity: O(Q * N * M)
   - Q: Number of test cases
   - N, M: Grid dimensions
   - For each test case: O(N*M) for hashing and comparison

Space Complexity: O(N*M)
   - Storage for original and rotated grid hashes
   - Precomputed powers of bases
"""

import sys
from random import randint


def solve():
    input = sys.stdin.read
    data = input().split()
    idx = 0
    Q = int(data[idx])
    idx += 1

    MOD1 = 10**9 + 7
    MOD2 = 998244353

    for _ in range(Q):
        # Read grid dimensions
        N, M = map(int, data[idx : idx + 2])
        idx += 2

        # Read grid
        grid = []
        for _ in range(N):
            grid.append(data[idx].strip())
            idx += 1

        min_additional = float("inf")

        # Generate random bases for double hashing
        base1 = randint(1000, 10000)
        base2 = randint(10000, 100000)

        # Precompute powers of bases
        max_power = N * M + 1
        pow1 = [1] * max_power
        pow2 = [1] * max_power
        for i in range(1, max_power):
            pow1[i] = (pow1[i - 1] * base1) % MOD1
            pow2[i] = (pow2[i - 1] * base2) % MOD2

        # Compute row-wise hashes
        row_hash1 = [[0] * M for _ in range(N)]
        row_hash2 = [[0] * M for _ in range(N)]

        for i in range(N):
            for j in range(M):
                val = ord(grid[i][j]) - ord("a") + 1
                if j > 0:
                    row_hash1[i][j] = (row_hash1[i][j - 1] * base1 + val) % MOD1
                    row_hash2[i][j] = (row_hash2[i][j - 1] * base2 + val) % MOD2
                else:
                    row_hash1[i][j] = val % MOD1
                    row_hash2[i][j] = val % MOD2

        # Compute column-wise hashes
        col_hash1 = [[0] * M for _ in range(N)]
        col_hash2 = [[0] * M for _ in range(N)]

        for j in range(M):
            for i in range(N):
                val = ord(grid[i][j]) - ord("a") + 1
                if i > 0:
                    col_hash1[i][j] = (col_hash1[i - 1][j] * base1 + val) % MOD1
                    col_hash2[i][j] = (col_hash2[i - 1][j] * base2 + val) % MOD2
                else:
                    col_hash1[i][j] = val % MOD1
                    col_hash2[i][j] = val % MOD2

        # Check all possible shifts
        for di in range(-N + 1, N):
            for dj in range(-M + 1, M):
                match = True
                # Check if the shifted grid matches the rotation
                for i in range(N):
                    for j in range(M):
                        ni, nj = N - 1 - i, M - 1 - j  # 180 degree rotation
                        oi, oj = i + di, j + dj  # Shifted position

                        if 0 <= oi < N and 0 <= oj < M:
                            if grid[oi][oj] != grid[ni][nj]:
                                match = False
                                break
                    if not match:
                        break

                if match:
                    # Calculate additional cells needed
                    add_rows = abs(di)
                    add_cols = abs(dj)
                    total = (N + add_rows) * (M + add_cols) - N * M
                    if total < min_additional:
                        min_additional = total

        print(min_additional if min_additional != float("inf") else -1)


if __name__ == "__main__":
    solve()
