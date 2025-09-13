# Contest 2067, Problem C: Devyatkino
# URL: https://codeforces.com/contest/2067/problem/C

for i in [*open(0)][1:]:
    t = int(i)
    l = []
    n = t
    for i in range(1, 10):
        c = 0
        while "7" not in str(t):
            t += int(i * "9")
            c += 1
        l += [c]
        t = n
    print(min(l))
