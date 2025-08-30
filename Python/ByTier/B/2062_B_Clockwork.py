# Contest 2062, Problem B: Clockwork
# URL: https://codeforces.com/contest/2062/problem/B

for s in [*open(0)][2::2]:
    a = s.split()
    print(
        "NYOE S"[all(i * 2 < int(x) > len(a) + ~i << 1 for i, x in enumerate(a)) :: 2]
    )
