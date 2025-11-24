# Problem: CF 1811 G1 - Vlad and the Nice Paths (easy version)
# https://codeforces.com/contest/1811/problem/G1

"""
Algorithm: Dynamic Programming with Segment-based Counting
Time Complexity: O(n^2 * k) per test case
Space Complexity: O(n * k) per test case

The solution works by:
1. Identifying all valid starting positions for blocks of size k with same colors
2. Building a graph of valid transitions between these positions
3. Using dynamic programming to count paths of maximum length
4. Applying modular arithmetic for large results
"""

from sys import stdin

input = lambda: stdin.readline()[:-1]
t = int(input())
for u in range(0, t):
    n, k = map(int, input().split())
    c = list(map(int, input().split()))
    data1 = [-1] * n  # For each position i, stores the end of the block starting at i
    data2 = []  # Stores valid [start, end] intervals
    for i in range(0, n):
        j = i  # Start searching from position i
        p = 0  # Counter for consecutive same colors
        while True:
            if c[j] == c[i]:
                p += 1
            if p == k:  # Found a block of k same-colored tiles
                data1[i] = j
                break
            j += 1
            if j >= n:  # If we reach end of array
                break
    for i in range(0, n):
        if data1[i] >= 0:  # If a valid block was found starting at i
            data2.append([i, data1[i]])
    data2.sort(key=lambda x: x[1])  # Sort intervals by end position
    
    out = 0  # Initialize count of non-overlapping intervals
    r = -1  # Rightmost end position of selected interval
    for w in data2:
        if w[0] > r:  # If this interval doesn't overlap with previous ones
            out += 1
            r = w[1]
    m = out * k  # Maximum path length possible
    if out == 0:  # If no block found
        print(1)
        continue
    if k == 1:  # Trivial case
        print(1)
        continue
        
    # Dynamic Programming approach for counting paths
    d1 = [1] * n  # Current state
    d2 = [-1] * n  # Next state
    for i in range(2, m + 1):
        sum_ = [0] * (n + 1)  # Running sum for current color
        sum1 = 0  # Running sum of all valid paths so far
        for j in range(0, n - 1):
            sum1 += d1[j]  # Accumulate paths ending at j
            sum1 %= 1000000007  # Apply modulo
            sum_[c[j]] += d1[j]  # Add to color-specific running sum
            sum_[c[j]] %= 1000000007
            if i % k == 1:  # If we're at start of new block
                d2[j + 1] = sum1  # Paths ending at j+1
            else:  # Else, extend path based on color constraint
                d2[j + 1] = sum_[c[j + 1]]
        d2[0] = 0  # Reset index 0
        d1 = list(map(int, d2))  # Update previous state
        d2 = [-1] * n  # Reset next state
    print(sum(d1) % 1000000007)  # Return total count modulo 1e9+7


# https://github.com/VaHiX/CodeForces/