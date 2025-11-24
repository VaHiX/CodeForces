# Problem: CF 2139 C - Cake Assignment
# https://codeforces.com/contest/2139/problem/C

"""
C. Cake Assignment

Purpose:
This code solves the problem of redistributing cakes between Chocola and Vanilla such that 
Chocola ends up with exactly x cakes and Vanilla gets the rest. The operations allowed are:
- Chocola gives half her cakes to Vanilla (if Chocola has even number of cakes)
- Vanilla gives half her cakes to Chocola (if Vanilla has even number of cakes)

Approach:
We simulate the reverse process - starting from the target configuration (x cakes for Chocola), 
we work backwards to find the minimum sequence of operations needed. At each step, we determine
whether we should double the count for Chocola or Vanilla based on the current state and the 
binary representation of x.

Time Complexity: O(k) per test case, where k is the exponent in 2^k.
Space Complexity: O(k) for storing the operations sequence.
"""

q = int(input())
for _ in range(q):
    k, x = map(int, input().split())
    n = 2**k
    ans = []
    while x != n:
        if x > n:
            # If x is greater than n, it means we are at a point where we need to "undo"
            # the process of Vanilla giving cakes to Chocola. So, we double x and mark operation 2.
            x = (x - n) * 2
            ans.append("2")
        else:
            # If x is less than or equal to n, it means we are at a point where we need to "undo"
            # the process of Chocola giving cakes to Vanilla. So, we double x and mark operation 1.
            x = 2 * x
            ans.append("1")
    ans.reverse()
    print(len(ans))
    print(" ".join(ans))


# https://github.com/VaHiX/codeForces/