# Problem: CF 2140 F - Sum Minimisation
# https://codeforces.com/contest/2140/problem/F

"""
F. Sum Minimisation

Purpose:
This code solves an optimization problem where we can perform operations on an array to reduce its sum.
Each operation allows selecting k distinct indices, computes a sum x and decreases the y smallest values (according to value then index) by 1,
where y = x % k.

Key Algorithm:
- The approach checks for special cases like when all elements are equal or when n is large.
- It also evaluates whether the array can be reduced indefinitely.
- For small arrays, advanced logic is applied to test reductions using modular arithmetic properties and greedy checks.

Time Complexity: O(n^2) in worst case due to nested loops checking modulo properties for all bases from 2 to n.
Space Complexity: O(n) for storing input and temporary arrays during computation.

Techniques:
- Modular arithmetic
- Greedy strategy with conditionals
- Set-based uniqueness checks
"""

import sys

input = sys.stdin.readline


def fg():
    return int(input())


def fgh():
    return [int(xx) for xx in input().split()]


def df():
    print("No")


def sd():
    print("Yes")


def good(a):
    fl = 1
    for i in range(2, len(a)):
        d = []
        for j in range(len(a)):
            d.append(a[j] % i)
        if len(set(d)) >= 2:  # Checks if there are multiple remainders when divided by i
            fl = 0
            break
    if fl:
        if sum(a) % len(a) == 0:
            return True
    return False


for __ in range(fg()):
    n = fg()
    a = fgh()
    if n >= 100:
        if len(set(a)) == 1:  # All elements are same, can multiply by n
            print(a[0] * n)
        else:
            print(-1)  # Not reducible indefinitely but not trivially so
    else:
        if n == 1:
            print(a[0])
            continue
        if n == 2:
            print((a[0] + a[1]) - (a[0] + a[1]) % 2)
        else:
            if good(a):  # If the initial array satisfies condition for reduction
                print(sum(a))
                continue
            if (sum(a) % n) != 1:  # Check divisibility condition
                print(-1)
                continue
            a.sort()  # Sorting helps in greedy-like behavior
            if not good(a[1:]):  # Check subarray starting from index 1
                print(-1)
                continue
            if sum(a) % n != 1:  # Again check the same divisibility
                print(-1)
                continue
            t = 0
            for i in range(2, n):
                if (a[0] + (i - 1) * a[1]) % i > 1:
                    t = 1
            if t:
                print(-1)
                continue
            a[0] -= 1  # Greedy decrement of first element
            fl = 1
            for i in range(2, n):
                d = []
                for j in range(n):
                    d.append(a[j] % i)
                if len(set(d)) >= 2:  # Another modular check
                    fl = 0
                    break
            if fl:
                print(sum(a))
            else:
                print(-1)


# https://github.com/VaHiX/codeForces/