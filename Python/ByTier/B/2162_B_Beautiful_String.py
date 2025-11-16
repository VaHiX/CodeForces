# Problem: CF 2162 B - Beautiful String
# https://codeforces.com/contest/2162/problem/B

import sys

""" 
Algorithm: 
- The key insight is to construct a non-decreasing subsequence p such that when p is removed from s, the remaining string x is a palindrome.
- A simple and effective approach: take all '0's in the string to form the subsequence p. 
- Since '0' <= '1', this subsequence p is automatically non-decreasing.
- When we remove all '0's from s, we are left with all '1's, which form a string that is trivially a palindrome (since all characters are identical).
- If there are no '0's in the string, then removing an empty subsequence leaves the entire string, which is also a palindrome.

Time Complexity: O(n) where n is the length of the string.
Space Complexity: O(n) for storing the result indices.
"""

input = sys.stdin.readline

for _ in range(int(input())):
    n = int(input())
    s = input().strip()
    result = []
    for i in range(n):
        if s[i] == "0":
            result.append(i + 1)  # Store 1-based indices
    print(len(result))
    print(*result)


# https://github.com/VaHiX/CodeForces/