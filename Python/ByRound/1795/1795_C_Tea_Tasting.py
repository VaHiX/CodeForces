# Problem: CF 1795 C - Tea Tasting
# https://codeforces.com/contest/1795/problem/C

"""
C. Tea Tasting
Purpose:
This problem simulates a tea tasting process where n tasters consume tea from n different sorts in a specific order.
Each taster moves through the tea sorts in reverse order (from sort i to sort i-1), and consumes tea limited by 
either the available amount or their capacity per step.

Algorithm:
1. Precompute prefix sums of tea capacities 'b' for binary search.
2. For each taster, simulate how much tea they can drink from each sort, handling overlaps using a difference array technique.
3. Apply final accumulation to compute actual amounts drunk by each taster.

Time Complexity: O(n * log(n)) per test case due to bisect operations and loop
Space Complexity: O(n) for prefix sums and arrays

Input:
- Number of test cases t
- For each test case:
  - n (number of tea sorts and tasters)
  - Array 'a' of available amounts for each tea type
  - Array 'b' of consumption capacities for each taster

Output:
For each test case, output n integers representing the total milliliters drunk by each taster.
"""

import bisect
import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    psa = [0]
    for x in b:
        psa.append(psa[-1] + x)
    offset = [0] * n
    r = [(i + 1) * b[i] for i in range(n)]
    for i in range(n):
        j = bisect.bisect_right(psa, a[i] + psa[i]) - 1 # Find which tea sort the taster will next get from
        if j < n:
            r[j] -= b[j]
            r[j] += a[i] + psa[i] - psa[j] # Adjust for partial consumption
            offset[j] += 1 # Track how many times this sort is accessed
    acc = 0
    for i in range(n):
        r[i] -= b[i] * acc # Apply accumulated offset to actual consumption
        acc += offset[i]
    print(" ".join(map(str, r)))


# https://github.com/VaHiX/codeForces/