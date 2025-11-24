# Problem: CF 2044 D - Harder Problem
# https://codeforces.com/contest/2044/problem/D

"""
Purpose: 
This code solves the problem of constructing an array b such that for each prefix of array a,
the element a[i] is a mode of the prefix b[0..i]. A mode is the most frequently occurring element
in a sequence. The solution ensures each b[i] is in the range [1, n] and satisfies the mode condition.

Algorithms/Techniques:
- Greedy approach: For each position i, if a[i] hasn't been used yet, assign it to b[i].
- Use a set to track unused numbers from 1 to n.
- Fill remaining positions with unused numbers in order.

Time Complexity: O(n) per test case, as each element is processed a constant number of times.
Space Complexity: O(n) for storing the output array and the set of unused elements.
"""

import sys


def input():
    return sys.stdin.readline().strip()


def solve():
    n = int(input())  # Read length of array
    a = [int(i) for i in input().split()]  # Read array a
    notused = set(range(1, 1 + n))  # Initialize set of unused numbers from 1 to n
    out = [-1] * n  # Initialize output array with -1
    for i in range(n):
        if a[i] in notused:  # If a[i] is not yet used
            out[i] = a[i]  # Assign a[i] to b[i]
            notused.remove(a[i])  # Remove a[i] from unused set
    it = iter(notused)  # Create iterator for unused elements
    for i in range(n):
        if out[i] == -1:  # If position i was not filled yet
            out[i] = next(it)  # Fill with next unused element

    print(" ".join(map(str, out)))  # Print result


for _ in range(int(input())):  # Process all test cases
    solve()


# https://github.com/VaHiX/CodeForces/