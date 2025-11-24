# Problem: CF 1938 H - Pho Restaurant
# https://codeforces.com/contest/1938/problem/H

import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

from math import inf

n = int(input())
min_sum = 0
best_flip = inf
min_zero = False
min_one = False
has_one = False
has_zero = False
for i in range(n):
    s = input().rstrip().decode()

    zero = s.count("0")
    one = len(s) - zero
    min_sum += min(zero, one)  # For each table, we want to minimize the number of moves by choosing the majority type
    best_flip = min(best_flip, max(zero, one) - min(zero, one))  # Minimum difference between 0s and 1s for a table
    if one > 0:
        has_one = True  # Check if at least one table has a '1'
    if zero > 0:
        has_zero = True  # Check if at least one table has a '0'

    if one <= zero:
        min_one = True  # If current table has fewer or equal 1s than 0s, we could minimize by keeping all 1s
    if zero <= one:
        min_zero = True  # If current table has fewer or equal 0s than 1s, we could minimize by keeping all 0s

if has_one and has_zero:
    # If both 0s and 1s are present in the input, we must handle the case where we can change the overall strategy
    if min_one and min_zero:
        # If all tables are such that we can decide either 0s or 1s to keep as dominant, no additional flips needed
        print(min_sum)
    else:
        # We must flip some tables to have consistent dish type across all tables
        print(min_sum + best_flip)
else:
    # If we only have one type (all 0s or 1s), no moves required
    print(0)

# https://github.com/VaHiX/CodeForces/