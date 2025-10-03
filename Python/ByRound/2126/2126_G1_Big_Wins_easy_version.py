# Problem: CF 2126 G1 - Big Wins! (easy version)
# https://codeforces.com/contest/2126/problem/G1

"""
G1. Big Wins! (easy version)

Purpose:
This code solves the problem of finding the maximum value of (median - minimum) over all possible subarrays of a given array.

Algorithms/Techniques:
- Brute force with optimization using prefix/suffix arrays and sorting
- For each unique value in descending order, compute the best subarray median-minimum difference
- Uses prefix and suffix arrays to efficiently check valid subarrays
- Time complexity: O(n^2 * log n), Space complexity: O(n)

Time and Space Complexity:
Time: O(n^2 * log n) where n is the size of input array. The algorithm checks all unique values and for each performs a scan with prefix/suffix computations.
Space: O(n) used for storing arrays and auxiliary structures.
"""

def solve():
    n = int(input())
    a = [int(i) for i in input().split()]
    if n == 1:
        print(0)
        return
    mn = min(a)
    ans = 0
    s = sorted(set(a), reverse=True)
    for v in s:
        # Skip if current value is less than or equal to minimum, or the gain is not beneficial
        if v <= mn or v - mn <= ans:
            break
        # Compute prefix sum array; +1 if element >= v, -1 otherwise
        pref = [0] * (n + 1)
        for i in range(n):
            pref[i + 1] = pref[i] + (1 if a[i] >= v else -1)
        # Precompute minimum prefix values
        pref_min = [0] * (n + 1)
        pref_min[0] = pref[0]
        for i in range(1, n + 1):
            pref_min[i] = pref_min[i - 1] if pref_min[i - 1] < pref[i] else pref[i]
        # Precompute maximum suffix values
        suff_max = [0] * (n + 1)
        suff_max[n] = pref[n]
        for i in range(n - 1, -1, -1):
            suff_max[i] = pref[i] if pref[i] > suff_max[i + 1] else suff_max[i + 1]
        m_min = float("inf")
        # Check each possible subarray ending at position k
        for k in range(1, n + 1):
            # If the suffix maximum is greater than or equal to prefix minimum,
            # then it's valid to consider this end point
            if suff_max[k] >= pref_min[k - 1]:
                m_min = min(a[k - 1], m_min)
        # Update global answer with difference between current value and minimum element seen
        ans = max(ans, v - m_min)
    print(ans)


if __name__ == "__main__":
    t = int(input())
    for _ in range(t):
        solve()


# https://github.com/VaHiX/codeForces/