# Problem: CF 1766 A - Extremely Round
# https://codeforces.com/contest/1766/problem/A

"""
Code purpose: Calculate the number of extremely round integers from 1 to n (inclusive).
An extremely round integer has only one non-zero digit.
For example: 1, 2, ..., 9, 10, 20, ..., 90, 100, 200, ..., 900, 1000, etc.

Algorithm:
1. For a number n with d digits, we need to count all extremely round numbers <= n
2. These can be divided into:
   - All 1-digit extremely round numbers (1-9): 9 numbers
   - All 2-digit extremely round numbers (10-90): 9 numbers  
   - All 3-digit extremely round numbers (100-900): 9 numbers
   - And so on...
3. For a d-digit number n:
   - All numbers with d-1 digits: (d-1) * 9
   - All numbers with same first digit as n, d digits: n[0] (since we can have 1000...0, 2000...0, ..., n[0]000...0)
   - But only count those <= n: (n[0]) if n[0] <= 9 and n[0] >= 1
4. So: (first digit) + (number of digits - 1) * 9

Time Complexity: O(1) - single operation per test case
Space Complexity: O(1) - only using constant extra space
"""

for i in range(int(input())):
    n = input()
    print(int(n[0]) + ((len(n) - 1) * 9))


# https://github.com/VaHiX/CodeForces/