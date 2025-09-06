# Contest 2091, Problem C: Combination Lock
# URL: https://codeforces.com/contest/2091/problem/C

for n in [*open(0)][1:]:
    print(*([-1], range(n := int(n), 0, -1))[n % 2])
