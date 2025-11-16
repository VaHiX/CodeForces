# Problem: CF 1744 E1 - Divisible Numbers (easy version)
# https://codeforces.com/contest/1744/problem/E1

import math

g = math.gcd
for i in range(int(input())):
    a, b, c, d = map(int, input().split())
    x = a * b
    ans = (-1, -1)
    for i in range(a + 1, c + 1):  # Iterate through all possible values of x in range (a, c]
        m = g(x, i)  # Compute GCD of x and i to find how much of x can be shared with i
        p = x // m   # Quotient of x divided by GCD, represents the part of x not covered by i
        r = b // p + 1  # Minimum value for y such that y*p >= b (ensuring divisibility)
        l = d // p   # Maximum value for y such that y*p <= d
        if r <= l:   # Check if there exists a valid y within range (b, d]
            ans = (i, r * p)  # Found a valid pair (x, y)
            break
    print(*ans)


# https://github.com/VaHiX/CodeForces/