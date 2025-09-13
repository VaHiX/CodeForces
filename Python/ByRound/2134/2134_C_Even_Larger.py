# Contest 2134, Problem C: Even Larger
# URL: https://codeforces.com/contest/2134/problem/C

for s in [*open(0)][2::2]:
    for i in range(2, len(a := [*map(int, s.split()), r := 0]), 2):
        d = min(c := max(0, a[i - 2] + a[i] - a[i - 1]), a[i])
        r += c
        a[i] -= d
        a[i - 2] -= c - d
    print(r)
