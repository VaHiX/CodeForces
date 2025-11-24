# Problem: CF 2005 E2 - Subtangle Game (Hard Version)
# https://codeforces.com/contest/2005/problem/E2

"""
Algorithm: Dynamic Programming with Preprocessing
Time Complexity: O(n * m + l)
Space Complexity: O(n * m + l)

This problem is a game theory problem where two players (Tsovak and Narek) take turns finding elements
of an array in a matrix, with the constraint that each subsequent choice must be in a submatrix
starting from (r+1, c+1) to (n, m). The key insight is to precompute for each row and column,
what is the rightmost valid position of an element such that it can be used as a next move.

The algorithm works as follows:
1. Preprocess the matrix to map each element to its column index in each row.
2. For each element in reverse order, compute for each row the latest valid column index 
   that can be used if we play this element.
3. This is done using a backward pass with a running maximum to track the rightmost valid index.
4. Finally, check if the first element in the array can be placed in the row such that a valid
   continuation exists.

The game can be solved by determining whether any valid path exists from the start to the end.
If Tsovak (the first player) can start with a move that leads to a winning strategy, he wins.
"""

import sys

input = sys.stdin.readline

t = int(input())
ansout = []
for _ in range(t):
    l, n, m = map(int, input().strip().split())
    a = list(map(int, input().strip().split()))
    b = [list(map(int, input().strip().split())) for _ in range(n)]

    # Preprocessing: Create a map of element -> column index for each row
    idx = []
    for b_i in b:
        idx_i = {}
        for j, b_ij in enumerate(b_i):
            idx_i[b_ij] = j
        idx.append(idx_i)

    # lb[i] will store the rightmost valid column index for row i.
    lb = [-1] * n
    # Process elements in reverse order
    for a_cur in a[n - 1 : 0 : -1]:
        for i in range(n):
            idx_i = idx[i].get(a_cur, -1)
            # If the element is not found, set to -1.
            # If the element exists but not beyond the current lb[i], set to -1.
            if idx_i < lb[i]:
                idx_i = -1
            lb[i] = idx_i
        lb_cur = -1
        # Update lb array backward to keep track of the maximum valid index for all rows.
        for i in range(n - 1, -1, -1):
            lb_i = lb[i]
            lb[i] = lb_cur
            lb_cur = max(lb_cur, lb_i)
    
    # Check if the first element can be placed such that a valid path exists.
    ans = (
        "T" if any(idx_i.get(a[0], -2) >= lb_i for lb_i, idx_i in zip(lb, idx)) else "N"
    )

    ansout.append(ans)

sys.stdout.write("\n".join(ansout))


# https://github.com/VaHiX/CodeForces/