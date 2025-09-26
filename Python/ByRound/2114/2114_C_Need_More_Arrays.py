# Contest 2114, Problem C: Need More Arrays
# URL: https://codeforces.com/contest/2114/problem/C

for s in [*open(0)][2::2]:
    r = 0
    p = -1
    for x in map(int, s.split()):
        if p + 1 < x:
            r += 1
            p = x
    print(r)
