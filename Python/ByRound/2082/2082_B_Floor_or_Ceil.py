# Contest 2082, Problem B: Floor or Ceil
# URL: https://codeforces.com/contest/2082/problem/B

for s in [*open(0)][1:]:
    x, *a = map(int, s.split())
    f = lambda i, p=x: p + (i << (k := min(30, a[i]))) - i >> k
    print(f(0, f(1)), f(1, f(0)))
