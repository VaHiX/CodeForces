# Problem: CF 2060 A - Fibonacciness
# https://codeforces.com/contest/2060/problem/A

# ******************************************************************************
# Problem: Maximum Fibonacciness
# Algorithm/Technique: Brute force with set operations
# 
# Time Complexity: O(1) per test case
# Space Complexity: O(1) 
#
# Description:
# Given an array of 5 integers where only a1, a2, a4, a5 are known,
# we can choose any value for a3. The goal is to maximize the number of 
# indices i (1 ≤ i ≤ 3) such that a[i+2] = a[i] + a[i+1]. 
# This is called the "Fibonacciness" of the array.
#
# We try all possible values for a3 and determine which ones yield
# maximum Fibonacciness by checking if a3 = a1 + a2, a4 = a2 + a3, and a5 = a3 + a4
# Using set to store computed sums helps in counting how many valid Fibonacci relations hold.
# ******************************************************************************
for s in [*open(0)][1:]:
    a, b, d, e = map(int, s.split())  # Read four integers from input line
    # Compute the three possible values of a3 such that:
    # a3 = a + b (to make a3 = a1 + a2)
    # d - b = a3 (to make a4 = a2 + a3)  
    # e - d = a3 (to make a5 = a3 + a4)
    print(4 - len({a + b, d - b, e - d}))  # Count how many of these are equal to each other


# https://github.com/VaHiX/codeForces/