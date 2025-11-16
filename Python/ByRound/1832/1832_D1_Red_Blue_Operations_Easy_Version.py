# Problem: CF 1832 D1 - Red-Blue Operations (Easy Version)
# https://codeforces.com/contest/1832/problem/D1

"""
Algorithm: Red-Blue Operations (Easy Version)
Approach:
- This problem involves simulating operations on an array with red/blue elements, where each operation either increases or decreases elements.
- The goal is to determine the maximum possible minimum value after exactly k operations.
- The key ideas involve:
  1. Preprocessing array values to compute prefix minimums for red elements.
  2. Using mathematical formulas to calculate outcomes based on parity and cumulative sums.
  3. Adjusting for even/odd operation counts and array size combinations.

Time Complexity: O(n + q)
Space Complexity: O(n)

Methods:
- Precompute prefix minimums to quickly determine the best possible value for red elements.
- For each query, depending on k and n:
  - If k < n: use simple adjustment.
  - Else: use math-based calculation to handle large k values efficiently.
"""

I = lambda: map(int, input().split())
n, q = I()
a = sorted(I())  # Sort the array to help with prefix computations
pr = [10**9 for i in range(n + 1)]  # Prefix minimum array
for i in range(n):
    pr[i + 1] = min(pr[i], a[i] - i)  # Compute prefix minimum of (a[i] - i)
s = sum(a) - n * (n - 1) // 2  # Cumulative sum adjusted for arithmetic progression
ans = []
for k in I():  # Process each query
    if k < n:
        # If number of operations is less than array size
        ans.append(min(pr[k] + k, a[k]))
    elif k % 2 == n % 2:
        # Both even or both odd
        ns = s - pr[n] * n  # Calculate necessary adjustment
        ans.append(pr[n] + k - (max(0, (k - n) // 2 - ns) + n - 1) // n)
    else:
        # Odd-even or even-odd case
        nmn = min(pr[n - 1], a[n - 1] - k)  # Determine new minimum value
        ns = (s + (n - 1) - k) - nmn * n  # Adjusted sum
        ans.append(nmn + k - (max(0, (k - (n - 1)) // 2 - ns) + n - 1) // n)
print(*ans)  # Output all results for each query


# https://github.com/VaHiX/CodeForces/