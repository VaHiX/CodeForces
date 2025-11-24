# Problem: CF 2022 B - Kar Salesman
# https://codeforces.com/contest/2022/problem/B

# B. Kar Salesman
# Algorithms/Techniques: Greedy approach, ceiling division
# Time Complexity: O(n) per test case, where n is the number of car models
# Space Complexity: O(1) additional space (excluding input storage)

import math

for i in range(int(input())):  # Loop through each test case
    n, x = map(int, input().split())  # Read number of models and max cars per customer
    a = [int(x) for x in input().split()]  # Read the count of cars for each model
    
    # The minimum number of customers is the maximum between:
    # 1. The largest stock of any single model (as we can't sell more than that in one customer)
    # 2. Total cars divided by max cars per customer, rounded up (ceiling division)
    print(max(max(a), math.ceil(sum(a) / x)))


# https://github.com/VaHiX/codeForces/