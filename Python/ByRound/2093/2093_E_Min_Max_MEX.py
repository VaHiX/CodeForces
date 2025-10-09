# Problem: CF 2093 E - Min Max MEX
# https://codeforces.com/contest/2093/problem/E

"""
E. Min Max MEX

Purpose:
This code solves the problem of splitting an array into exactly k non-overlapping subarrays such that the minimum MEX (minimum excludant) among all subarrays is maximized.

Algorithm:
- The solution uses binary search on the answer (the value of x, i.e., minimum MEX)
- For each candidate value x, it checks if we can partition the array into k subarrays such that each subarray has MEX >= x
- To check feasibility, it greedily assigns elements to subarrays by ensuring no subarray contains all values from 0 to (x - 1)

Time Complexity: O(N * log(N)) per test case, where N is the size of array.
Space Complexity: O(N) for storing the array and auxiliary variables.

"""

import sys

input = sys.stdin.readline
Q = int(input())
for _ in range(Q):
    N, K = map(int, input().split())
    A = list(map(int, input().split()))
    l = 0
    r = N
    while True:
        if l == r:
            break
        m = (l + r + 1) // 2  # Midpoint for binary search
        v = [0] * m  # Tracks which group each element value belongs to
        x = m  # Number of remaining slots in current window
        count = 0  # Number of complete segments processed
        for i in range(N):
            y = A[i]
            if y >= m:
                continue  # Skip elements that are too large for this MEX check
            if v[y] == count:  # If current element hasn't been assigned yet
                v[y] = count + 1  # Assign it to next group
                x -= 1  # One less slot available
                if x == 0:  # Current window is full
                    count += 1  # Move to next segment
                    x = m  # Reset slots for new window
        if count >= K:
            l = m  # Feasible, try higher value of MEX
        else:
            r = m - 1  # Not feasible, reduce the MEX value
    print(l)


# https://github.com/VaHiX/codeForces/