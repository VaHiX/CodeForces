# Problem: CF 1861 C - Queries for the Array
# https://codeforces.com/contest/1861/problem/C

"""
Check if a sequence of operations (+, -, 0, 1) on an array is valid.

The operations represent:
- +: Append an integer to the array
- -: Remove the last element from the array
- 0: Check if current array is sorted (non-descending), output 0 if not sorted
- 1: Check if current array is sorted (non-descending), output 1 if sorted

Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) using only a few variables for tracking state
"""
from sys import stdin

input = stdin.readline
for _ in range(int(input())):
    s = input().strip()
    c = 0  # Current size of the array
    f = 1  # Flag for validity of sequence, 1 means valid
    uf = 0  # Unsorted flag, indicates if the last check was unsorted
    sf = 0  # Sorted flag, tracks if last check had a sorted segment
    for i in s:
        if i == "+":
            c += 1  # Increase array size
            sf += 1  # Increase sorted fragment count
            if uf:
                uf += 1  # If still unsorted, extend the counter
        elif i == "-":
            c -= 1  # Decrease array size
            if sf:
                sf -= 1  # Decrease sorted fragment
            if uf:
                uf -= 1  # If still unsorted, decrease counter
        elif i == "0":
            # Check if array is not sorted and has at least 2 elements
            if c < 2 or sf == 0:
                f = 0  # Invalid sequence
                break
            else:
                if uf == 0:
                    uf = 1  # Mark that we have an unsorted state
        else:  # i == "1"
            sf = 0  # Reset sorted fragment
            if uf:
                f = 0  # If we were in unsorted state, then this is invalid
                break
    if f:
        print("YES")
    else:
        print("NO")


# https://github.com/VaHiX/CodeForces/