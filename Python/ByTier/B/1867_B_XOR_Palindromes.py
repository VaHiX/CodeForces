# Problem: CF 1867 B - XOR Palindromes
# https://codeforces.com/contest/1867/problem/B

"""
B. XOR Palindromes
Given a binary string s of length n, determine for each number x from 0 to n whether there exists a binary string l of length n with exactly x ones such that s ⊕ l is a palindrome.

Algorithm:
- For each test case, compute the number of mismatches between s[i] and s[n-i-1] for i in range(n//2).
- If n is odd, we can have at most (n - 2*c + 1) positions where we can place a '1' in the middle.
- If n is even, we can place '1's in pairs to make the result palindrome.
- Use dynamic construction of the output string t based on matched/unmatched characters.

Time Complexity: O(n) per test case
Space Complexity: O(1) excluding input/output
"""

import sys

input = sys.stdin.readline
for i in range(int(input())):
    n = int(input())
    s = input()
    c = 0
    # Count mismatches between symmetric positions
    for i in range(n // 2):
        if s[i] != s[n - i - 1]:
            c += 1
    # Build the output string based on number of mismatches
    if n % 2:
        # If length is odd, place zeros for mismatches, one in the center, then zeros again
        sys.stdout.write("0" * c + "1" * (n - 2 * c + 1) + "0" * c + "\n")
    else:
        # If length is even, construct pairs of '01' or ending in '1'
        sys.stdout.write("0" * c + "10" * ((n - 2 * c) // 2) + "1" + "0" * (c) + "\n")


# https://github.com/VaHiX/codeForces/