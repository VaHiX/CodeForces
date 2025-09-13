# Contest 1995, Problem A: Diagonals
# URL: https://codeforces.com/contest/1995/problem/A

for s in [*open(0)][1:]:
    n, k = map(int, s.split())
    r = 0
    while -k < k:
        r += 1
        k -= n - r // 2
    print(r)
