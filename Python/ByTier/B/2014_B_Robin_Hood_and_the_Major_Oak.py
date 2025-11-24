# Problem: CF 2014 B - Robin Hood and the Major Oak
# https://codeforces.com/contest/2014/problem/B

# B. Robin Hood and the Major Oak
# Purpose: Determine if the number of leaves on the Major Oak in year n is even.
# Algorithm: 
#   - Leaves from year i last for k years (i to i+k-1).
#   - The number of leaves in year n is the count of integers i such that i <= n and i + k - 1 >= n.
#   - This simplifies to counting how many i satisfy max(1, n - k + 1) <= i <= n.
#   - Which equals n - max(1, n - k + 1) + 1 = min(n, k) if k <= n, else just n.
#   - The exact count is simply min(n, k), because leaves last exactly k years,
#     so for any year n, the number of leaves is:
#     if k >= n: all leaves from 1 to n (n leaves)
#     else: leaves from n-k+1 to n (k leaves)
#   - Therefore, count = min(n, k).
# Time Complexity: O(1) per test case.
# Space Complexity: O(1).

for s in [*open(0)][1:]:
    n, k = map(int, s.split())
    print("YNEOS"[n % 2 + k & 3 > 1 :: 2])


# https://github.com/VaHiX/codeForces/