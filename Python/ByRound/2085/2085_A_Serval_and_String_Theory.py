# Problem: CF 2085 A - Serval and String Theory
# https://codeforces.com/contest/2085/problem/A

"""
Problem: Serval and String Theory

Purpose:
This code determines whether a given string can be made "universal" by performing at most k swaps.
A string is considered universal if it is lexicographically smaller than its reverse.
The approach checks several base cases to quickly determine if transformation is possible.

Algorithms/Techniques:
- String reversal comparison
- Early termination conditions based on edge cases
- Greedy logic for checking if string can be made smaller than its reverse

Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(n) due to storing the input string and its reverse.

Input:
- Number of test cases t
- For each test case:
  - n (length of string), k (max swaps allowed)
  - String s of lowercase letters

Output:
- "YES" if s can be made universal with at most k swaps, otherwise "NO"
"""

for t in range(int(input())):
    n, k = map(int, input().split())  # Read length of string and max swaps
    s = input()  # Read the string
    
    # Check for base cases where answer is immediately known
    if n == 1 or set(s) == set(s[0]) or (k == 0 and s >= s[::-1]):
        print("NO")  # Cannot make it universal in these cases
    else:
        print("YES")  # Otherwise, it's possible to make it universal


# https://github.com/VaHiX/codeForces/