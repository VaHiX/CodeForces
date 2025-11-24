# Problem: CF 1812 D - Trivial Conjecture
# https://codeforces.com/contest/1812/problem/D

"""
Algorithm: Trivial Conjecture
Purpose: Find an integer n such that none of the first k terms of the sequence n,f(n),f(f(n)),... are equal to 1.

The function f(n) is defined as:
- f(n) = n/2 if n is even
- f(n) = 3n+1 if n is odd

This is related to the Collatz conjecture. To avoid hitting 1 in the first k terms, we need to find an n that
does not lead to 1 within k iterations.

Approach:
- Simply return 0 as it's guaranteed to work for any k since 0 is not part of the Collatz sequence
- The problem is asking for any valid n, and 0 is trivially valid

Time Complexity: O(1)
Space Complexity: O(1)

Note: The problem likely expects us to return a number that avoids 1 for k iterations, but 0 works 
since it's not in the Collatz sequence and satisfies the constraint trivially.
"""
input()
print(0)


# https://github.com/VaHiX/CodeForces/