# Problem: CF 1845 C - Strong Password
# https://codeforces.com/contest/1845/problem/C

"""
Algorithm: Backtracking with Subsequence Check
Approach:
- For each possible password of length m, check if it satisfies:
  1. Each digit i is in range [l[i], r[i]]
  2. The password does NOT appear as a subsequence in string s
- Since m <= 10, we can generate all possible passwords and check each one.
- We'll use backtracking to generate passwords efficiently and check if they're valid.

Time Complexity: O(10^m * |s|) where m <= 10 and |s| <= 3*10^5
Space Complexity: O(|s| + m) for storing string s and recursion stack
"""

import sys

input = sys.stdin.readline

for i in range(int(input())):
    x = input().strip()  # password database string
    tr = int(input())   # required length of password
    a = input().strip() # lower bounds for each digit
    b = input().strip() # upper bounds for each digit
    
    ind = 0             # current position in password being built
    se = set()          # set to track used digits in current segment
    t = 0               # count of available digits in current segment
    u = ord(b[ind]) - ord(a[ind]) + 1  # number of digits allowed at position ind
    
    # Process each character in the database string
    for i in x:
        # If current digit meets the constraint and has not yet been used
        if b[ind] >= i >= a[ind] and i not in se:
            se.add(i)
            t += 1
            # When we've used all allowable digits for current position
            if t == u:
                t = 0
                ind += 1
                se = set()  # reset set for next position
                if ind == tr:  # if we have filled all positions
                    print("NO")
                    break
                u = ord(b[ind]) - ord(a[ind]) + 1  # update allowable digits for new position

    else:
        # If we didn't break out of loop, there is at least one valid subsequence
        print("YES")


# https://github.com/VaHiX/CodeForces/