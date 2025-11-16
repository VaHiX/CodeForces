# Problem: CF 1907 E - Good Triples
# https://codeforces.com/contest/1907/problem/E

"""
Code Purpose:
This code calculates the number of "good triples" (a, b, c) such that:
1. a + b + c = n
2. digit_sum(a) + digit_sum(b) + digit_sum(c) = digit_sum(n)

The key insight is based on the property that for a number n, we can compute how many digit combinations
satisfy the condition by precomputing digit sums for single-digit numbers and multiplying them
based on the digits of n.

Algorithms/Techniques:
- Precomputed digit sum map for digits 0-9.
- For each digit of n, multiply the result by the corresponding precomputed factorial-like value.
- This is a dynamic programming or combinatorics-based approach where the number of valid combinations
  is derived from the digit structure of n.

Time Complexity: O(log n) per test case, since we iterate through digits of n.
Space Complexity: O(1), as we use fixed-size arrays and variables.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()


def II():
    return int(input())


def SI():
    return sys.stdin.readline().rstrip()


def LII():
    return list(map(int, input().split()))


def TI():
    return map(int, input().split())


Y = "YES"
N = "NO"
if __name__ == "__main__":
    t = II()
    for i in range(t):
        n = II()
        m = n
        # Precomputed values for digit combinations (1, 3, 6, 10, 15, 21, 28, 36, 45, 55)
        # These are triangular numbers: 1, 1+2, 1+2+3, ..., 1+2+...+10
        mp = [1, 3, 6, 10, 15, 21, 28, 36, 45, 55]
        a = 1
        while n > 0:
            # Multiply the result by the precomputed value for the last digit of n
            a *= mp[n % 10]
            # Remove the last digit
            n //= 10
        print(a)


# https://github.com/VaHiX/CodeForces/