# Problem: CF 1902 A - Binary Imbalance
# https://codeforces.com/contest/1902/problem/A

# Flowerbox:
# Purpose: Determines if it's possible to make the number of '0's strictly greater than the number of '1's
#          in a string by inserting characters according to specific rules.
# Algorithm/Technique: Greedy approach based on observation that insertion only adds '0' when neighbors differ.
# Time Complexity: O(n) where n is the length of the string (single pass through input).
# Space Complexity: O(1) as no extra space is used beyond variables.

for i in [*open(0)][2::2]:  # Read every second line starting from index 2 (test cases)
    print("NYOE S"["0" in i :: 2])  # If '0' exists in input, print "YES", else "NO"


# https://github.com/VaHiX/codeForces/