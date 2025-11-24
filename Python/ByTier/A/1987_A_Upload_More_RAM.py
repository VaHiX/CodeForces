# Problem: CF 1987 A - Upload More RAM
# https://codeforces.com/contest/1987/problem/A

"""
Algorithm: Mathematical Calculation

Purpose:
This code calculates the minimum number of seconds required to upload n GBs of RAM,
subject to the constraint that in any k consecutive seconds, at most 1 GB can be uploaded.

Approach:
The optimal strategy is to upload 1 GB every k seconds, leaving k-1 seconds with 0 GB.
This means for n GBs:
- We need (n-1) full cycles of k seconds (each cycle contributes 1 GB)
- Plus 1 additional second to upload the last GB
- Total = (n-1) * k + 1

Time Complexity: O(1) - constant time per test case
Space Complexity: O(1) - constant space usage
"""

t = int(input())
for i in range(t):
    n, k = map(int, input().split())
    print(k * (n - 1) + 1)


# https://github.com/VaHiX/CodeForces/