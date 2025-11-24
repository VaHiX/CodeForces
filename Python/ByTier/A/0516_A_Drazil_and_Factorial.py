# Problem: CF 516 A - Drazil and Factorial
# https://codeforces.com/contest/516/problem/A

"""
Code purpose: 
This code solves the problem of finding the maximum number x that
satisfies two conditions: (1) x contains no digits 0 or 1, and (2) 
the product of factorials of digits in x equals the product of factorials of digits in input number a.

Algorithm:
1. Precompute factorial representations for digits 0-9 as products of prime factors
2. Convert each digit of input to its factorial representation 
3. Combine all factors and sort them in descending order to form maximum number

Time Complexity: O(n * log(n)) where n is the number of digits in input
Space Complexity: O(n) for storing intermediate results

Techniques:
- Precomputation of factorial representations
- String manipulation and sorting
- Greedy approach to maximize the resulting number
"""

L = ["", "", "2", "3", "223", "5", "35", "7", "2227", "3327"]  # Precomputed factorial representations
input()  # Read n but don't use it, just consume the line
# Convert each digit to its factorial representation, join all characters,
# sort in descending order, then join to form the final number
print("".join(sorted("".join([L[int(k)] for k in input()]))[::-1]))


# https://github.com/VaHiX/CodeForces/