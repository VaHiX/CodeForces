# Problem: CF 1772 F - Copy of a Copy of a Copy
# https://codeforces.com/contest/1772/problem/F

"""
Code Purpose:
This code solves the problem of reconstructing the sequence of operations performed on a binary matrix.
The operations include:
1. Recoloring a cell (if it's surrounded by 4 opposite-colored neighbors)
2. Making a copy of the current picture

The algorithm works as follows:
1. Parse all input pictures and calculate a 'score' for each based on the number of cells that meet the recoloring criteria (0 surrounded by all 1s or 1 surrounded by all 0s)
2. Sort the pictures in descending order of this score to determine which one is the initial (least modified), then apply operations step-by-step
3. Identify differences between consecutive pictures to determine which cells were recolored
4. For each copy operation, record it in the sequence

Algorithms/Techniques:
- Score calculation based on local neighborhood checks
- Sorting to identify initial state
- Difference detection between images to identify operations
- Simulation of operation sequence reconstruction

Time Complexity: O(n^2 * m^2 * k) in worst case where we process all pairs of pictures and check every cell
Space Complexity: O(n * m * k) to store all input pictures and results

"""

import sys

input = sys.stdin.readline


def calc(P):
    # Calculate score based on how many cells would be recolored (for each type of cell)
    a, b = 0, 0  # a counts zeros surrounded by ones, b counts ones surrounded by zeros

    # Iterate through cells that are not on the border (between 1 and n-1, 1 and m-1)
    for i in range(1, n - 1):
        for j in range(1, m - 1):
            z, o = False, False  # z=has zero neighbor, o=has one neighbor

            # Check all four neighbors (up, down, left, right)
            for ni, nj in [(i - 1, j), (i + 1, j), (i, j - 1), (i, j + 1)]:
                if P[ni][nj] == 0:
                    z = True
                else:
                    o = True

            # If no zero neighbor and current cell is 0 -> would be flipped
            if (not z) and P[i][j] == 0:
                a += 1

            # If no one neighbor and current cell is 1 -> would be flipped
            if (not o) and P[i][j] == 1:
                b += 1

    return (a, b)


n, m, k = map(int, input().split())
PS = []

# Read all k+1 pictures
for i in range(k + 1):
    input()  # consume empty line
    P = [list(map(int, list(input()[:-1]))) for _ in range(n)]  # read picture without trailing newline
    PS.append((i, P))  # store index and picture

# Sort pictures by descending score (higher score means more recoloring opportunities)
PS.sort(key=lambda t: calc(t[1]), reverse=True)
print(PS[0][0] + 1)  # print the index of initial picture (1-based)

ans = []

# Process each consecutive pair of pictures to determine operations
for i in range(k):
    P1 = PS[i][1]      # previous picture
    P2 = PS[i + 1][1]  # next picture

    # Find cells that differ between P1 and P2
    for j in range(n):
        for k in range(m):
            if P1[j][k] != P2[j][k]:  # if cell changed
                # Mark a recoloring operation at (j+1, k+1) due to difference
                ans.append((1, j + 1, k + 1))

    # Mark copy operation for the next picture
    ans.append((2, PS[i + 1][0] + 1))

print(len(ans))  # total number of operations

# Print each operation in required format
for i in range(len(ans)):
    print(*ans[i])


# https://github.com/VaHiX/CodeForces/