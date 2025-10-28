# Problem: CF 2106 B - St. Chroma
# https://codeforces.com/contest/2106/problem/B

# B. St. Chroma
# Task: Construct a permutation such that the number of cells painted color x is maximized.
# MEX (minimum excludant) of prefix determines the color of each cell.
# Algorithm:
#   - If x < n, place x at the end to ensure it's included in later prefixes.
#     Place all elements from 0 to x-1 first, then x+1 to n-1, and finally x.
#   - If x >= n, just output numbers from 0 to n-1 in order.
# Time Complexity: O(n) per test case
# Space Complexity: O(n) for storing the permutation

for _ in range(int(input())):
    n, x = map(int, input().split())
    if x < n:
        # Print elements from 0 to x-1, then x+1 to n-1, and finally x
        print(*range(x), *range(x + 1, n), x)
    else:
        # If x >= n, we can't achieve color x, so just print 0..n-1
        print(*range(n))


# https://github.com/VaHiX/codeForces/