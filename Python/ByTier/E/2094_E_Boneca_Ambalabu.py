# Contest 2094, Problem E: Boneca Ambalabu
# URL: https://codeforces.com/contest/2094/problem/E

for s in [*open(0)][2::2]:
    a = [*map(int, s.split())]
    c = [0] * 30
    for x in a:
        for b in range(30):
            c[b] += x >> b & 1
    mx = 0
    for x in a:
        v = 0
        for b in range(30):
            t = x >> b & 1
            v += (c[b] if 1 - t else len(a) - c[b]) << b
        mx = max(mx, v)
    print(mx)
