# Problem: CF 1699 D - Almost Triple Deletions
# https://codeforces.com/contest/1699/problem/D

"""
Algorithm: Dynamic Programming with State Tracking
Techniques: 
- State compression using a dp array where dp[i] represents the maximum number of operations ending at index i
- Two-pointer approach to find valid pairs for deletion
- Frequency tracking to determine maximum count of any element in a segment

Time Complexity: O(n^2) where n is the length of the array
Space Complexity: O(n) for the dp array and auxiliary arrays

This solution simulates the deletion process by tracking the maximum number of valid operations 
that can be performed to reduce the array to equal elements. It uses dynamic programming to 
track the best result up to each index, updating based on valid adjacent pair deletions.
"""

I = input
for _ in [0] * int(I()):
    n = int(I())
    # Add sentinel values at start and end to simplify boundary handling
    a = [0] + I().split() + [0]
    # dp[i] stores the maximum number of operations possible ending at index i
    dp = [0] + [-1] * (n + 1)
    for i in range(n + 1):
        # Skip if this index hasn't been reached in any valid operation sequence
        if dp[i] == -1:
            continue
        # f[v] tracks frequency of each value in current segment
        f, mxf = [0] * (n + 1), 0
        for j in range(i + 1, n + 2):
            # Check if (j - i) is odd, meaning we have an odd number of elements between i and j
            # and the max frequency in segment is within the limit (half of the segment length)
            # and either we are at a sentinel (0) or the elements match
            if (
                (j - i) & 1
                and mxf <= (j - i) // 2
                and (a[i] == 0 or a[j] == 0 or a[j] == a[i])
            ):
                # Update dp[j] with maximum operations if a new valid sequence is found
                dp[j] = max(dp[j], dp[i] + 1)
            # Update frequency of element at index j
            if a[j] != 0:
                v = int(a[j])
                f[v] += 1
                mxf = max(mxf, f[v])
    # Subtract 1 because the initial state is counted as one operation
    print(dp[n + 1] - 1)


# https://github.com/VaHiX/CodeForces/