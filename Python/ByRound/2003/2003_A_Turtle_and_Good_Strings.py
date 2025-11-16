# Problem: CF 2003 A - Turtle and Good Strings
# https://codeforces.com/contest/2003/problem/A

"""
Algorithm/Technique: Greedy Approach

Time Complexity: O(n) where n is the length of the string, as we only check the first and last character.
Space Complexity: O(n) due to storing the string in a list.

The key insight is that for a string to be "good", it must be possible to split it into at least 2 parts such that 
no part's first character equals any later part's last character. 
If the first and last characters of the entire string are the same, it's impossible to satisfy the condition
for any valid split, hence we return "NO". Otherwise, it's always possible to construct a valid split.
"""

for _ in range(int(input())):  # Read number of test cases
    n = int(input())           # Read length of string
    s = [x for x in input()]   # Read string as list of characters
    if s[0] == s[-1]:          # Check if first and last characters are same
        print("NO")            # If same, impossible to form good string
    else:
        print("YES")           # Otherwise, it's always possible


# https://github.com/VaHiX/CodeForces/