# Problem: CF 2143 B - Discounts
# https://codeforces.com/contest/2143/problem/B

"""
B. Discounts

Algorithm/Technique: Greedy + Sorting

Time Complexity: O(n log n + k log k)
Space Complexity: O(n + k)

The problem involves minimizing the cost of purchasing products using discount vouchers.
Each voucher allows selecting a group of products and paying for all but the cheapest one in that group.
We use a greedy approach:
1. Sort products in descending order to prioritize higher-priced items for grouping.
2. Sort vouchers in ascending order to apply smaller groups first, maximizing savings.
3. For each voucher, if it can be applied without exceeding the total product count,
   we calculate how much we save by using that voucher (i.e., skip the cheapest item in the group).
"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n, k = map(int, input().split())
    a = sorted(list(map(int, input().split())))[::-1]  # Sort prices in descending order
    b = sorted(list(map(int, input().split())))        # Sort vouchers in ascending order
    p = 0
    ans = sum(a)  # Start with total cost without any discounts
    for j in range(k):
        if b[j] + p > n:  # If applying this voucher exceeds number of products
            break
        else:
            p += b[j]  # Update the cumulative product count used
            ans -= a[p - 1]  # Subtract the cost of the cheapest item in current group (since it's free)
    print(ans)


# https://github.com/VaHiX/codeForces/