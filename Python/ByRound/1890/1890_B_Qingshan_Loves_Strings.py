# Problem: CF 1890 B - Qingshan Loves Strings
# https://codeforces.com/contest/1890/problem/B

"""
Algorithm: String Manipulation and Greedy Check
Time Complexity: O(n + m) per test case, where n is length of s and m is length of t
Space Complexity: O(1) additional space, not counting input storage

The solution checks if it's possible to make string s good by inserting string t anywhere.
A string is good if no two adjacent characters are the same.
Key observations:
1. If t has all same characters, we can only insert t at positions where s doesn't conflict.
2. If t has different start and end, we can use it to break any adjacent duplicates in s.
3. We iterate through s and check for conflicts with t insertions.
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def solution(n, s, t):
    # Check if t is all same characters (f = True means all same)
    f = False
    if t[0] == t[-1]:
        f = True
        for i in range(1, len(t)):
            if t[i] == t[i - 1]:
                f = False
                break

    # Iterate through s to find conflicts
    for i in range(1, len(s)):
        # If s[i] != s[i-1], it's okay (no adjacent duplicates)
        # If f is True and s[i] != t[0], we can insert t here
        if s[i] != s[i - 1] or (f and s[i] != t[0]):
            continue
        # Otherwise, it's impossible to make s good
        return "No"

    return "Yes"


ans = []
for _ in range(int(input())):
    n, m = [int(i) for i in input().split()]
    s = [int(i) for i in input().rstrip()]
    t = [int(i) for i in input().rstrip()]
    ans.append(solution(n, s, t))
sys.stdout.write("\n".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/