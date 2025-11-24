# Problem: CF 1766 C - Hamiltonian Wall
# https://codeforces.com/contest/1766/problem/C

"""
Code Purpose:
This code determines whether a Hamiltonian path exists on a 2-row, m-column grid such that:
1. The path visits every black cell exactly once.
2. The path only moves through adjacent cells (sharing a side).
3. No white cells are visited.
4. Each column has at least one black cell.

The algorithm analyzes the pattern of black and white cells in each column:
- If both rows in a column are the same (both B or both W), the column is processed differently.
- If the rows in a column differ, the algorithm tracks a 'state' variable to determine how to proceed.
- The solution checks that there are at most 2 distinct 'types' of columns in the path (represented by the set s).

Algorithms/Techniques:
- Greedy approach with state tracking
- Column-by-column analysis
- Set-based tracking of column types

Time Complexity: O(m) where m is the number of columns
Space Complexity: O(1) as only a constant amount of extra space is used (set s and variables i, x)
"""

I = input
for _ in [0] * int(I()):
    I()  # Read m (number of columns), but don't use it
    s = {i := 0}  # Initialize a set s with 0, and i = 0
    for x in zip(I(), I()):  # Iterate over pairs of characters from two rows
        if x[0] == x[1]:  # If both cells in the column are the same
            i ^= 1  # Toggle the value of i (0 -> 1 or 1 -> 0)
        else:  # If cells in the column differ
            s |= {x[i]}  # Add the character from the row determined by i to set s
    print("YNEOS"[len(s) > 2 :: 2])  # Print YES if len(s) <= 2, otherwise NO


# https://github.com/VaHiX/CodeForces/