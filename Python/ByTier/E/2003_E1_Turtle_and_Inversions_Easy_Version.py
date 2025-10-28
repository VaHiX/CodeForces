# Problem: CF 2003 E1 - Turtle and Inversions (Easy Version)
# https://codeforces.com/contest/2003/problem/E1

"""
Algorithm: Dynamic Programming with Optimization
Time Complexity: O(n^2) per test case
Space Complexity: O(n) per test case

The approach uses dynamic programming where we process intervals sequentially.
For each interval, we compute the maximum number of inversions that can be achieved
by placing elements in a way that satisfies the constraints on `a_i` and `b_i`.

Key steps:
1. Process intervals in order, merging overlapping or adjacent intervals.
2. For each interval, evaluate all valid placements of elements to maximize inversions.
3. Use a DP table `vault` to track the maximum inversions achievable up to a certain point.
4. For each interval, generate valid configurations and update the DP accordingly.

This version handles the constraint r_i < l_{i+1} efficiently by processing intervals
as non-overlapping segments.
"""

ans = []
for _ in range(int(input())):
    n, m = [int(x) for x in input().split()]
    spear = list(range(n))  # Initialize spear with identity mapping
    for _ in range(m):
        L, R = [int(x) - 1 for x in input().split()]  # Convert to 0-indexed
        spear[L] = R  # spear[i] stores the right boundary of the interval starting at i

    vault = [-1] * n  # DP array storing max inversions for each starting index
    vault[0] = 0      # Base case: zero inversions at start
    L = 0             # Current start of interval

    while L < n:
        R = spear[L]  # Get the right boundary of current interval
        nv = [-1] * n  # New DP array for next state
        pairs = []

        if L == R:
            # Single element interval, only one way to place
            pairs = [(1, 0), (0, 1)]
        else:
            # Generate all valid (small, big) assignments for the interval
            for i in range(R - L):
                pairs.append((R - L - i, 1 + i))

        # Process all valid pairs for current interval
        for small, big in pairs:
            for i in range(n - big):
                if vault[i] == -1:
                    continue  # Skip invalid states

                # Calculate new number of inversions
                new = (
                    vault[i]
                    + small * (small - 1) // 2
                    + big * (big - 1) // 2
                    + small * L
                    + big * i
                )
                # Update new state in nv array
                nv[i + big] = max(nv[i + big], new)

        vault = nv  # Move to next state
        L = R + 1   # Move to next interval

    ans.append(max(vault))  # Maximum inversions among all valid permutations

for w in ans:
    print(w)


# https://github.com/VaHiX/CodeForces/