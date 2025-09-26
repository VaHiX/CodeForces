# Contest 2072, Problem B: Having Been a Treasurer in the Past, I Help Goblins Deceive
# URL: https://codeforces.com/contest/2072/problem/B

for s in [*open(0)][2::2]:
    d, m = map(s.count, "-_")
    print(d // 2 * (-~d // 2) * m)
