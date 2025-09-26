# Problem: CF 2127 C - Trip Shopping
# https://codeforces.com/contest/2127/problem/C

"""
C. Trip Shopping

Purpose:
This code solves a game between Ali and Bahamin where they play k rounds to optimize the sum of absolute differences between two arrays a and b. 
Ali wants to minimize the final value v = sum(|a[i] - b[i]|), while Bahamin wants to maximize it.

Algorithms/Techniques:
- Greedy strategy with sorting
- Optimal assignment of elements in each round to either minimize or maximize the cost

Time Complexity: O(n log n) per test case due to sorting step
Space Complexity: O(n) for storing the array of pairs and auxiliary variables

The approach uses a greedy idea that, in each round:
1. Ali selects two indices to try to reduce difference.
2. Bahamin rearranges elements to either maximize or minimize the final sum based on their goal.

This greedy strategy works because Bahamin can always assign values optimally for maximizing.
"""

t = int(input())
for _ in range(t):
    n, k = list(map(int, input().split()))
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    ans = 0
    c = []
    # Calculate initial total difference and store min/max pairs for each index
    for i in range(0, n):
        ans += abs(a[i] - b[i])
        c.append([min(a[i], b[i]), max(a[i], b[i])])
    
    # Sort by the maximum value of each pair to enable greedy selection
    c.sort(key=lambda x: x[1])
    
    mi = 10**18  # Initialize minimum possible increment
    
    # Check for overlaps in intervals and compute optimal gain
    for i in range(1, n):
        if c[i][0] < c[i - 1][1]:
            # Overlapping intervals => can make difference 0
            mi = 0
            break
        # Compute potential improvement from non-overlapping interval
        mi = min(mi, 2 * (c[i][0] - c[i - 1][1]))
    
    print(ans + mi)


# https://github.com/VaHiX/codeForces/