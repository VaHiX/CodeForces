# Problem: CF 2154 E - No Mind To Think
# https://codeforces.com/contest/2154/problem/E

"""
Algorithm: 
- The problem involves finding the maximum possible sum after performing at most k operations on an array.
- Each operation selects a subsequence of length x (odd) and replaces all elements in it with the median of that subsequence.
- To optimize, we sort the array and use prefix sums for efficient computation.
- For each possible median position idx, we perform a binary search to find the optimal subsequence length y that maximizes the gain.
- Time Complexity: O(n^2 * log n) in worst case due to nested loops and binary search, but optimized with prefix sums.
- Space Complexity: O(n) for the prefix sum array.

Approach:
- Sort the array to enable greedy logic and prefix sum computation.
- For each potential median index, compute optimal gain using binary search over possible subsequence lengths.
- Use prefix sums to quickly compute sum of ranges, reducing time for delta calculation.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()


def solve_case():
    n, k = map(int, input().split())
    a = sorted(map(int, input().split()))

    # Compute prefix sums for efficient range sum queries
    ps = [0] * (n + 1)
    for i in range(n):
        ps[i + 1] = ps[i] + a[i]

    # Function to compute the net gain/loss for choosing a median at 'idx' with subsequence length 'y'
    def delta(idx, y):
        # j is the index in the sorted array where subsequence ends, ensuring valid window
        j = min(k * y - 1, idx - 1)
        # gain: increase if we replace elements before idx with median at idx
        gain = (j + 1) * a[idx] - ps[j + 1]
        # loss: decrease if we replace elements after idx with median at idx
        loss = ps[idx + y + 1] - ps[idx + 1] - y * a[idx]
        return gain - loss

    ans = 0
    # Iterate over each possible median position (avoiding borders)
    for idx in range(1, n - 1):
        # Determine valid range for y: subsequence size must be odd and fit in array
        y_min, y_max = 0, min(idx, n - 1 - idx)
        lo, hi = y_min, y_max
        # Binary search to find optimal y
        while lo < hi:
            mid = (lo + hi) // 2
            # Compare gain of mid vs mid+1 to decide which direction to move
            if delta(idx, mid) < delta(idx, mid + 1):
                lo = mid + 1
            else:
                hi = mid
        # Keep track of maximum gain
        ans = max(ans, delta(idx, lo))
    
    # Return total sum plus maximum gain
    return sum(a) + ans


ans = []
for _ in range(int(input())):
    ans.append(str(solve_case()))
print("\n".join(ans))


# https://github.com/VaHiX/CodeForces/