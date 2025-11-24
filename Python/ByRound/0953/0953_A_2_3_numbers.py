# Problem: CF 953 A - 2-3-numbers
# https://codeforces.com/contest/953/problem/A

"""
Purpose: Count the number of 2-3-integers in the range [l, r].
A 2-3-integer is a positive integer that has only 2 and 3 as prime factors.
This means the number can be expressed as 2^x * 3^y where x, y >= 0.

Algorithm:
- Generate all possible values of 2^x * 3^y within the range [l, r].
- Use nested loops to iterate through possible values of x and y.
- For each valid combination, check if the resulting number lies in [l, r].
- Count such valid numbers.

Time Complexity: O(1) - The loops are bounded by constants (35 and 22), so it's constant time.
Space Complexity: O(1) - Only a few variables are used, no extra space needed.
"""

stroka = input().split()
l = int(stroka[0])
r = int(stroka[1])
counter = 0
for x in range(35):       # Loop through possible powers of 2 (2^34 > 2*10^9)
    for y in range(22):   # Loop through possible powers of 3 (3^21 > 2*10^9)
        num = 2**x * 3**y # Compute 2^x * 3^y
        if l <= num <= r: # Check if the number is in range [l, r]
            counter += 1  # Increment counter if in range
print(counter)


# https://github.com/VaHiX/CodeForces/