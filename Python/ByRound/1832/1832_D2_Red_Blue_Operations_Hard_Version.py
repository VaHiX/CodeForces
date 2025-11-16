# Problem: CF 1832 D2 - Red-Blue Operations (Hard Version)
# https://codeforces.com/contest/1832/problem/D2

"""
Algorithm: Binary Search + Greedy + Mathematical Analysis
Time Complexity: O(n + q * log(max_k))
Space Complexity: O(n)

Approach:
1. Precompute prefix minimums of (a[i] - i) to determine the best possible value for red elements.
2. Compute the sum of the array adjusted for operation costs.
3. For each query:
   - If k < n, directly use the prefix computation.
   - Otherwise, use mathematical formulas involving the sum and the number of operations to compute the final result.
   
Key Techniques:
- Prefix minimums for optimal red element handling
- Mathematical optimization for large k values
- Operations on blue/red state tracking using index-based cost calculation
"""

n, q = map(int, input().split())
a = list(map(int, input().split()))
a.sort()

# Precompute prefix minimums of (a[i] - i)
pr = [10**9 for i in range(n + 1)]
for i in range(n):
    pr[i + 1] = min(pr[i], a[i] - i)

# Compute adjusted sum of array
s = sum(a) - n * (n - 1) // 2

ans = []
for k in map(int, input().split()):
    if k < n:
        # For small k, directly calculate based on prefix minimums
        ans.append(min(pr[k] + k, a[k]))
        continue
    if k % 2 == n % 2:
        # When k and n have same parity
        ns = s - pr[n] * n
        # Calculate final value using the formula derived from mathematical analysis
        ans.append(pr[n] + k - (max(0, (k - n) // 2 - ns) + n - 1) // n)
    else:
        # When k and n have different parity
        nmn = min(pr[n - 1], a[n - 1] - k)
        ns = (s + (n - 1) - k) - nmn * n
        # Calculate final value using the formula derived from mathematical analysis
        ans.append(nmn + k - (max(0, (k - (n - 1)) // 2 - ns) + n - 1) // n)

print(*ans)


# https://github.com/VaHiX/CodeForces/