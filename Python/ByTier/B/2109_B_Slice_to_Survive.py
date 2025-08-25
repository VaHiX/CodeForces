# Contest 2109, Problem B: Slice to Survive
# URL: https://codeforces.com/contest/2109/problem/B

f = lambda x, y: (x - 1).bit_length() - ~(y - 1).bit_length()
for s in [*open(0)][1:]:
    n, m, a, b = map(int, s.split())
    print(min(f(n - a + 1, m), f(a, m), f(n, m - b + 1), f(n, b)))
