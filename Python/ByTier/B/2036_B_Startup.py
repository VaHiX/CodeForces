# Problem: CF 2036 B - Startup
# https://codeforces.com/contest/2036/problem/B

"""
B. Startup

Purpose:
This code solves the problem of maximizing profit from placing bottles on shelves in a vending machine.
Each shelf can only hold bottles of the same brand, and each bottle has a brand index and cost.
We aim to select up to n brands (shelves) and place all bottles of those brands on the shelves such that total cost is maximized.

Algorithm:
1. For each test case, we count how many bottles exist for each brand.
2. We sum all the costs for each brand.
3. To maximize profit, we sort the brand totals in ascending order and take the top n sums.
4. This greedy approach works because we want to pick the brands with the highest total cost.

Time Complexity: O(k log k) per test case, due to sorting the brand totals.
Space Complexity: O(k), for storing the brand counts.

Input format:
- First line: number of test cases t
- For each test case:
  - Line 1: n (number of shelves), k (number of bottles)
  - Next k lines: b (brand index), c (cost)

Output:
- Maximum profit achievable by placing bottles on shelves.
"""

for _ in range(int(input())):  # Read number of test cases
    n, k = map(int, input().split())  # Read n (shelves) and k (bottles)
    c = [0] * (k + 1)  # Array to store total cost per brand (indexed from 1 to k)
    
    for i in range(k):  # For each bottle
        x, y = map(int, input().split())  # Read brand index x and cost y
        c[x] += y  # Accumulate cost for the brand
    
    c.sort()  # Sort brand totals in ascending order
    print(sum(c[-n:]))  # Take sum of largest n values (maximum profit)


# https://github.com/VaHiX/codeForces/