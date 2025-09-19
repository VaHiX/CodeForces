# Contest 2098, Problem E: Bermuda Triangle
# URL: https://codeforces.com/contest/2098/problem/E

from math import gcd, lcm
import sys

input = sys.stdin.readline
MOD = 10**9 + 7


def bezout(a, b):
    """
    Given integers a and b, return a tuple (x, y, g),
    where x*a + y*b == g == gcd(a, b).
    """
    # Apply the Extended Euclidean Algorithm:
    # use the normal Euclidean Algorithm on the RHS
    # of the equations
    #     u1*a + v1*b == r1
    #     u2*a + v2*b == r2
    # But carry the LHS along for the ride.
    u1, v1, r1 = 1, 0, a
    u2, v2, r2 = 0, 1, b

    while r2:
        q = r1 // r2
        u1, u2 = u2, u1 - q * u2
        v1, v2 = v2, v1 - q * v2
        r1, r2 = r2, r1 - q * r2
        assert u1 * a + v1 * b == r1
        assert u2 * a + v2 * b == r2

    if r1 < 0:
        u1, v1, r1 = -u1, -v1, -r1

    # a_coefficient, b_coefficient, gcd
    return (u1, v1, r1)


def crt(cong1, cong2):
    """
    Apply the Chinese Remainder Theorem:
        If there are any integers x such that
        x == a1 (mod n1) and x == a2 (mod n2),
        then there are integers a and n such that the
        above congruences both hold iff x == a (mod n)
    Given two compatible congruences (a1, n1), (a2, n2),
    return a single congruence (a, n) that is equivalent
    to both of the given congruences at the same time.

    Not all congruences are compatible. For example, there
    are no solutions to x == 1 (mod 2) and x == 2 (mod 4).
    For congruences (a1, n1), (a2, n2) to be compatible, it
    is sufficient, but not necessary, that gcd(n1, n2) == 1.
    """
    a1, n1 = cong1
    a2, n2 = cong2
    c1, c2, g = bezout(n1, n2)
    assert n1 * c1 + n2 * c2 == g

    if (a1 - a2) % g != 0:
        raise ValueError(f"Incompatible congruences {cong1} and {cong2}.")

    lcm = n1 // g * n2
    rem = (a1 * c2 * n2 + a2 * c1 * n1) // g
    return rem % lcm, lcm


def read_array(factory):
    return [factory(num) for num in input().strip().split()]


def print_array(arr):
    print(" ".join(map(str, arr)))


def solve(n, x, y, vx, vy):
    # Imagine the infinite tessellation of triangles.
    # (x + c*vx, y + c*vy) == (a*n, b*n)
    # Sadly, c does not have to be an integer.
    # print(n, x, y, vx, vy)
    g = gcd(vx, vy)
    vx //= g
    vy //= g
    # Now, c has to be an integer.
    # (x + c*vx, y + c*vy) == (a*n, b*n)
    if x % gcd(vx, n) != 0:
        return -1
    if y % gcd(vy, n) != 0:
        return -1
    # (c*vx, c*vy) == (-x, -y)   (mod n)
    gx = gcd(vx, n)
    cx = (-(x // gx)) * pow(vx // gx, -1, n // gx) % (n // gx)
    gy = gcd(vy, n)
    cy = (-(y // gy)) * pow(vy // gy, -1, n // gy) % (n // gy)
    # c == cx (mod n//gx)
    # c == cy (mod n//gy)
    g = gcd(n // gx, n // gy)
    if cx % g != cy % g:
        return -1
    # c == cx (mod n//gx)
    # c == cy (mod n//gy)
    c, cmod = crt((cx, n // gx), (cy, n // gy))
    if c == 0:
        c += cmod

    hor = (c * vy) // n
    ver = (c * vx) // n
    # adi = (c*vy+c*vx+n) // (2*n)
    adi = abs((y + c * vy) + (x + c * vx)) // (2 * n)
    # y = x + n + k*2*n
    dia = abs((y + c * vy) - (x + c * vx)) // (2 * n)
    # print('wow', abs(c*vy-c*vx), x+c*vx, y+c*vy)
    # print(n, x, y, vx, vy)
    # print(hor, ver, adi, dia)
    return hor + ver + adi + dia

    # f = crt
    # for ngx in range(1, 20):
    #     for ngy in range(1, 20):
    #         for cx in range(0, ngx):
    #             for cy in range(0, ngy):
    #                 for c in range(1, 100):
    #                     x1 = (c % ngx == cx) and (c % ngy == cy)
    #                     g = gcd(ngx, ngy)
    #                     if cx % g != cy % g: continue
    #                     # cg = chinese_remainder([ngx//g, ngy//g, g], [cx, cy, cx%g])
    #                     # l = (ngx//g) * (ngy//g) * g
    #                     x2 = c % f[1] == f[0] % f[1]
    #                     print(ngx, ngy, cx, cy)
    #                     assert x1 == x2
    # for n in range(1, 20):
    #     for x in range(1, n):
    #         for vx in range(1, 20):
    #             for c in range(1, 100):
    #                 gx = gcd(vx, n)
    #                 if x % gx != 0: continue
    #                 cx = (-(x//gx)) * pow(vx//gx, -1, n//gx) % (n//gx)
    #                 # x1 = (x + c*vx) % n == 0
    #                 x1 = (c*vx) % n == (-x) % n
    #                 x2 = c%(n//gx) == cx
    #                 print(x1, x2, n, x, vx, c)
    #                 assert x1 == x2
    return


if __name__ == "__main__":
    # Read in input:
    t = int(input())

    # Call solution:
    for _ in range(t):
        n, x, y, vx, vy = read_array(int)
        ans = solve(n, x, y, vx, vy)
        print(ans)
