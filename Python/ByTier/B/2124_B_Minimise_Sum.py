# Contest 2124, Problem B: Minimise Sum
# URL: https://codeforces.com/contest/2124/problem/B

for s in [*open(0)][2::2]:
    a, b, *_ = map(int, s.split())
    print(a + min(a, b))
