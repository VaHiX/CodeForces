# Problem: CF 1725 C - Circular Mirror
# https://codeforces.com/contest/1725/problem/C

"""
Circular Mirror Problem

Algorithm:
- This problem involves counting valid colorings of lamps placed on a circle such that no three lamps forming a right triangle have the same color.
- The key insight is to determine if a right triangle can be formed by certain combinations of lamps on the circle.
- We use the fact that a right triangle on a circle (inscribed) has one side as a diameter.
- So the problem reduces to identifying diametric pairs of lamps and handling those constraints using combinatorics and modular arithmetic.
- We compute modular exponentiations and combinations using precomputed factorials.

Time Complexity: O(N + M)
Space Complexity: O(N + M)

"""
import sys

input = lambda: sys.stdin.readline().strip()


p = 998244353


def f(s, i):
    """Fast modular exponentiation"""
    global p
    if i == 0:
        return 1
    elif i % 2 == 1:
        return (s * f(s, i - 1)) % p
    else:
        return (f(s, i // 2) ** 2) % p


# Precompute factorials
b = [1] * 300001
for i in range(1, 300001):
    b[i] = (b[i - 1] * i) % p

# Precompute inverse factorials
d = [1] * 300001
k = f(b[-1], p - 2)
for i in range(300000, 0, -1):
    d[i] = k
    k *= i
    k %= p

# Read input
n, m = map(int, input().split())
a = list(map(int, input().split()))


s = sum(a)
if s % 2 == 1:
    # If total arc length is odd, no diametric pairs, all colorings are valid
    print(f(m, n))
else:
    # Find number of diametric pairs (half the total circle)
    k = 0
    l = 0
    j = 0
    for i in range(n):
        while k < s // 2:
            k += a[j]
            j += 1
            j %= n
        if k == s // 2:
            l += 1
        k -= a[i]
    l //= 2  # Count of diametric pairs
    
    # Calculate valid colorings
    ans = 0
    for i in range(min(l, m) + 1):
        # Calculate combination of choosing i diametric pairs with same color
        c = b[m] * d[m - i]
        c %= p
        c *= b[l] * d[i] * d[l - i]
        c %= p
        # Multiply by possibilities for remaining lamps
        c *= f(((m - i) * (m - i - 1)) % p, l - i)
        c %= p
        c *= f(m - i, n - 2 * l)
        c %= p
        ans += c
        ans %= p
    print(ans)


# https://github.com/VaHiX/CodeForces/