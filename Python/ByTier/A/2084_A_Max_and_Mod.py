# Contest 2084, Problem A: Max and Mod
# URL: https://codeforces.com/contest/2084/problem/A

for n in [*open(0)][1:]:
    print(*([-1], (n := int(n), *range(1, n)))[n % 2])
