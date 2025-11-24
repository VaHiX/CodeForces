# Problem: CF 2025 A - Two Screens
# https://codeforces.com/contest/2025/problem/A

"""
Problem: Minimum time to display two strings on two screens using typing and copying operations.

Algorithms/Techniques:
- String prefix matching to find common beginning
- Greedy approach to minimize total operations

Time Complexity: O(min(|s|, |t|)) per test case, where |s| and |t| are the lengths of the strings.
Space Complexity: O(1) - only using a few variables for computation.

Approach:
1. Find the length of the longest common prefix between s and t.
2. Calculate minimum operations needed to build both strings:
   - Type characters not in the shared prefix on each screen
   - Copy one screen's content to another when beneficial
"""

t = int(input())
for i in range(t):
    a = input()  # First string to display on screen 1
    b = input()  # Second string to display on screen 2
    s = 0  # Length of common prefix
    # Find the longest common prefix
    while s <= min(len(a), len(b)) and a[:s] == b[:s]:
        s += 1
    s -= 1  # Adjust for over-increment from while loop

    # Total operations = length of both strings minus twice the common prefix length,
    # plus one extra operation if there is no common prefix to allow copy action
    print(len(a) + len(b) - s + 1 - (s == 0))


# https://github.com/VaHiX/codeForces/