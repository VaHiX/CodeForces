# Problem: CF 2060 D - Subtract Min Sort
# https://codeforces.com/contest/2060/problem/D

"""
D. Subtract Min Sort

Purpose:
    Determine if a sequence of positive integers can be made non-decreasing by repeatedly performing 
    the operation: select an index i (1 ≤ i < n), and subtract min(a[i], a[i+1]) from both a[i] and a[i+1].

Algorithms/Techniques:
    - Greedy simulation with a single pass
    - For each element, subtract the minimum of adjacent elements if current element is less than or equal to next
    - Final check on last element to determine if sequence can be non-decreasing

Time Complexity: O(n) where n is the length of the array. Each element is visited at most once.
Space Complexity: O(n) for storing input array.

Input Format:
    - First line contains number of test cases t
    - For each test case:
        - First line: integer n (length of sequence)
        - Second line: n space-separated positive integers

Output Format:
    - "YES" if sequence can be made non-decreasing, otherwise "NO"
"""

for s in [*open(0)][2::2]:  # Read input lines starting from index 2 with step 2
    a = [*map(int, s.split()), -1]  # Convert line to int list and append -1 as sentinel
    i = 0  # Initialize index pointer
    while a[i] <= a[i := i + 1]:  # While current element is <= next, move pointer and adjust
        a[i] -= a[i - 1]  # Subtract previous value from current
    print("YNEOS"[a[i] > 0 :: 2])  # Print "YES" if last value > 0, else "NO"


# https://github.com/VaHiX/codeForces/