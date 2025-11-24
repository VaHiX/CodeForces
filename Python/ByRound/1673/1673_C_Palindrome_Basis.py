# Problem: CF 1673 C - Palindrome Basis
# https://codeforces.com/contest/1673/problem/C

"""
Palindrome Basis

This problem involves counting the number of ways to express a given positive integer n as a sum of palindromic integers.
The approach uses dynamic programming where we iterate through all palindromic numbers up to n and update a DP array
to count the number of ways each sum can be achieved.

Algorithms:
- Dynamic Programming (DP)
- Palindrome checking using string reversal
- Preprocessing all palindromes up to 40000

Time Complexity: O(n * sqrt(n)) where n is up to 40000
Space Complexity: O(n) for the DP array and palindrome storage

The solution precomputes all palindromic numbers up to 40000 and then uses a DP approach similar to unbounded knapsack,
where for each palindromic number, we update counts for all sums greater than or equal to that number.
"""
M = 10**9 + 7
m = 40001
r = range
v = [1] + [0] * m
for i in r(1, m):
    if str(i) == str(i)[::-1]:  # Check if the number is palindromic
        for j in r(i, m):
            v[j] = v[j] % M + v[j - i]  # Update DP array with new combinations
for n in [*open(0)][1:]:
    print(v[int(n)] % M)  # Output result for each test case


# https://github.com/VaHiX/CodeForces/