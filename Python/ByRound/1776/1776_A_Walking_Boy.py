# Problem: CF 1776 A - Walking Boy
# https://codeforces.com/contest/1776/problem/A

"""
Task: Walking Boy

Purpose:
This code determines whether it's possible for a judge to have walked their dog Boy at least twice in a day,
given the times when messages were sent. Each walk must be exactly 120 minutes long and non-overlapping.
Messages cannot be sent during walks.

Algorithms/Techniques:
- Greedy approach:
  - We process message times and calculate how many 120-minute gaps are available between them.
  - We try to place two walks (each of 120 minutes) such that they don't interfere with any message time.

Time Complexity: O(n), where n is the number of messages. This is because we iterate through the list once.
Space Complexity: O(1), excluding input storage, since only a few variables are used to store intermediate values.

Input Format:
- t test cases
- For each test case:
  - n (number of messages)
  - n space-separated integers representing message times

Output Format:
- "YES" if at least two walks are possible, otherwise "NO"
"""

for _ in range(int(input())):  # Process each test case
    n = int(input())  # Read number of messages
    l = [0] + list(map(int, input().split())) + [1440]  # Add start (0) and end (1440) points to the message times
    c = 0  # Counter for valid walk intervals
    for i in range(n + 1):  # Iterate over all consecutive pairs of timestamps including the start and end
        # Calculate how many 120-minute walks can fit between current and next timestamp
        c += (l[i + 1] - l[i]) // 120
    if c >= 2:  # If at least two full walks are possible
        print("YES")
    else:
        print("NO")


# https://github.com/VaHiX/codeForces/