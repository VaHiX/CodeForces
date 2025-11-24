# Problem: CF 1699 E - Three Days Grace
# https://codeforces.com/contest/1699/problem/E

"""
Algorithm: Dynamic Programming with Factorization
Time Complexity: O(m * sqrt(m) + m)
Space Complexity: O(m)

This solution uses dynamic programming to determine the minimum possible balance
after performing factorization operations on the elements of the multiset.

The key idea is to use a dp array where dp[i] represents the minimum value that
element i can be reduced to through factorization. We iterate from large values
down to small, updating dp values for multiples of current i. The balance is
then determined by the difference between the maximum and minimum values in the
final state, optimized across all possible reductions.
"""

for _ in range(int(input())):
    n, m = list(map(int, input().split()))
    data = [0] * (m + 1)  # Tracks presence of elements in the multiset
    trace = [0] * (m + 1)  # Tracks how many elements there are of each value
    mn, mx = m, 0  # Track minimum and maximum values in the multiset
    for el in input().split():
        data[int(el)] = 1
        trace[int(el)] = 1
        mn = min(mn, int(el))
        mx = max(mx, int(el))
    dp = [*range(mx + 1)]  # Initialize dp with identity mapping
    ptr = mx  # Pointer to track current maximum value with elements
    dist = mx - mn  # Initial distance (balance)
    for i in range(mx, 0, -1):  # Traverse from max to 1
        for j in range(i**2, mx + 1, i):  # For all multiples of i
            if data[j] == 1:
                trace[dp[j]] -= 1  # Remove old dp value from trace
            dp[j] = min(dp[j], dp[j // i])  # Update dp value
            if data[j] == 1:
                trace[dp[j]] += 1  # Add new dp value to trace
        while trace[ptr] == 0:  # Find next valid upper bound
            ptr -= 1
        if i <= mn:  # Only consider valid start points
            dist = min(dist, ptr - i)  # Update minimum balance
    print(dist)


# https://github.com/VaHiX/CodeForces/