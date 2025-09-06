# Contest 2090, Problem A: Treasure Hunt
# URL: https://codeforces.com/contest/2090/problem/A

for s in [*open(0)][1:]:
    x, y, a = map(int, s.split())
    print("YNEOS"[a % (x + y) < x :: 2])
