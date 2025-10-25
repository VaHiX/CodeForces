# Problem: CF 2010 C2 - Message Transmission Error (hard version)
# https://codeforces.com/contest/2010/problem/C2

"""
Algorithm: KMP Failure Function (Z-algorithm approach)
Purpose: Determine if a given string can be split into two identical strings with overlapping,
         where the overlap occurs at the end of the first and beginning of the second.
         This simulates an error in message transmission where two messages merge.

Time Complexity: O(n), where n is the length of the input string.
Space Complexity: O(n), for storing the failure function array.

Approach:
- Use KMP-like failure function to find the longest proper prefix which is also suffix.
- If the last value in failure function is such that twice its value + 2 is greater than the string length,
  then we can reconstruct a valid original message s.
"""

s = input()
C = len(s)
f = [0] * C
f[0] = -1
for i in range(1, C):
    f[i] = f[i - 1]
    # Loop to backtrack using failure function until matching character is found or we go back to -1
    while f[i] >= 0 and s[f[i] + 1] != s[i]:
        f[i] = f[f[i]]  # Fall back using failure function
    if s[f[i] + 1] == s[i]:
        f[i] = f[i] + 1  # Extend match
# Check if a valid split exists based on failure function value
if (f[C - 1] + 1) * 2 > C:
    print("YES\n" + s[0 : f[C - 1] + 1])
else:
    print("NO")


# https://github.com/VaHiX/codeForces/