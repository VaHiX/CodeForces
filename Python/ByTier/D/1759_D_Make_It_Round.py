# Problem: CF 1759 D - Make It Round
# https://codeforces.com/contest/1759/problem/D

from math import lcm

# Purpose: Find the roundest possible price after multiplying n by k (1 <= k <= m)
# Algorithm: 
#   - For each possible number of trailing zeros (from 18 down to 0):
#       * Compute lcm(n, 10^i) 
#       * If this lcm is <= m*n, then we can multiply n by some k <= m to get a number divisible by lcm(n, 10^i)
#       * Among those valid values, we want the one that maximizes the number of trailing zeros
#       * So we pick the largest such i (i.e., the most trailing zeros), and compute m - m % x to make the result as large as possible
# Time Complexity: O(1) - We iterate only 19 times (from 18 to 0)
# Space Complexity: O(1) - Only use a constant amount of extra space

for _ in range(int(input())):
    n, m = map(int, input().split())
    m *= n
    for i in range(18, -1, -1):
        if (x := lcm(n, 10**i)) <= m:
            print(m - m % x)
            break


# https://github.com/VaHiX/CodeForces/