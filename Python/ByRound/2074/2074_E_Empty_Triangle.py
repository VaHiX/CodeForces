# Contest 2074, Problem E: Empty Triangle
# URL: https://codeforces.com/contest/2074/problem/E

import random

for _ in range(int(input())):
    n = int(input())
    p = [1, 2, 3]
    for i in range(75):
        print(f"? {p[0]} {p[1]} {p[2]}")
        nw = int(input())
        if nw == 0:
            break
        p[random.randint(0, 2)] = nw
    print(f"! {p[0]} {p[1]} {p[2]}")
