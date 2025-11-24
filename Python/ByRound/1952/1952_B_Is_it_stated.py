# Problem: CF 1952 B - Is it stated?
# https://codeforces.com/contest/1952/problem/B

"""
Algorithm: String Substring Search
Time Complexity: O(n*m) where n is the number of test cases and m is the average string length
Space Complexity: O(1) - only using constant extra space

The problem asks to determine if the substring "it" exists in each given string.
We iterate through each test case and check if "it" is a substring of the input string.
If found, we print "YES", otherwise "NO".
"""

tt = int(input())  # Read number of test cases
for _ in range(tt):  # Process each test case
    s = input()  # Read the input string
    if "it" in s:  # Check if "it" is a substring of current string
        print("YES")  # Print YES if "it" is found
    else:
        print("NO")  # Print NO if "it" is not found


# https://github.com/VaHiX/CodeForces/