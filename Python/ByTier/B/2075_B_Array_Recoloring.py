# Contest 2075, Problem B: Array Recoloring
# URL: https://codeforces.com/contest/2075/problem/B

R = lambda: map(int, input().split())
(t,) = R()
while t:
    t -= 1
    n, k = R()
    (*a,) = R()
    if k < 2:
        a.remove(r := max(a[:: n - 1]))
        r += max(a)
    else:
        r = sum(sorted(a)[~k:])
    print(r)
