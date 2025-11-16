# Problem: CF 1799 D1 - Hot Start Up (easy version)
# https://codeforces.com/contest/1799/problem/D1

"""
Algorithm: Dynamic Programming with State Tracking
Time Complexity: O(n * k)
Space Complexity: O(k)

This solution uses dynamic programming to track the minimum time needed to run all programs,
considering the hot start optimization. For each program, we determine whether it's a hot start
(i.e., the same as the previous program on the same CPU) or a cold start. We maintain a cost array
to track the minimum time to reach each program and update the total time accordingly.

The algorithm tracks two key things:
1. The cumulative time needed to run all programs, considering hot/cold start times.
2. The minimum prefix cost for each program type to determine the best CPU assignment.

We use an array 'L' to store the minimum cost to reach a program type,
and 'V' to track which program types have been seen.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def print(*values, sep=" ", end="\n"):
    sep = str(sep)
    end = str(end)
    for i in range(len(values) - 1):
        sys.stdout.write(str(values[i]))
        sys.stdout.write(sep)
    if values:
        sys.stdout.write(str(values[-1]))
    sys.stdout.write(end)


test = int(input().decode())
for testtest in range(test):

    n, k = map(int, input().decode().split())
    N = list(map(int, input().decode().split()))
    C = list(map(int, input().decode().split()))
    H = list(map(int, input().decode().split()))

    V = [0] * (k + 1)  # Track seen programs
    V[0] = 1  # Initialize
    V[N[0]] = 1  # Mark first program as seen

    co = C[N[0] - 1]  # Initial cost for first program

    L = [0] * (k + 1)  # Minimum cost to reach each program type

    mins = 0

    for i in range(1, n):
        if N[i - 1] == N[i]:  # Same program as previous -> hot start
            co += H[N[i] - 1]
        else:  # Different program -> cold start
            co += C[N[i] - 1]
            L[N[i - 1]] = mins  # Store the current minimum prefix cost
            
            # If the current program has been seen before, adjust cost accordingly
            if V[N[i]]:
                L[N[i - 1]] = min(L[N[i - 1]], L[N[i]] + H[N[i] - 1] - C[N[i] - 1])

            mins = min(mins, L[N[i - 1]])  # Update the minimum

        V[N[i]] = 1  # Mark current program as seen

    mins = 1e15  # Reset mins to large number

    # Find minimum cost among all seen programs
    for i in range(k + 1):
        if V[i] == 0:
            continue  # Skip unseen programs
        mins = min(L[i], mins)

    print(mins + co)


# https://github.com/VaHiX/CodeForces/