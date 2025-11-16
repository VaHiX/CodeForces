# Problem: CF 2005 A - Simple Palindrome
# https://codeforces.com/contest/2005/problem/A

"""
Algorithm: 
The solution aims to minimize the number of palindromic subsequences in a string of length n consisting only of vowels.
To achieve this, we distribute the vowels as evenly as possible across the 5 vowels ('a', 'e', 'i', 'o', 'u').
This minimizes the chance of forming palindromic subsequences because:
- If we use the same vowel repeatedly, we increase the number of palindromic subsequences (e.g., "aa" creates 3 palindromic subsequences: "a", "a", "aa").
- By distributing the vowels evenly, we avoid forming long repeated subsequences.

Time Complexity: O(n)
Space Complexity: O(n)

Approach:
1. Calculate base count of each vowel (e = n // 5) and remainder (r = n % 5).
2. Create an array of 5 strings, each initialized with 'e' copies of the respective vowel.
3. Distribute the remainder 'r' by appending one more of the first 'r' vowels.
4. Join these strings to form the final result.
"""

for _ in range(int(input())):
    n = int(input())
    v = ["a", "e", "i", "o", "u"]
    e = n // 5  # Base count of each vowel
    r = n % 5   # Remaining characters to distribute
    ans = []
    for i in range(5):
        ans.append(v[i] * e)  # Initialize each vowel with base count
    for i in range(r):
        ans[i] += v[i]        # Add one more of the first r vowels
    print("".join(ans))       # Combine all parts into final string


# https://github.com/VaHiX/CodeForces/