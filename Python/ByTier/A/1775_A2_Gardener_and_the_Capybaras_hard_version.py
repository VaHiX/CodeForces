# Problem: CF 1775 A2 - Gardener and the Capybaras (hard version)
# https://codeforces.com/contest/1775/problem/A2

"""
Algorithm/Technique:
The problem requires splitting a string of 'a' and 'b' characters into three parts a, b, and c such that either:
1. a <= b and c <= b (b is the maximum among all), or
2. b <= a and b <= c (b is the minimum among all)

The approach:
1. We iterate through the string to find the first occurrence of 'a' after the first character.
2. If no such 'a' is found (i.e., the string is all 'b's or starts with 'b' and all remaining are 'b's),
   then we split the string as:
   - First character as 'a'
   - Middle part as 'b'
   - Last character as 'c'
3. Otherwise, we split the string at that first 'a' position to form:
   - Prefix up to (but not including) the first 'a' as 'a'
   - The 'a' character as 'b'
   - The rest as 'c'

Time Complexity: O(n) where n is the length of string s, as we perform a single pass.
Space Complexity: O(1) excluding the input/output space.
"""

import sys

input = sys.stdin.readline
print = sys.stdout.write

T = int(input().strip())

for _ in range(T):
    s = input().strip()
    idx = 0

    # Find the first occurrence of 'a' after index 0
    for i in range(1, len(s) - 1):
        if s[i] == "a":
            idx = i

    # If no 'a' found after index 0, split the string accordingly
    if idx == 0:
        print(s[0] + " " + s[1 : len(s) - 1] + " " + s[-1] + "\n")
    else:
        # Split at the first 'a' found after index 0
        print(s[:idx] + " " + s[idx] + " " + s[idx + 1 :] + "\n")


# https://github.com/VaHiX/CodeForces/