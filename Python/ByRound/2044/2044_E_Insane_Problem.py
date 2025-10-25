# Problem: CF 2044 E - Insane Problem
# https://codeforces.com/contest/2044/problem/E

"""
E. Insane Problem

Task: Count the number of ordered pairs (x, y) such that:
- l1 <= x <= r1
- l2 <= y <= r2
- There exists a non-negative integer n such that y/x = k^n

Algorithm:
For each valid value of n (where k^n is computed iteratively), we determine how many
pairs (x, y) satisfy the constraints. The key observation is that for fixed n,
y = x * k^n, so we can iterate over valid x values and check if corresponding y
falls within [l2, r2]. 

We use a while loop to generate powers of k until k^n exceeds r2.
For each such power, we compute the range of valid x values using inclusion-exclusion
principle, then count how many x in [l1, r1] also satisfy y in [l2, r2].

Time Complexity: O(log(r2) * log_k(r2)) or effectively O(log(r2))
Space Complexity: O(1)

"""

t = int(input())
for _ in range(t):
    k, l1, r1, l2, r2 = map(int, input().strip().split())
    n = 1
    ans = 0
    while (r2) // n >= l1:  # Continue while the smallest possible y (when x = l1) is within range
        # Compute how many valid x values exist such that y = x * k^n falls in [l2, r2]
        # For a given x, y must be in [l2, r2], so x must be in [l2/k^n, r2/k^n]
        # But also x must be in [l1, r1]
        # So x is in the intersection: [max(l1, (l2 + k - 1) // k^n), min(r1, r2 // k^n)]
        ans += max(0, 1 + min((r2) // n, r1) - max((l2 + n - 1) // n, l1))
        n *= k  # Increment to next power of k
    print(ans)


# https://github.com/VaHiX/codeForces/