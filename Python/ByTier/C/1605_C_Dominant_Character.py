# Problem: CF 1605 C - Dominant Character
# https://codeforces.com/contest/1605/problem/C

"""
Problem: Find the length of the smallest substring where 'a' occurs strictly more times than 'b' and 'c', and the substring length is at least 2.

Approach: 
- Since we need the smallest valid substring, we can check for all possible small patterns
- The key insight is that we only need to check substrings of length up to 9 (based on the provided patterns)
- We look for specific patterns that are known to be valid candidates
- Time Complexity: O(n) where n is the length of string s
- Space Complexity: O(1) as we use constant extra space
"""

for _ in range(int(input())):
    n = int(input())
    s = input()
    # Check for predefined patterns that satisfy the conditions
    for i in ["aa", "aba", "aca", "abca", "acba", "abbacca", "accabba"]:
        if i in s:  # If pattern exists in string
            print(len(i))  # Print length of first matching pattern
            break  # Exit loop after first match
    else:
        print(-1)  # If no pattern found, print -1


# https://github.com/VaHiX/CodeForces/