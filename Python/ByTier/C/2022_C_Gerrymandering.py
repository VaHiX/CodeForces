# Problem: CF 2022 C - Gerrymandering
# https://codeforces.com/contest/2022/problem/C

"""
C. Gerrymandering

Purpose:
This code solves a problem where we have a 2xN grid (N is multiple of 3) and need to divide it into districts of 3 connected cells.
Each district votes for candidate A (Álvaro) if at least 2 of its 3 cells are A, otherwise it votes for J (José).
The goal is to maximize the number of districts that vote for A by optimally choosing how to form the districts.

Algorithms:
Dynamic Programming with states representing the last few columns processed and which district type was used.
We use a DP state dp[k][i] where k is the current column index, i is a state indicating previous district configuration,
and the value represents max votes for A up to that point.

Time Complexity: O(n)
Space Complexity: O(n)

State transitions are handled based on possible configurations of districts in the last few columns.
The district types are encoded as:
0: three consecutive cells in same row
1: two cells in row 0, one in row 1 (or vice versa)
2: two cells in row 1, one in row 0 (or vice versa)

"""

from sys import stdin

input = stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    vot = [[0] * (n + 5) for _ in range(2)]
    for i in range(2):
        tmp = input()
        for j in range(n):
            if tmp[j] == "A":
                vot[i][j + 1] = 1
    dp = [[-1] * 3 for _ in range(n + 5)]
    dp[0][0] = 0
    for k in range(n):
        for i in range(3):
            if dp[k][i] != -1:
                val = dp[k][i]
                if i == 0:
                    # Case 0: Previous was a vertical trio (same column, row 0 and row 1 both have A in this district)
                    vt = (vot[0][k + 1] + vot[0][k + 2] + vot[0][k + 3]) // 2 + (
                        vot[1][k + 1] + vot[1][k + 2] + vot[1][k + 3]
                    ) // 2
                    dp[k + 3][0] = max(dp[k + 3][0], val + vt)
                    # Case 1: One cell from row 0 and two from row 1 (but this is valid for a district starting at column k+1)  
                    vt = (vot[0][k + 1] + vot[0][k + 2] + vot[1][k + 1]) // 2
                    dp[k + 1][1] = max(dp[k + 1][1], val + vt)
                    # Case 2: One cell from row 1 and two from row 0 (but this is valid for a district starting at column k+1)  
                    vt = (vot[1][k + 1] + vot[1][k + 2] + vot[0][k + 1]) // 2
                    dp[k + 1][2] = max(dp[k + 1][2], val + vt)
                elif i == 1:
                    # Case 1: Previous district was from row 0 to row 1 (two in row 0, one in row 1 or vice versa)
                    vt = (vot[0][k + 2] + vot[0][k + 3] + vot[0][k + 4]) // 2 + (
                        vot[1][k + 1] + vot[1][k + 2] + vot[1][k + 3]
                    ) // 2
                    dp[k + 3][1] = max(dp[k + 3][1], val + vt)
                    # Move 2 columns to reset with case 0 (i.e., start of new trio)
                    vt = (vot[1][k + 1] + vot[1][k + 2] + vot[0][k + 2]) // 2
                    dp[k + 2][0] = max(dp[k + 2][0], val + vt)
                elif i == 2:
                    # Case 2: Another variant of districts starting from row 1 (two in row 1, one in row 0 or vice versa)
                    vt = (vot[0][k + 1] + vot[0][k + 2] + vot[0][k + 3]) // 2 + (
                        vot[1][k + 2] + vot[1][k + 3] + vot[1][k + 4]
                    ) // 2
                    dp[k + 3][2] = max(dp[k + 3][2], val + vt)
                    # Move 2 columns to reset with case 0
                    vt = (vot[0][k + 1] + vot[0][k + 2] + vot[1][k + 2]) // 2
                    dp[k + 2][0] = max(dp[k + 2][0], val + vt)
    print(dp[n][0])


# https://github.com/VaHiX/codeForces/