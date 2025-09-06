# Contest 2072, Problem A: New World, New Me, New Array
# URL: https://codeforces.com/contest/2072/problem/A

for s in [*open(0)][1:]:
    n, k, p = map(int, s.split())
    r = -abs(k) // p
    print(-(r ** (-r <= n)))
