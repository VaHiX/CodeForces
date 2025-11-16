# Problem: CF 2073 A - Control Towers
# https://codeforces.com/contest/2073/problem/A

"""
Control Towers
Algorithms/Techniques: Dynamic Programming, Combinatorics, Preprocessing

Time Complexity: O(r * c)
Space Complexity: O(r + c)

The problem requires placing 4 control towers in empty cells such that consecutive towers
are in the same row or column. The solution preprocesses row and column counts of empty cells,
then iterates through all possible starting positions and computes valid combinations using
mathematical formulas to avoid brute-force enumeration.
"""

r, c = map(int, input().split())
g = [input().strip() for _ in range(r)]
rcnt = [0] * r  # Count of empty cells in each row
ccnt = [0] * c  # Count of empty cells in each column

# Preprocess: count empty cells in each row and column
for i in range(r):
    for j in range(c):
        if g[i][j] == ".":
            rcnt[i] += 1
            ccnt[j] += 1

ans = 0

# Process rows:
# For each row with at least 2 empty cells, calculate valid configurations
for i in range(r):
    R = rcnt[i]
    if R < 2:  # Not enough cells to form a valid path of 4 towers in same row
        continue
    s = 0      # Sum of (R + ccnt[j] - 3) for each empty cell in this row
    s2 = 0     # Sum of squares of (R + ccnt[j] - 3)
    for j in range(c):
        if g[i][j] == ".":
            f = R + ccnt[j] - 3  # Contribution to number of valid paths from this cell
            s += f
            s2 += f**2
    # Add contribution to answer using derived mathematical formula
    ans += s * s - s2 - R * (R - 1) * (R - 2)

# Process columns:
# For each column with at least 2 empty cells, calculate valid configurations
for j in range(c):
    C = ccnt[j]
    if C < 2:  # Not enough cells to form a valid path of 4 towers in same column
        continue
    s = 0      # Sum of (C + rcnt[i] - 3) for each empty cell in this column
    s2 = 0     # Sum of squares of (C + rcnt[i] - 3)
    for i in range(r):
        if g[i][j] == ".":
            f = C + rcnt[i] - 3   # Contribution to number of valid paths from this cell
            s += f
            s2 += f**2
    # Add contribution to answer using derived mathematical formula
    ans += s * s - s2 - C * (C - 1) * (C - 2)

print(ans)


# https://github.com/VaHiX/codeForces/