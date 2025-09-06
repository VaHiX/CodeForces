# Contest 2102, Problem C: Mex in the Grid
# URL: https://codeforces.com/contest/2102/problem/C

for _ in range(int(input())):
    n = int(input())
    m = [[0] * n for _ in range(n)]
    g = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    i = j = n // 2
    if n % 2 == 0:
        i -= 1
        j -= 1
    val = 0
    m[i][j] = val
    val += 1
    step = 1
    while val < n * n:
        for d in range(4):
            x, y = g[d]
            for _ in range(step):
                if val >= n * n:
                    break
                i += x
                j += y
                if 0 <= i < n and 0 <= j < n:
                    m[i][j] = val
                    val += 1
            if d % 2 == 1:
                step += 1
    res = []
    for row in m:
        res.append(" ".join(map(str, row)))
    print("\n".join(res))
