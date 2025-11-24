# Problem: CF 2042 A - Greedy Monocarp
# https://codeforces.com/contest/2042/problem/A

"""
Algorithm: Greedy
Time Complexity: O(n * log(n)) due to sorting; each test case is processed in O(n) time after sorting
Space Complexity: O(n) for storing the list of coin counts

Approach:
- Sort the chests in ascending order.
- Use a greedy strategy: take the largest chests first (from the end of sorted list).
- Keep removing the largest chests until the sum of taken coins is at least k.
- The number of coins we need to add equals the difference between k and the current sum of coins taken.
"""

import sys

input = sys.stdin.readline
for _ in [0] * int(input()):
    n, k = map(int, input().split())
    l = sorted(map(int, input().split()))  # Sort chests by number of coins
    while l and k:
        if k < l[-1]:  # If remaining k is less than the largest chest
            break
        k -= l.pop()  # Take the largest chest and reduce k accordingly
    print(k)


# https://github.com/VaHiX/codeForces/