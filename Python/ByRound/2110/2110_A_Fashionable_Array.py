# Contest 2110, Problem A: Fashionable Array
# URL: https://codeforces.com/contest/2110/problem/A

for s in [*open(0)][2::2]:
    a = [x % 2 for x in sorted(map(int, s.split()))]
    print(min(a.index(a[-1]), a[::-1].index(a[0])))
