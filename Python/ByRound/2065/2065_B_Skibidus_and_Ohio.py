# Problem: CF 2065 B - Skibidus and Ohio
# https://codeforces.com/contest/2065/problem/B

"""
B. Skibidus and Ohio

Problem Description:
Given a string of lowercase Latin letters, we can perform operations to reduce its length:
- Choose index i such that s[i] == s[i+1]
- Replace s[i] with any letter and remove s[i+1]
The goal is to find the minimum possible length of the string after any number of operations.

Algorithm:
- If there exists at least one pair of adjacent equal characters, we can reduce the entire string to a single character.
- Otherwise, the string cannot be reduced further and its length is the answer.
- This is determined by checking if any two consecutive characters are equal.

Time Complexity: O(n) where n is the length of the string, as we only need to scan once for adjacent duplicates.
Space Complexity: O(1), constant space usage.
"""

t = int(input())
for _ in range(t):
    s = input()
    # Check if there exists any pair of adjacent equal characters
    # If yes, we can reduce entire string to 1 character
    # If no, return the length of the string as it cannot be reduced further
    print(1 if any(v == w for v, w in zip(s[:-1], s[1:])) else len(s))


# https://github.com/VaHiX/codeForces/