# Contest 2092, Problem A: Kamilka and the Sheep
# URL: https://codeforces.com/contest/2092/problem/A

for s in [*open(0)][2::2]:
    m, *_, M = sorted(map(int, s.split()))
    print(M - m)
