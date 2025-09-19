# Contest 2064, Problem B: Variety is Discouraged
# URL: https://codeforces.com/contest/2064/problem/B

for s in [*open(0)][2::2]:
    n = len(a := [*map(int, s.split())])
    m = [0] * n
    for i in a:
        m[i - 1] += 1
    b = l = 0
    r = [0, 0]
    for i in range(n):
        if m[a[i] - 1] != 1:
            l = i + 1
        elif b < i - l + 1:
            b = i - l + 1
            r = [l, i]
    if b:
        print(r[0] + 1, r[1] + 1)
    else:
        print(0)
