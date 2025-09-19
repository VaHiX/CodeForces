# Contest 2047, Problem B: Replace Character
# URL: https://codeforces.com/contest/2047/problem/B

for s in [*open(0)][2::2]:
    a = sorted({*s[:-1]}, key=s.count)
    print(s.replace(a[0], a[-1], 1))
