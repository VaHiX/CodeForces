# Problem: CF 1740 A - Factorise N+M
# https://codeforces.com/contest/1740/problem/A

"""
Purpose: Given a prime number n, find a prime number m such that n + m is not prime.
Algorithm: 
- For any prime n > 2, we can choose m = 2, because n + 2 will be even and greater than 2, hence not prime.
- For n = 2, we need a different approach. We can choose m = 7, because 2 + 7 = 9 = 3 * 3, which is not prime.
Time Complexity: O(1) - constant time since the solution doesn't depend on input size.
Space Complexity: O(1) - constant space used.
"""
print("7\n" * int(input()))


# https://github.com/VaHiX/CodeForces/