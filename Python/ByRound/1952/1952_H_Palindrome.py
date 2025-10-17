# Problem: CF 1952 H - Palindrome
# https://codeforces.com/contest/1952/problem/H

"""
Palindrome Checker
Algorithm: For each string, check if it reads the same forwards and backwards
Techniques: String reversal comparison
Time Complexity: O(n*m) where n is number of strings and m is average string length
Space Complexity: O(m) where m is the average string length (for storing reversed string)

The code checks if each input string is a palindrome by comparing it with its reverse.
"""

n = int(input())
g = [list(input()) for _ in range(n)]  # Read n strings and convert to list of characters
for i in range(n):
    h = [s[i] for s in g if i < len(s)]  # This creates a list of characters at position i from all strings
    if h == h[::-1]:  # Compare the list with its reverse
        print("YES")
    else:
        print("NO")


# https://github.com/VaHiX/CodeForces/