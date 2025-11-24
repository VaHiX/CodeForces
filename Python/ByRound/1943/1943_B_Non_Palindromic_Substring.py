# Problem: CF 1943 B - Non-Palindromic Substring
# https://codeforces.com/contest/1943/problem/B

"""
Algorithm: Manacher's Algorithm for finding palindromes + preprocessing for non-palindromic substring detection
Time Complexity: O(n + q) where n is length of string and q is number of queries
Space Complexity: O(n) for storing palindrome information and auxiliary arrays

Manacher's algorithm is used to find all palindromic substrings in linear time.
The solution uses a modified version of Manacher's algorithm to determine
which lengths of substrings are palindromes and which are not.
Then, for each query, we compute the sum of k values for which the substring
is k-good (i.e., contains at least one non-palindromic substring of length k).
"""

import sys

R = sys.stdin.readline
S = lambda: map(int, R().split())


def f(s):
    # Preprocess string for Manacher's algorithm by inserting '#' between chars
    s = "#" + "#".join(list(s)) + "#"
    dp = [0] * len(s)
    r, k = -1, -1
    for i in range(len(s)):
        # Use previously computed values to avoid redundant checks
        if i <= r:
            dp[i] = min(r - i, dp[2 * k - i])
        # Expand palindrome centered at i
        while (
            dp[i] <= min(i - 1, len(s) - i - 2) and s[i - dp[i] - 1] == s[i + dp[i] + 1]
        ):
            dp[i] += 1
        # Update rightmost palindrome center
        if r < i + dp[i]:
            r = i + dp[i]
            k = i
    return dp


def h(x):
    # Calculate sum of first x natural numbers (used for computing sum of all k from 1 to x)
    return x * (x + 1) // 2


def gg():
    # Read input for current test case
    n, q = S()
    s = R().rstrip()
    m = f(s)  # Get palindrome information using Manacher's algorithm
    a = [0] * n  # Store the leftmost index where character changes
    j = 0
    for i in range(1, n):
        if s[i] != s[i - 1]:
            j = i
        a[i] = j
    # Process each query
    for _ in range(q):
        l, r = S()
        # If no change in characters from l to r, then no non-palindromic substrings
        if a[r - 1] < l:
            print(0)
            continue
        g = r - l + 1  # Length of current substring
        x = h(g)  # Sum of all k from 1 to g
        # Check if the entire current substring is palindrome
        if g & 1:  # Odd length
            # If center of palindrome is less than full length, then substring is not palindrome
            if m[l + r - 1] < g:
                print(x - 1)
                continue
            x -= g  # Subtract all positions that are palindrome (but we only want not palindrome)
            # Check if there are enough non-palindromes at ends of substring
            if m[l + r - 3] < g - 2 or m[l + r + 1] < g - 2:
                print(x - 1)
            else:
                print(x - (g // 2) ** 2)
        else:  # Even length
            # If palindrome of full length exists, subtract it
            if m[l + r - 1] >= g:
                x -= g
            # Adjust by checking middle sections to avoid overcounting
            if m[l + r - 2] < g - 1 or m[l + r] < g - 1:
                print(x - 1)
            else:
                print(x - (g // 2) ** 2)


# Process multiple test cases
for _ in range(int(R())):
    gg()


# https://github.com/VaHiX/CodeForces/