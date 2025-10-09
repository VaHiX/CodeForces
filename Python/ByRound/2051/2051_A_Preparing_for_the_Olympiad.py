# Problem: CF 2051 A - Preparing for the Olympiad
# https://codeforces.com/contest/2051/problem/A

"""
Problem: A. Preparing for the Olympiad

Purpose:
  Maximizes the difference (m - s) where m is the number of problems Monocarp solves,
  and s is the number of problems Stereocarp solves.
  
  Key insight:
    - Monocarp chooses which days to train.
    - If Monocarp trains on day i, then Stereocarp trains on day i+1 (if exists).
    - To maximize difference, for each day i, we can choose whether Monocarp trains or not.
      If Monocarp trains on day i, he gains a[i], but Stereocarp must train on day i+1 and loses b[i+1].
      
  Strategy:
    - For each day from 0 to n-2:
        If Monocarp trains on day i (a[i]), and Stereocarp trains on day i+1 (b[i+1]),
        we can compute the net gain of training on this day as (a[i] - b[i+1]).
    - If Monocarp trains on last day, he gets a[-1], since Stereocarp has no next day.

  Time Complexity: O(n) per test case
  Space Complexity: O(1) additional space (excluding input)
"""

for _ in range(int(input())):  # Read number of test cases
    t = int(input())  # Number of days
    c = 0  # Initialize counter for total difference
    a = [*map(int, input().split())]  # Problems Monocarp solves per day
    b = [*map(int, input().split())]  # Problems Stereocarp solves per day
    
    # Loop through all days except the last one
    for i in range(t - 1):
        # If Monocarp trains on day i and Stereocarp trains on day i+1,
        # the net gain for Monocarp is a[i] - b[i+1]
        if 0 < a[i] - b[i + 1]:
            c += a[i] - b[i + 1]
    
    # Add the last day's problem count (Monocarp trains on last day, no follow-up)
    print(c + a[-1])


# https://github.com/VaHiX/codeForces/