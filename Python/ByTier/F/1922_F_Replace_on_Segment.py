# Problem: CF 1922 F - Replace on Segment
# https://codeforces.com/contest/1922/problem/F

"""
Algorithm: Dynamic Programming with Segment-based Minimization
Time Complexity: O(n^3 * x) where n is the array length and x is the range of values
Space Complexity: O(n^2 * x) for the DP tables

The approach uses dynamic programming to find the minimum operations needed to make all elements equal.
It considers all possible target values and computes the minimum operations required to convert the array to that value.
The core idea is to split the array into segments and use DP to compute the cost of making each segment uniform.
"""

INF = float("inf")
for _ in range(int(input())):
    n, x = map(int, input().split())
    a = list(map(lambda y: int(y) - 1, input().split()))  # Convert to 0-based indexing
    dp1 = [[0] * (n + 1) for _ in range(n + 1)]  # dp1[l][r] stores min operations for subarray [l,r]
    for r in range(n + 1):
        dp2 = [[0] * x for _ in range(r + 1)]  # dp2[l][k] stores min operations to make [l,r) all k
        dp2[-1] = [1] * x  # Base case: if l == r, we need 1 operation to change to any value
        for l in reversed(range(r)):
            for k in range(x):
                # If k is not the value at l, we can use it, otherwise it's invalid
                dp2[l][k] = min(dp2[l + 1][k], dp1[l + 1][r] + 1) if k != a[l] else INF
            for c in range(l + 1, r):
                # If a[c-1] is the value of element at c-1, then we can update dp2[l][a[c-1]]
                # This considers splitting subsegment [l,r] at position c and combining results
                dp2[l][a[c - 1]] = min(dp2[l][a[c - 1]], dp1[l][c] + dp2[c][a[c - 1]])
            dp1[l][r] = min(dp2[l][k] for k in range(x))  # Find min over all possible values k
    
    result = INF
    for k in range(x):
        dp3 = [INF] * (n + 1)  # dp3[i] = min operations to make first i elements all k
        dp3[0] = 0  # Zero operations to make empty prefix all k
        for i in range(n):
            if a[i] == k:
                # If current element is already k, no extra operation needed
                dp3[i + 1] = min(dp3[i + 1], dp3[i])
            for j in range(i + 1, n + 1):
                # Try using a subsegment [i, j) to make all elements k
                dp3[j] = min(dp3[j], dp3[i] + dp1[i][j])
        result = min(result, dp3[-1])  # Update global minimum
    
    print(result)


# https://github.com/VaHiX/CodeForces/