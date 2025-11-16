# Problem: CF 1732 C1 - Sheikh (Easy version)
# https://codeforces.com/contest/1732/problem/C1

"""
Algorithm: 
This problem requires finding a subsegment [l, r] within a given range [L, R] that maximizes the function f(l, r) = sum(l, r) - xor(l, r).
The key insight is to compute prefix sums and prefix XORs to efficiently calculate range sum and XOR in O(1) time.
We use binary search to optimize the selection of right boundary r for a fixed left boundary l.
Time Complexity: O(n log n) due to the binary search over the array elements for each possible left boundary.
Space Complexity: O(n) for storing prefix sums and prefix XORs arrays.
"""
import sys

input = sys.stdin.readline
t = int(input())

for _ in [0] * t:
    n, q = map(int, input().split())
    a = list(map(int, input().split()))
    L, R = map(int, input().split())
    # Create prefix sum array
    sum = [0] + a[::1]
    # Create prefix xor array
    xor = [0] + a[::1]
    # Compute prefix sums and prefix xors
    for i in range(1, n + 1):
        sum[i] += sum[i - 1]
        xor[i] ^= xor[i - 1]

    # Calculate maximum possible value of f(l, r) for entire array
    ans = sum[-1] - xor[-1]
    # If maximum value is 0, any single element subarray gives optimal result
    if ans == 0:
        print(1, 1)
        continue
    # Initialize minimum length and the corresponding interval 
    mn = [float("inf"), -1, -1]
    # Iterate over all possible left boundaries
    for i in range(1, n):
        l = i
        r = n
        # Binary search for the right boundary that achieves the max value
        while r - l > 1:
            m = (r + l) // 2
            # Calculate the value of f(i-1, m) 
            tmp = sum[m] - sum[i - 1] - (xor[m] ^ xor[i - 1])
            if tmp == ans:
                r = m
            else:
                l = m

        # Check if the current interval achieves the maximum value and has a smaller length
        if sum[r] - sum[i - 1] - (xor[r] ^ xor[i - 1]) == ans and mn[0] > r - i:
            mn = [r - i, i, r]
    print(mn[1], mn[2])


# https://github.com/VaHiX/CodeForces/