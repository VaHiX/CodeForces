# Problem: CF 2103 A - Common Multiple
# https://codeforces.com/contest/2103/problem/A

# flowerbox start
"""
Code Purpose:
This code solves the problem of finding the maximum size of a beautiful subsequence from a given array.
A subsequence is considered beautiful if there exists another sequence of distinct integers such that 
the product of corresponding elements in both sequences is the same for all pairs.

Algorithms/Techniques:
- Uses set data structure to count unique elements in input.
- For each line of input (starting from line 2, skipping every other line), 
  it splits the string into words and computes the number of unique words.
  
Time Complexity: O(n * m) where n is the number of lines processed and m is the average number of words per line.
Space Complexity: O(m) where m is the maximum number of unique words in any single line.

Note: This code appears to be parsing input lines, assuming input format as:
Line 1: Number of test cases
Line 2 onwards: Data lines alternating between metadata and actual data.
"""
# flowerbox end

for s in [*open(0)][2::2]:  # Read all input lines, skip first two lines, process every second line starting from index 2
    print(len({*s.split()}))  # Split the string by whitespace, convert to set (removes duplicates), and print length


# https://github.com/VaHiX/codeForces/