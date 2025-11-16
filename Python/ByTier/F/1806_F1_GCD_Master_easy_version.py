# Problem: CF 1806 F1 - GCD Master (easy version)
# https://codeforces.com/contest/1806/problem/F1

"""
Algorithm: GCD Master (Easy Version)
Purpose:
    Given an array of integers, perform exactly k operations where each operation
    selects two elements, computes their GCD, appends the GCD to the array, and removes
    the two selected elements. Goal is to maximize the sum of the final array.

Approach:
    1. Preprocess the count of each number in the array.
    2. For each possible GCD value (from 1 to m), compute the maximum sum of the array
       that can be achieved if we only consider numbers divisible by this GCD.
       This is done by iterating through multiples of the GCD and removing the smallest
       elements to maximize sum.
    3. Then, use dynamic programming to precompute optimal values.
    4. Finally, iterate over all numbers and simulate choosing specific GCDs and
       calculate contribution to final sum.

Time Complexity: O(m * (m + n))
Space Complexity: O(m + n)

Techniques Used:
    - Prefix sum and GCD preprocessing
    - Dynamic Programming
    - Greedy approach for optimization
"""

t = int(input())
for _ in range(t):
    n, m, k = map(int, input().split())
    a = list(map(int, input().split()))
    cnt = [0] * (m + 1)
    for x in a:
        cnt[x] += 1
    tot = sum(a)

    # DP[i] stores the maximum sum achievable with at most i operations
    DP = [0] * (n + 1)
    for gc in range(1, m + 1):
        remsum = tot + gc  # Initial sum including the new GCD value
        used = 0
        for x in range(gc, m + 1, gc):
            if cnt[x] == 0:
                continue
            used += 1
            remsum -= x  # Remove one element to maximize sum
            DP[used] = max(DP[used], remsum)
    ans = DP[k + 1]  # Take the best sum for k+1 elements
    ctx, base = 0, 0
    for x in range(1, m + 1):
        for rep in range(cnt[x] - 1):
            ctx += 1
            base += x
            if ctx <= k + 1:
                ans = max(ans, DP[k + 1 - ctx] - base)
    print(ans)


# https://github.com/VaHiX/CodeForces/