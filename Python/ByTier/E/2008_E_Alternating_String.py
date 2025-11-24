# Problem: CF 2008 E - Alternating String
# https://codeforces.com/contest/2008/problem/E

"""
E. Alternating String

Problem Description:
Given a string of lowercase Latin letters, determine the minimum number of operations required to make it an alternating string. An alternating string has all even-positioned characters the same and all odd-positioned characters the same, and its length must be even.

Two types of operations are allowed:
1. Delete one character (at most once).
2. Replace one character with any other letter.

Algorithm:
- If the string length is odd, we can consider deleting one character to make it even, then compute minimum changes needed.
- For even-length strings:
  - Count frequency of characters at odd and even indices separately.
  - The minimal operations needed = total length - max(odd_freq) - max(even_freq)
- For odd-length strings:
  - First try keeping the string as-is (checking if it's already alternating).
  - Otherwise, simulate deleting one character (at most once), and for each deletion position, compute changes needed.
  
Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(1) — only using fixed-size arrays of size 26 for character counts.

"""

import sys

ci = sys.stdin.readline


def get_ind(c):
    return ord(c) - 97


for _ in range(int(ci())):
    n = int(ci())
    s = ci().strip()
    odd, even = [0] * 26, [0] * 26
    if n & 1:  # If length is odd
        # Initialize odd and even frequency arrays for odd/even positions (excluding last)
        for i in range(1, n, 2):
            odd[get_ind(s[i])] += 1
            even[get_ind(s[i + 1])] += 1
        res = n - max(odd) - max(even)
        # Slide window: simulate removing one character from the string and recalculate
        for i in range(0, n - 1):
            arr = even if i & 1 else odd  # Select which array to update based on parity
            arr[get_ind(s[i])] += 1      # Add current character to count
            arr[get_ind(s[i + 1])] -= 1  # Remove next character from count
            res = min(res, n - max(odd) - max(even))
        print(res)
    else:  # If length is even
        # Directly compute frequencies of odd and even positions
        for i in range(0, n, 2):
            odd[get_ind(s[i])] += 1
            even[get_ind(s[i + 1])] += 1
        print(n - max(odd) - max(even))


# https://github.com/VaHiX/codeForces/