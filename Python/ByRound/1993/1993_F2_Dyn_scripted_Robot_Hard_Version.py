# Problem: CF 1993 F2 - Dyn-scripted Robot (Hard Version)
# https://codeforces.com/contest/1993/problem/F2

"""
Algorithm: 
- Simulate the first few executions to detect periodic behavior.
- Identify the cycle of positions and transitions.
- Use mathematical techniques to compute how many times origin (0,0) is visited in k executions.
- Time complexity: O(n * log(min(w,h)) + number_of_unique_positions)
- Space complexity: O(n)

Techniques:
- Modular arithmetic for periodicity detection.
- Extended Euclidean algorithm for solving modular equations.
- GCD and LCM for cycle detection.
"""

from math import gcd

ans = []
for _ in range(int(input())):
    n, k, w, h = [int(t) for t in input().split()]
    w *= 2  # scale up to simulate bounds
    h *= 2
    px, py = 0, 0
    m = {}
    # Run through the script and track all visited positions (mod w, h)
    for inst in input():
        if inst == "U":
            py = (py + 1) % h
        if inst == "D":
            py = (py + h - 1) % h
        if inst == "L":
            px = (px + w - 1) % w
        if inst == "R":
            px = (px + 1) % w
        m[(px, py)] = m[(px, py)] + 1 if (px, py) in m else 1
    # Compute cycle lengths for x and y positions
    gx = gcd(px, w)
    gy = gcd(py, h)
    mx = w // gx  # x-period
    my = h // gy  # y-period
    G = gcd(mx, my)  # gcd of periods
    dx = mx // G  # x-part of reduced period
    dy = my // G  # y-part of reduced period
    L = mx * my // G  # total cycle length
    res = 0
    # For each unique position visited, determine how many times it repeats in k steps
    for a, b in m:
        if a % gx or b % gy:  # skip if doesn't align with period
            continue
        # Use modular inverse to solve linear Diophantine equation
        r1 = -(a // gx) * pow(px // gx, -1, mx)
        r2 = -(b // gy) * pow(py // gy, -1, my)
        if (r1 - r2) % G:
            continue
        s = r1 % G
        r1 = (r1 - s) // G
        r2 = (r2 - s) // G
        t = (r1 % dx) + dx * ((r2 - (r1 % dx)) * pow(dx, -1, dy))
        t = t * G + s
        t = ((t % L) + L) % L
        # Count contributions to final answer
        res += m[(a, b)] * ((k - 1 - t) // L + 1)
    ans.append(res)
for w in ans:
    print(w)


# https://github.com/VaHiX/CodeForces/