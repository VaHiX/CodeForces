# Problem: CF 2091 D - Place of the Olympiad
# https://codeforces.com/contest/2091/problem/D

"""
D. Place of the Olympiad

Problem Description:
Given a rectangular venue with n rows and m spots per row, place k participants at individual desks such that 
the maximum bench length (a group of consecutive occupied desks in a row) is minimized.

Approach:
This is a classic binary search on the answer problem. We binary search over the possible maximum bench length.
For a given maximum bench length L, we check if it's possible to place k participants using at most L desks per bench.

Time Complexity: O(t * log(min(n, m))) where t is number of test cases
Space Complexity: O(1)

Algorithms/Techniques:
Binary Search on Answer + Greedy Placement

"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n, m, k = map(int, input().split())
    # Calculate how many rows we need if each row has at most (k-1)//n + 1 desks
    x = (k - 1) // n + 1
    # y represents the minimum number of desks per row required to distribute k people optimally  
    y = m - x
    # Compute final result using formula to determine best placement strategy 
    print((m + 1 - 1) // (y + 1))


# https://github.com/VaHiX/codeForces/