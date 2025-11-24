# Problem: CF 1995 B1 - Bouquet (Easy Version)
# https://codeforces.com/contest/1995/problem/B1

"""
B1. Bouquet (Easy Version)
Algorithms/Techniques: Sliding Window
Time Complexity: O(n log n) per test case due to sorting; O(n) for the sliding window.
Space Complexity: O(1) not counting input storage.

This problem asks us to find the maximum sum of petals in a bouquet such that:
1. The difference between the maximum and minimum number of petals in the bouquet is at most 1.
2. The total cost (sum of petals) does not exceed m coins.

We use a sliding window approach:
- Sort the flowers by the number of petals.
- Use two pointers (l and r) to maintain a valid window where all elements differ by at most 1.
- Keep track of the sum of elements in the current window.
- Update the maximum sum found so far.
"""

for _ in range(int(input())):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    a.sort()
    l, r, s = 0, 0, 0
    ans = 0
    while r < n:
        s += a[r]  # Add current element to the window sum
        # Shrink window from left while it's invalid:
        # - Difference between a[r] and a[l] exceeds 1,
        # - Or total sum exceeds k (budget).
        while l < n and (a[r] - a[l] > 1 or s > k):
            s -= a[l]
            l += 1
        ans = max(ans, s)  # Update maximum sum found so far
        r += 1
    print(ans)


# https://github.com/VaHiX/codeForces/