# Contest 2036, Problem A: Quintomania
# URL: https://codeforces.com/contest/2036/problem/A

for s in [*open(0)][2::2]:
    a = (*map(int, s.split()),)
    print("NYOE S"[{abs(x - y) for x, y in zip(a, a[1:])} <= {5, 7} :: 2])
