# Problem: CF 2169 C - Range Operation
# https://codeforces.com/contest/2169/problem/C

from itertools import accumulate

# Flowerbox: 
# Purpose: This code solves the problem of maximizing the sum of an array after at most one operation.
#          The operation allows choosing a subarray [l, r] and replacing all elements in it with (l + r).
# Algorithm: 
#   - Use prefix sums to efficiently calculate subarray sums.
#   - For each possible end position i of a subarray, compute the best possible gain from applying the operation
#     starting from any previous position.
#   - Maintain a maximum value of (prefix_sum[i-1] + i - i*i) to determine optimal start point.
# Time Complexity: O(n) per test case, where n is the length of the array.
# Space Complexity: O(n) for storing the prefix array.

for _ in range(int(input())):
    n = int(input())
    arr = [*map(int, input().split())]
    pref = [0, *accumulate(arr)]  # Prefix sum array
    ans = mx = 0
    for i in range(1, n + 1):
        # Update the maximum value for potential start positions
        mx = max(mx, pref[i - 1] + i - i * i)
        # Calculate the maximum possible sum considering the current subarray end
        ans = max(ans, pref[-1] + mx - pref[i] + i * i + i)
    print(ans)


# https://github.com/VaHiX/CodeForces/