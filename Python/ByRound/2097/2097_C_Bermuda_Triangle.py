# Problem: CF 2097 C - Bermuda Triangle
# https://codeforces.com/contest/2097/problem/C

"""
C. Bermuda Triangle

Purpose:
This code determines whether an airplane traveling inside a triangular region (with vertices at (0,0), (0,n), and (n,0)) can escape by reaching one of the triangle's vertices, and if so, how many times it hits the boundary before escaping.

Algorithms/Techniques:
- Mathematical simulation with reflections using modular arithmetic,
- Linear Diophantine equations to solve for reflection times,
- GCD-based reduction of vector components,
- Modular inverse computation for solving congruences.

Time Complexity: O(log(min(vx, vy))) per test case due to GCD calculations and modular inverse computation.
Space Complexity: O(1) - only a constant amount of extra space used.
"""
import math
import sys

input = sys.stdin.readline
MOD = 998244353
INF = 10**9
ivar = lambda: int(input())
ivars = lambda: map(int, input().split())
ilist = lambda: list(map(int, input().split()))
istr = lambda: input().strip()

def solve():
    n, x, y, vx, vy = ivars()
    # Reduce velocity vector using GCD to simplify computation
    g = math.gcd(vx, vy)
    vx //= g
    vy //= g
    
    # Find how many times we can take full cycles in x and y directions
    gx = math.gcd(vx, n)
    gy = math.gcd(vy, n)
    
    # Check if it's possible to reach a vertex based on initial position relative to step size
    if x % gx or y % gy:
        return -1
    
    # Normalize coordinates and velocity components by GCD
    xc = x
    yc = y
    vxc = vx
    vyc = vy
    x //= gx
    y //= gy
    vx //= gx
    vy //= gy
    nx = n // gx
    ny = n // gy
    
    # Compute time to hit boundary in each direction using modular inverse
    a = (-x) * pow(vx, -1, nx) % nx  # Solve x + t*vx ≡ 0 (mod nx)
    b = (-y) * pow(vy, -1, ny) % ny  # Solve y + t*vy ≡ 0 (mod ny)
    
    # Check compatibility with modular system
    g = math.gcd(nx, ny)
    if a % g != b % g:
        return -1
    
    # Solve combined congruence equation to find valid t values
    s = (a // g - b // g) * pow(ny // g, -1, nx // g)
    t = (s * ny + b) % n
    
    # Validate if point after reflection touches a vertex
    if (xc + (t * vxc)) % n == 0 and (yc + (t * vyc)) % n == 0:
        fx, fy = (xc + (t * vxc)) // n, (yc + (t * vyc)) // n
        odd = (fx + fy) // 2
        even = abs(fx - fy) // 2
        # Return total count of boundary hits minus 2 (because we don't count the final escape vertex)
        return fx + fy + odd + even - 2
    else:
        return -1

print("\n".join(map(str, (solve() for _ in range(int(input()))))))


# https://github.com/VaHiX/codeForces/