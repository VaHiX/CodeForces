# Problem: CF 2007 F - Eri and Expanded Sets
# https://codeforces.com/contest/2007/problem/F

"""
F. Eri and Expanded Sets
Algorithms/Techniques: Segment Tree with GCD, Sliding Window
Time Complexity: O(n log n) per test case
Space Complexity: O(n log n) for segment tree storage

The problem asks to count the number of subarrays that can be made into consecutive sets
through a series of operations where we add the average of two elements if it's not present.

Key Observations:
- A subarray is brilliant if after inserting all valid averages, we can eventually form a set 
  of consecutive integers.
- This translates to checking if the GCD of differences of adjacent elements is 1,
  because if GCD is 1, then using differences we can generate any integer in range.

Approach:
1. For each subarray, compute differences between adjacent elements.
2. Use a Segment Tree with GCD to quickly query GCD over ranges.
3. A subarray is brilliant if the minimal GCD of differences across all possible 
   subarrays is 1 (i.e., there exists at least one range where elements are spaced by 1).
"""

from math import gcd

MAXN = 400_000
lg = [0] * (MAXN + 1)
lg[1] = 0
for c in range(2, MAXN + 1):
    lg[c] = lg[c // 2] + 1


def main():
    n = int(input())
    n -= 1  # because we compare adjacent elements, length becomes n
    a = list(map(int, input().split()))
    ans = n + 1  # start with count of all single element subarrays
    k = lg[n]
    st = [[0] * n for _ in range(k + 1)]
    
    # Build the segment tree with differences between adjacent elements
    for i in range(n):
        st[0][i] = abs(a[i] - a[i + 1])
        
    for i in range(1, k + 1):
        for j in range(n - (1 << i) + 1):
            st[i][j] = gcd(st[i - 1][j], st[i - 1][j + (1 << (i - 1))])

    # Query function for GCD over range [L, R]
    def q(L, R):
        sz = lg[R - L + 1]
        return gcd(st[sz][L], st[sz][R - (1 << sz) + 1])

    # Check if a number is a power of 2 (used to decide valid ranges for checking)
    def ok(val):
        if val & (val - 1):  # If val is not a power of 2
            return False
        return True

    # First pass to count valid ranges where difference array has zeros
    l = 0
    for r in range(n):
        if st[0][r]:
            l = r
            continue
        while st[0][l]:
            l += 1
        ans += r - l + 1  # Add number of valid subranges ending at r

    l = 0
    for r in range(n):
        # Slide left pointer while we can keep the current subarray valid or GCD is a power of two
        while l <= r and st[0][r] and ok(q(l, r)):
            l += 1
        if l != 0 and ok(q(l - 1, r)):
            ans += l  # Add number of valid starting positions

    print(ans)


t = int(input())
for _ in range(t):
    main()


# https://github.com/VaHiX/codeForces/