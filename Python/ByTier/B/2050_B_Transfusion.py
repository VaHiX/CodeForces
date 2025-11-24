# Problem: CF 2050 B - Transfusion
# https://codeforces.com/contest/2050/problem/B

# B. Transfusion
# time limit per test2 seconds
# memory limit per test256 megabytes
#
# Problem Description:
# Given an array of integers, we can perform operations on elements at indices from 2 to n-1 (1-indexed).
# In each operation, we can transfer 1 unit of value from one neighbor to the other neighbor,
# maintaining non-negativity of all values.
# The goal is to determine if it's possible to make all elements equal.
#
# Algorithm:
# Key Insight:
# For any valid sequence of operations that results in all elements being equal,
# the total sum must be divisible by the number of elements (n).
# Additionally, the sum of elements at odd indices must equal the sum of elements at even indices
# when each is multiplied by n/2 (since we distribute the values evenly in pairs).
#
# Time Complexity: O(n) per test case.
# Space Complexity: O(n) due to input storage and processing.

for s in [*open(0)][2::2]:  # Read odd lines (test cases)
    lst = list(map(int, s.split()))  # Parse line into list of integers
    len_, sum_ = len(lst), sum(lst)  # Get length and total sum
    
    # Check if sum is divisible by length (necessary condition)
    # And check if the alternating sum matches required distribution property
    print(
        "YES"
        if sum_ % len_ == 0 and sum(lst[1::2]) == (len_ // 2) * (sum_ // len_)
        else "NO"
    )


# https://github.com/VaHiX/codeForces/