# Problem: CF 457 A - Golden System
# https://codeforces.com/contest/457/problem/A

"""
Golden System Comparison
========================

This code compares two numbers represented in the "golden system", a non-standard numeral system based on the golden ratio φ ≈ 1.618.
In this system, each digit position corresponds to a power of φ, and the value of a number is computed as the sum of digits multiplied by respective powers of φ.

The algorithm works by:
1. Equalizing the lengths of both input strings by padding with leading zeros.
2. Iterating through the digits from left to right (most significant to least significant).
3. When a difference is found:
   - If it's a single-digit difference (i.e., one digit is 1 and the other is 0), we compare based on proximity to φ^i.
   - If the difference is near the end of the string, we compute the actual values and compare.
   - Otherwise, we propagate the carry (i.e., treat the larger digit as if it were 2 in the next position) and continue.
4. A special optimization is performed when reaching the last few digits to avoid precision errors.

Time Complexity: O(n) where n is the length of the longer string.
Space Complexity: O(n) due to storing the padded digit arrays.
"""

import sys

input = sys.stdin.readline


a = input()[:-1]  # Read first number and remove newline
b = input()[:-1]  # Read second number and remove newline
n = max(len(a), len(b))  # Determine the maximum length
a = list(map(int, a.rjust(n, "0")))  # Pad and convert first number to list of integers
b = list(map(int, b.rjust(n, "0")))  # Pad and convert second number to list of integers
i = 0  # Initialize index

while i < n:  # Iterate through each digit position
    if abs(a[i] - b[i]) == 1:  # If there is a single-digit difference
        if i >= n - 2:  # If we are near the end, directly compare values
            if a[i] > b[i]:  # Compare based on current position's value
                print(">")
            else:
                print("<")
            exit()  # End processing
        # Propagate carry: increment next few digits based on which is larger
        if a[i] > b[i]:
            for i1 in range(i, min(i + 3, n)):  # Increment current and next few digits
                a[i1] += 1
        else:
            for i1 in range(i, min(i + 3, n)):  # Increment current and next few digits
                b[i1] += 1
    elif a[i] > b[i]:  # If current digit of 'a' is greater
        print(">")
        exit()
    elif a[i] < b[i]:  # If current digit of 'b' is greater
        print("<")
        exit()
    i += 1  # Move to next digit

print("=")  # If all digits are equal, output equals


# https://github.com/VaHiX/CodeForces/