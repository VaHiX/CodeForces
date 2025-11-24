# Problem: CF 1748 D - ConstructOR 
# https://codeforces.com/contest/1748/problem/D

from math import gcd

t = int(input())
for _ in range(t):
    a, b, d = tuple(map(int, input().split()))
    # Reduce a, b, d by their GCD to simplify the problem
    i = gcd(gcd(gcd(1 << 30, a), b), d)
    a //= i
    b //= i
    d //= i
    # If d is even, no solution exists because both a|x and b|x must be multiples of d
    if d % 2 == 0:
        print(-1)
        continue
    # Compute initial x as a bitwise OR of a and b
    x = a | b
    # Prepare for modular arithmetic by computing a multiplicative inverse
    p = 1
    for __ in range(30):
        if p % 2:
            p += d
        p //= 2
    # Adjust x to make a|x and b|x divisible by d
    x += ((-x * p) % d) << 30
    # Scale back up to original values
    print(x * i)


# https://github.com/VaHiX/CodeForces/