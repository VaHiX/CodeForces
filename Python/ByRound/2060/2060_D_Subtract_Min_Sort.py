# Contest 2060, Problem D: Subtract Min Sort
# URL: https://codeforces.com/contest/2060/problem/D

for s in [*open(0)][2::2]:
    a = [*map(int, s.split()), -1]
    i = 0
    while a[i] <= a[i := i + 1]:
        a[i] -= a[i - 1]
    print("YNEOS"[a[i] > 0 :: 2])
