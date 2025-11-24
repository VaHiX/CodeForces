# Problem: CF 2126 D - This Is the Last Time
# https://codeforces.com/contest/2126/problem/D

"""
D. This Is the Last Time

Algorithm/Technique:
Greedy algorithm with sorting. The idea is to sort the casinos by their required coins (l_i) in ascending order, 
then process them one by one. For each casino, if we have enough coins to enter (k >= l_i), we update k to be 
the maximum of its current value and the new value after playing (v). Since all valid casinos are processed once 
in increasing order of required coins, we get an optimal solution.

Time Complexity: O(n log n) due to sorting.
Space Complexity: O(n) for storing the list of casinos.

Input:
- Number of test cases t
- For each test case:
  - n (number of casinos), k (initial coins)
  - n lines of l_i, r_i, real_i describing each casino

Output:
- Maximum coins achievable after visiting some subset of casinos in optimal order.
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n, k = map(int, input().split())
    a = [tuple(map(int, input().split())) for _ in range(n)]
    # Sort by the lower bound of coins needed to enter the casino (l_i)
    a.sort(key=lambda x: x[0])
    for l, r, v in a:
        # If current coins k is within the range [l, r], we can play this casino
        if l <= k <= r:
            # Update k to be the maximum of current k and the new value after playing
            k = max(k, v)
    print(k)


# https://github.com/VaHiX/codeForces/