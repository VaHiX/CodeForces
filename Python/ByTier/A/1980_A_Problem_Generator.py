# Problem: CF 1980 A - Problem Generator
# https://codeforces.com/contest/1980/problem/A

"""
Algorithm: Greedy Approach
Approach:
- For each difficulty level from 'A' to 'G', count how many problems of that level exist in the bank.
- For each difficulty level, calculate how many additional problems are needed to satisfy `m` rounds.
- Sum up all the shortages to get the minimum number of new problems required.

Time Complexity: O(n + 1) = O(n), where n is the number of problems in the bank.
Space Complexity: O(1), since we use a fixed-size dictionary for 7 difficulty levels ('A' to 'G').

"""

import sys

input = lambda: sys.stdin.readline().strip()

p = "ABCDEFG"  # All possible difficulty levels

T = int(input())  # Number of test cases
for _ in range(T):
    n, m = map(int, input().split())  # n: number of problems, m: number of rounds
    s = input()  # String of problem difficulties
    
    # Initialize a dictionary to count problems of each difficulty
    d = dict()
    for i in p:  # For each difficulty level
        d[i] = 0  # Initialize count to zero
    
    # Count how many problems of each difficulty are present in the bank
    for i in s:
        d[i] += 1  # Increment count for the difficulty
    
    # Calculate minimum number of additional problems needed
    ans = 0
    for i in p:  # For each difficulty level
        # If we need more than what we have, add the shortage
        ans += max(0, m - d[i])
    
    print(ans)  # Output the result


# https://github.com/VaHiX/CodeForces/