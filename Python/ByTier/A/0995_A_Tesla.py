# Contest 995, Problem A: Tesla
# URL: https://codeforces.com/contest/995/problem/A

n, k = map(int, input().split())
sp = [list(map(int, input().split())) for _ in range(4)]
res = []
sos = [(1, c) for c in range(n)] + [(2, c) for c in range(n - 1, -1, -1)]
L = 2 * n
for i in range(n):
    if sp[1][i] != 0 and sp[0][i] == sp[1][i]:
        car = sp[1][i] 
        sp[1][i] = 0
        res.append((car, 1, i + 1))
    if sp[2][i] != 0 and sp[3][i] == sp[2][i]:
        car = sp[2][i]
        sp[2][i] = 0
        res.append((car, 4, i + 1))

while True:
    flag = True
    for i in range(n):
        if sp[1][i] != 0 or sp[2][i] != 0:
            flag = False
            break
    if flag:
        break
    zero = -1
    for i, (a, b) in enumerate(sos):
        if sp[a][b] == 0:
            zero = i
            break
    if zero == -1:
        f = False
        for c in range(n):
            if sp[1][c] != 0 and sp[0][c] == sp[1][c]:
                car = sp[1][c]
                sp[1][c] = 0
                res.append((car, 1, c + 1))
                f = True
            if sp[2][c] != 0 and sp[3][c] == sp[2][c]:
                car = sp[2][c]
                sp[2][c] = 0
                res.append((car, 4, c + 1))
                f = True
        if not f:
            print(-1)
            exit()
        else:
            continue
    for i in range(1, L):
        tt = (zero - i) % L
        r, c = sos[tt]
        nr, nc = sos[(tt + 1) % L]
        if sp[r][c] != 0 and sp[nr][nc] == 0:
            car = sp[r][c]
            sp[r][c] = 0
            sp[nr][nc] = car
            res.append((car, nr + 1, nc + 1))
    for i in range(n):
        if sp[1][i] != 0 and sp[0][i] == sp[1][i]:
            car = sp[1][i]
            sp[1][i] = 0
            res.append((car, 1, i + 1))
        if sp[2][i] != 0 and sp[3][i] == sp[2][i]:
            car = sp[2][i]
            sp[2][i] = 0
            res.append((car, 4, i + 1))
    if len(res) > 20000:
        print(-1)
        exit()

print(len(res))
for a, b, c in res:
    print(a, b, c)
