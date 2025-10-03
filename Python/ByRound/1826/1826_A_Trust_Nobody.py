# Contest 1826, Problem A: Trust Nobody
# URL: https://codeforces.com/contest/1826/problem/A

for s in [*open(0)][2::2]:
    n = len(a := s.split())
    b = [0] * 101
    r = i = -1
    for x in a:
        b[int(x)] += 1
    for x in b:
        i += 1
        n -= x
        r = (r, i)[n == i]
    print(r)
