# Problem: CF 1978 D - Elections
# https://codeforces.com/contest/1978/problem/D

"""
Code Purpose:
This code solves the problem of determining the minimum number of candidates to exclude 
so that each candidate can win the election. The key idea is to simulate the effect of 
excluding candidates and compute how many need to be excluded for a specific candidate 
to have the maximum votes, considering that undecided voters vote for the lowest-numbered 
candidate with enough votes.

Algorithm:
- For each candidate, simulate excluding them and calculate how many total votes 
  they would get (fans + undecided).
- Determine if this candidate can win with the current number of excluded candidates.
- Use a prefix sum approach to optimize checking each candidate.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the array of candidates' votes
"""

import sys

input = lambda: sys.stdin.readline().strip()
I = lambda: map(int, input().split())
for _ in range(int(input())):
    n, c = I()
    a = [*I()]
    a[0] += c  # Add undecided voters to first candidate
    m = max(a)  # Find maximum votes among candidates (with undecided voters)
    p = a.index(m)  # Index of candidate with maximum votes
    a[0] -= c  # Remove undecided voters from first candidate for future calculations
    
    # Iterate through each candidate
    for i in range(n):
        if i == p:
            # If candidate i is the one that would win, no exclusion needed (0)
            print(0, end=" ")
        elif a[i] >= m - c:
            # If candidate i can win with (m - c) votes, he needs to be excluded
            # This means we need to exclude candidates from 0 to i (inclusive)
            print(i, end=" ")
        else:
            # Otherwise, we need to exclude i + 1 candidates (including candidate i)
            print(i + 1, end=" ")
        c += a[i]  # Add current candidate's fans to total undecided voters for next iteration
    print()  # Print newline after each test case


# https://github.com/VaHiX/CodeForces/