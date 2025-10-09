# Problem: CF 2143 A - All Lengths Subtraction
# https://codeforces.com/contest/2143/problem/A

"""
Algorithm/Technique: Simulation with greedy approach
Time Complexity: O(n^2) where n is the length of the permutation
Space Complexity: O(n) for storing the permutation array

This code checks whether it's possible to reduce a permutation to all zeros 
by performing exactly one operation for each k from 1 to n. Each operation 
involves choosing a subarray of length k and subtracting 1 from every element 
in that subarray. The key idea is to simulate the process backwards or check 
if there's an order of operations that can lead to all zeros.
"""

for _ in range(int(input())):  # For each test case
    n = int(input())  # Read length of permutation
    a = list(map(int, input().split()))  # Read the permutation
    flag = True  # Flag to track whether we're still in decreasing phase
    for i in range(1, n):  # Iterate through array elements starting from index 1
        if a[i - 1] > a[i] and flag:  # If previous element is greater and we are in decreasing phase
            flag = False  # Switch to increasing phase
        elif a[i - 1] < a[i] and not flag:  # If previous element is smaller but we're in increasing phase
            print("NO")  # This means we have an invalid transition; impossible to make all zeros
            break  # Exit loop early
    else:  # If loop completed without breaking (no invalid transitions)
        print("YES")  # It's possible to make all elements zero


# https://github.com/VaHiX/codeForces/