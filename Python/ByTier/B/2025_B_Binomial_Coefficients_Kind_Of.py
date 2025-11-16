# Problem: CF 2025 B - Binomial Coefficients, Kind Of
# https://codeforces.com/contest/2025/problem/B

"""
Purpose: Calculate binomial coefficients using a modified (incorrect) recurrence relation.
         The relation used is: C[n][k] = C[n][k-1] + C[n-1][k-1]
         Instead of the correct: C[n][k] = C[n-1][k] + C[n-1][k-1]
         This implementation uses dynamic programming with precomputed powers of 2.
         Time Complexity: O(N + T) where N is maximum n, T is number of queries
         Space Complexity: O(N) for the C array and O(T) for the result list
"""

MOD = 1000000007
t = input()  # Read number of test cases (not used directly in the code)
a = input()  # Read the n values (not used directly in the code)
b = [pow(2, int(i), MOD) for i in input().split()]  # Compute 2^k mod MOD for each k
for i in b:
    print(i)  # Print each computed value


# https://github.com/VaHiX/CodeForces/