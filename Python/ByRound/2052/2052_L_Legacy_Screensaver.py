# Contest 2052, Problem L: Legacy Screensaver
# URL: https://codeforces.com/contest/2052/problem/L

T = int(input())
from math import gcd


def simulate_vector(W, w1, x1, dx1, w2, x2, dx2):

    p1 = (W - w1) * 2
    p2 = (W - w2) * 2

    if gcd(p1, p2) == 1:
        T = p1 * p2
    else:
        g = gcd(p1, p2)
        T = g * (p1 // g) * (p2 // g)
    # print(T)
    hz = [0] * T

    # simulate
    l1 = x1
    r1 = x1 + w1 - 1
    l2 = x2
    r2 = x2 + w2 - 1

    for t in range(T):
        if l1 <= l2 < r1 or l1 <= r2 <= r1 or l2 <= l1 <= r2 or l2 <= r1 <= r2:
            hz[t] = 1
        # print(l1,r1,'  ',l2,r2)
        # update rects
        if dx1 == 1:
            if r1 == W - 1:
                dx1 = -1
        else:
            if l1 == 0:
                dx1 = 1
        l1 += dx1
        r1 += dx1

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

    horiz_vec = simulate_vector(W, w1, x1, dx1, w2, x2, dx2)
    vert_vec = simulate_vector(H, h1, y1, dy1, h2, y2, dy2)

    # print(horiz_vec)
    # print(vert_vec)
    # now determine total overlap/matching

    Hlen = len(horiz_vec)
    Vlen = len(vert_vec)

    G = gcd(Hlen, Vlen)
    if True:  # G==1:
        Hnew = [0] * G
        Vnew = [0] * G
        for i in range(Hlen):
            Hnew[i % G] += horiz_vec[i]
        for i in range(Vlen):
            Vnew[i % G] += vert_vec[i]
        num = 0
        for i in range(G):
            num += Vnew[i] * Hnew[i]

        denom = Hlen * Vlen // G

        G = gcd(num, denom)
        print(f"{num//G}/{denom//G}")
