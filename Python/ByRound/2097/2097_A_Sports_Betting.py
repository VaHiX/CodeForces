# Problem: CF 2097 A - Sports Betting
# https://codeforces.com/contest/2097/problem/A

"""
Sports Betting

Problem Description:
Vadim makes bets with n students on specific days. For each student, he bets on day a_i. 
He wins the bet if he correctly predicts the boarding process on both day a_i and day a_i + 1.
The goal is to determine whether Vadim can guarantee at least one win by choosing a strategy for predicting the boarding process.

Approach:
- Sort the days in ascending order.
- Traverse through sorted days and count consecutive occurrences of the same day.
- For each group of same days, check if there's a way to assign predictions such that at least one student gets a correct guess on both day a_i and day a_i + 1.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(1) excluding input storage

Algorithms/Techniques:
- Sorting
- Greedy approach to detect valid assignments
"""

import sys

input = sys.stdin.readline


def read_input():
    input()
    a = list(map(int, input().split()))
    return a


def solve(a):
    a.sort()  # Sort the days in ascending order
    a.append(-1)  # Add sentinel to simplify loop logic
    px = -1  # Previous day processed
    k = 1  # Count of consecutive same days
    det = False  # Flag indicating if we have enough duplicates to cover all cases
    
    for i in range(len(a) - 1):
        if a[i] == a[i + 1]:
            k += 1  # Increment count for same day
            continue
        
        # If current day is greater than previous day + 1, it's a gap
        if a[i] > px + 1:
            det = False  # Reset flag when there is a gap
        
        # Check if we can guarantee at least one win:
        # - If there are at least 4 occurrences of the same day (always possible to get 2 consecutive wins)
        # - Or, if we can use 2 or more duplicate days with previous pattern matched
        if k >= 4 or (k >= 2 and det):
            return "Yes"
        
        # Update flag for future comparisons based on current group size
        det = det or (k >= 2)
        px = a[i]  # Update previous day
        k = 1  # Reset count for next group
    
    return "No"


T = int(input())
for _ in range(T):
    print(solve(read_input()))


# https://github.com/VaHiX/codeForces/