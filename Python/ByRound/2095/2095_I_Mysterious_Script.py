# Problem: CF 2095 I - Mysterious Script
# https://codeforces.com/contest/2095/problem/I

"""
I. Mysterious Script
time limit per test1 second
memory limit per test256 megabytes

Algorithms/Techniques:
- Base-9 number system conversion
- String replacement and manipulation
- Custom numeral mapping using a dictionary-like list

Time Complexity: O(log_9(a) + log_9(b)) for the addition operation, which is linear in the number of digits.
Space Complexity: O(1) excluding input/output space, as fixed-size arrays and variables are used.

This program simulates adding two numbers represented in a custom base-9 Balikon numeral system,
where each digit is mapped to a specific string. The final sum is converted back into this
numeral system using base-9 arithmetic and string mapping.
"""

a = ["la", "le", "lon", "sha", "she", "shon", "ta", "te", "ton"]  # Mapping of digits to Balikon words
b = input().split()  # Read two strings representing the numbers
c, d = [b[0][:-1], b[1][:-1]]  # Remove last character ('s') from each string to convert

# Replace each Balikon word in c and d with its corresponding digit (0-8)
for i in range(9):
    c, d = c.replace(a[i], str(i)), d.replace(a[i], str(i))

# Convert strings to base-9 integers and add them
h = int(c, 9) + int(d, 9)

# Convert the result back to Balikon numeral form
r = ""
while h > 0:
    r = a[h % 9] + r  # Map remainder to corresponding Balikon word
    h //= 9

print(r + "s")  # Append 's' at end to denote number in Balikon style


# https://github.com/VaHiX/codeForces/