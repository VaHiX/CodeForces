# Problem: CF 2121 G - Gangsta
# https://codeforces.com/contest/2121/problem/G

"""
G. Gangsta
Algorithm: Prefix Sum + Sorting + Math
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for prefix array and sorting

Given a binary string s, compute the sum of f(s[l:r+1]) over all substrings,
where f(p) is the maximum count of any character in substring p.
The approach uses prefix sums to efficiently compute character counts,
sorts the prefix sums to enable fast calculation of contribution of each
interval, then uses mathematical formula for efficient summation.

Key idea:
- Convert 0s to -1 and 1s to +1 for easier prefix sum calculation.
- Prefix sum array helps determine count of 1s in any substring.
- Sorting prefix sums enables us to use cumulative contributions efficiently.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()


def solve_case():
    n = int(input())
    s = input()
    
    # Build prefix sum array where each element represents balance of 1s over 0s
    # 0 -> -1, 1 -> +1
    pref = [0] * (n + 1)
    for i in range(n):
        pref[i + 1] = pref[i] + (-1 if s[i] == "0" else +1)
    
    # Sort the prefix sums to group similar values together
    pref.sort()
    
    # Compute total contribution using formula:
    # For each adjacent pair (pref[i], pref[i+1]), we have
    # (pref[i+1] - pref[i] + 1) * (i+1) * (n-i) / 2
    ans = sum((pref[i + 1] - pref[i] + 1) * (i + 1) * (n - i) for i in range(n)) // 2
    
    return ans


ans = []
for _ in range(int(input())):
    ans.append(str(solve_case()))
print("\n".join(ans))


# https://github.com/VaHiX/codeForces/