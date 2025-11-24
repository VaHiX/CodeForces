# Problem: CF 2148 F - Gravity Falls
# https://codeforces.com/contest/2148/problem/F

"""
Problem: Gravity Falls

Purpose:
This code solves a problem where Farmer John stacks multiple arrays (which may have different lengths) into a grid.
After stacking, gravity causes elements to fall down until the arrangement is stable.
The goal is to find the lexicographically smallest possible bottom row among all possible stackings.

Approach:
- For each column position, we greedily select the minimum value from the available top elements of arrays that haven't fully been processed yet.
- We process columns one by one and simulate gravity by ensuring that only the valid rows which can still contribute to the next step are kept.
- This greedy selection mimics how gravity would naturally pull elements downward while maintaining lexicographical order.

Algorithms/Techniques:
- Greedy algorithm
- Simulation of gravity effect in a stacked array structure

Time Complexity:
O(N * K), where N is the number of arrays and K is the maximum length among all arrays.
Each element in the arrays is considered at most once across all steps.

Space Complexity:
O(N * K), due to storage for input arrays and auxiliary data structures like G (graph representation),
v (lengths), h (active indices), and result list.

"""

import sys

input = sys.stdin.readline
Q = int(input())
for _ in range(Q):
    N = int(input())
    G = [[] for i in range(N)]
    z = 0
    v = [0] * N
    for i in range(N):
        A = list(map(int, input().split()))
        K = A[0]
        A = A[1:]
        G[i] = A[:]  # Store each array's elements
        z = max(z, K)  # Track maximum length of arrays
        v[i] = K       # Store length for each row
    result = []
    h = [i for i in range(N)]  # Initially all rows are active
    for i in range(z):  # For each column index up to max length
        x = 10**10  # Initialize with large value to get min
        for pos in h:  # Check current active rows
            x = min(x, G[pos][i])  # Find minimum among active rows at this column
        ans = True
        h2 = []  # New set of active rows after this step
        result.append(x)  # Add minimum to result (this will be part of final row)
        for pos in h:  # Iterate over rows still active
            if v[pos] == i + 1 and G[pos][i] == x:
                # If this row was fully consumed but element equals x, it means we've reached the end and shouldn't proceed further
                ans = False
                break
            if G[pos][i] == x:
                # If current element matches minimum, it contributes to next steps, keep that row
                h2.append(pos)
        h = h2[:]  # Update active rows for next step
        if ans == False:
            # If no element was chosen or all remaining rows had all elements used up
            h = []
            for j in range(N):
                # Re-add any rows that still have unprocessed elements (i + 1 is the index of current column being considered)
                if v[j] > i + 1:
                    h.append(j)
    print(*result)


# https://github.com/VaHiX/codeForces/