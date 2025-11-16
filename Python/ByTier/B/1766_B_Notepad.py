# Problem: CF 1766 B - Notepad#
# https://codeforces.com/contest/1766/problem/B

"""
Algorithm: Check if there exists a substring of length 2 that appears more than once in the string.
If such a substring exists, we can use the copy-paste operation to reduce the total number of operations.

Time Complexity: O(n^2) in worst case due to the string.count() operation inside the loop.
Space Complexity: O(n) for storing the input string and substrings.

Techniques:
- Iterate through all possible substrings of length 2.
- Use the count() method to check if a substring appears more than once.
- If found, print "YES", otherwise print "NO".
"""

for t in range(int(input())):
    n = int(input())
    s = input()
    # Loop through all possible substrings of length 2
    for i in range(n - 1):
        b = s[i : i + 2]  # Extract substring of length 2
        if s.count(b) > 1:  # Check if this substring appears more than once
            print("YES")
            break
    else:
        print("NO")  # No repeated substring of length 2 found


# https://github.com/VaHiX/CodeForces/