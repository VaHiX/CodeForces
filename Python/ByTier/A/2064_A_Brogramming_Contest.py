# Problem: CF 2064 A - Brogramming Contest
# https://codeforces.com/contest/2064/problem/A

"""
A. Brogramming Contest
time limit per test1 second
memory limit per test256 megabytes

Problem Description:
Given a binary string s of length n and an initially empty binary string t,
you can perform two types of operations:
1. Remove a suffix from s and append it to t.
2. Remove a suffix from t and append it to s.

Goal: Make s contain only '0's and t contain only '1's with minimum moves.

Algorithm/Technique:
- The key insight is to count transitions between '0' and '1' in the string.
- Each transition (i.e., "01" or "10") corresponds to a move needed to separate
  groups of same characters.
- We prepend a '0' to the string to simplify counting.

Time Complexity: O(n) where n is the length of the string.
Space Complexity: O(n) due to string concatenation and copying.

"""

for _ in range(int(input())):  # Read number of test cases
    n = int(input())           # Read length of string
    s = input()                # Read binary string
    s = "0" + s                # Prepend a '0' to handle edge case
    print(s.count("01") + s.count("10"))  # Count transitions and print result


# https://github.com/VaHiX/codeForces/