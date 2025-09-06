# Contest 613, Problem A: Peter and Snow Blower
# URL: https://codeforces.com/contest/613/problem/A

import sys
import math

def dist2(x1, y1, x2, y2):
    return (x1 - x2) ** 2 + (y1 - y2) ** 2

def find_dist(x1, y1, x2, y2, X, Y):
    if x2 == x1:
        if min(y1, y2) <= Y <= max(y1, y2):
            return (x1 - X) ** 2
        else:
            return min(dist2(x1, y1, X, Y), dist2(x2, y2, X, Y))
    a = (y2 - y1) / (x2 - x1)
    b = y1 - a * x1
    x = (X + a * (Y - b)) / (1 + a * a)
    if min(x1, x2) <= x <= max(x1, x2):
        return dist2(x, a * x + b, X, Y)
    else:
        return min(dist2(x1, y1, X, Y), dist2(x2, y2, X, Y))

def main():
    N, X, Y = map(int, sys.stdin.readline().split())
    maxr = 0
    minr = 10**15
    pts = [tuple(map(int, sys.stdin.readline().split())) for _ in range(N)]
    pts.append(pts[0])
    for i in range(0, len(pts)-1):
        x, y = pts[i]
        r = dist2(x, y, X, Y)
        if r > maxr:
            maxr = r
        r = find_dist(x, y, pts[i+1][0], pts[i+1][1], X, Y)
        if r < minr:
            minr = r

    print ("%.10f" % (math.pi * (maxr - minr)))

if __name__ == '__main__':
    main()
