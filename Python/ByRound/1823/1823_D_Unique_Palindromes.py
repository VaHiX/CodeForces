# Problem: CF 1823 D - Unique Palindromes
# https://codeforces.com/contest/1823/problem/D

"""
Algorithm: 
- Use greedy approach to construct a string that satisfies all palindrome conditions.
- For each prefix, determine how many palindromes we must add (b[i] - b[i-1]) and how many extra positions (a[i] - a[i-1] - (b[i] - b[i-1])).
- Fill palindromes with unique characters (a, b, c, ...) for required palindromes.
- Fill remaining positions with a fixed repeating pattern (xyz) to avoid disrupting palindromes.
- If at any point required palindromes exceed available positions, return "NO".

Time Complexity: O(n) - where n is the length of the string.
Space Complexity: O(n) - for storing the answer string.
"""

import sys

input = sys.stdin.readline

t = int(input())

for _ in range(t):
    n, k = map(int, input().split())
    a = [0] + list(map(int, input().split()))  # prefix lengths
    b = [0] + list(map(int, input().split()))  # required palindromes
    flag = True
    ans = []
    index = 0
    for i in range(1, k + 1):
        # Check if it's possible to satisfy the condition
        if b[i] - b[i - 1] > a[i] - a[i - 1]:
            flag = False
            break
        d = (a[i] - a[i - 1]) - (b[i] - b[i - 1])  # Extra positions to fill
        # Add palindromic substrings with unique characters
        ans += [chr(96 + i)] * (b[i] - b[i - 1])
        # Fill extra positions with repeating pattern xyz
        for _ in range(d):
            ans.append("xyz"[index])
            index = (index + 1) % 3
    if flag:
        print("YES")
        ans[:3] = ["x", "y", "z"]  # Replace first 3 characters with fixed xyz
        print("".join(ans))
    else:
        print("NO")


# https://github.com/VaHiX/CodeForces/