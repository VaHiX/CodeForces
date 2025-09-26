# Problem: CF 2140 A - Shift Sort
# https://codeforces.com/contest/2140/problem/A

"""
Problem: Minimum Operations to Sort Binary String
Algorithm/Technique: Greedy approach with observation of shifts
Time Complexity: O(n) per test case, where n is the length of the string
Space Complexity: O(1), only using a few variables for counting

The problem allows us to perform operations on 3 indices i < j < k by cyclically shifting 
the values at those positions either left or right. The goal is to find the minimum number 
of such operations to sort the binary string (i.e., all 0s come before all 1s).

Key Insight:
- Since we can only shift 3 elements cyclically, and sorting a binary string means 
  arranging all 0s to the left and 1s to the right, we can observe that any operation
  affects only 3 positions.
- If we count how many 0s are at the beginning of the string (i.e., s[:s.count("0")]), 
  then this gives us a measure of how many 1s are misplaced in the correct part.

Approach:
For each test case, compute:
1. Count total number of 0s in the string.
2. Take prefix of length equal to this count (which should contain all 0s if sorted).
3. Count how many 1s are present in that prefix - these are misplaced 1s.
4. That count represents the minimum number of operations needed.
"""

for _ in range(int(input())):
    n = int(input())
    s = input()
    s1 = s.count("0")                              # Count total number of zeros
    ans = s[:s1].count("1")                        # Count ones in prefix of size s1
    print(ans)


# https://github.com/VaHiX/codeForces/