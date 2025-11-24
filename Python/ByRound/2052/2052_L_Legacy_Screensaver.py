# Problem: CF 2052 L - Legacy Screensaver
# https://codeforces.com/contest/2052/problem/L

"""
Purpose:
This code solves a problem involving two rectangles moving inside a screen with elastic collisions.
The goal is to compute the limiting fraction of time (as t approaches infinity) during which the two rectangles overlap.

Algorithms:
1. Simulation of movement of two rectangles in x and y directions separately:
   - Each rectangle moves with constant velocity (dx, dy).
   - Collisions with screen boundaries reverse the corresponding velocity component.
   - The movements are simulated until a period repeats (periodic behavior).

2. Combining x and y movements:
   - The x-direction and y-direction behaviors are treated as separate periodic sequences.
   - Using least common multiple of periods to compute combined behavior over one full cycle.

3. Counting overlapping intervals:
   - For each step in the combined period, check if rectangles overlap.
   - Use modular arithmetic to avoid simulating too many steps.

Time Complexity: O(W * H) per test case, where W and H are the dimensions of the screen.
Space Complexity: O(W + H) for storing the simulation vectors.

Techniques:
- Periodic simulation
- Greatest common divisor (GCD) for simplifying fractions
- Modular arithmetic for efficient cycle reduction
"""

T = int(input())
from math import gcd


def simulate_vector(W, w1, x1, dx1, w2, x2, dx2):
    # Compute period of motion for each rectangle in x direction
    p1 = (W - w1) * 2
    p2 = (W - w2) * 2
    # LCM of periods
    if gcd(p1, p2) == 1:
        T = p1 * p2
    else:
        g = gcd(p1, p2)
        T = g * (p1 // g) * (p2 // g)
    # Initialize histogram of overlaps for one period
    hz = [0] * T
    # Rectangle positions
    l1 = x1
    r1 = x1 + w1 - 1
    l2 = x2
    r2 = x2 + w2 - 1
    # Simulate each time step in period T
    for t in range(T):
        # Check overlap in this step
        if l1 <= l2 < r1 or l1 <= r2 <= r1 or l2 <= l1 <= r2 or l2 <= r1 <= r2:
            hz[t] = 1
        # Update dx1 based on collision
        if dx1 == 1:
            if r1 == W - 1:
                dx1 = -1
        else:
            if l1 == 0:
                dx1 = 1
        l1 += dx1
        r1 += dx1
        # Update dx2 based on collision
        if dx2 == 1:
            if r2 == W - 1:
                dx2 = -1
        else:
            if l2 == 0:
                dx2 = 1
        l2 += dx2
        r2 += dx2
    return hz


for _ in range(T):
    W, H = map(int, input().strip().split())
    w1, h1, x1, y1, dx1, dy1 = map(int, input().strip().split())
    w2, h2, x2, y2, dx2, dy2 = map(int, input().strip().split())
    # Simulate x-direction behavior
    horiz_vec = simulate_vector(W, w1, x1, dx1, w2, x2, dx2)
    # Simulate y-direction behavior
    vert_vec = simulate_vector(H, h1, y1, dy1, h2, y2, dy2)
    Hlen = len(horiz_vec)
    Vlen = len(vert_vec)
    # Compute GCD of both periods to get combined period
    G = gcd(Hlen, Vlen)
    # Reduce vector lengths to G for efficient counting
    Hnew = [0] * G
    Vnew = [0] * G
    for i in range(Hlen):
        Hnew[i % G] += horiz_vec[i]
    for i in range(Vlen):
        Vnew[i % G] += vert_vec[i]
    # Total number of overlapping steps in one full combined cycle
    num = 0
    for i in range(G):
        num += Vnew[i] * Hnew[i]
    # Total steps in combined cycle
    denom = Hlen * Vlen // G
    # Simplify fraction
    G = gcd(num, denom)
    print(f"{num//G}/{denom//G}")


# https://github.com/VaHiX/CodeForces/