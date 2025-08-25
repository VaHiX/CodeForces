# Contest 2066, Problem E: Tropical Season
# URL: https://codeforces.com/contest/2066/problem/E


def contains(n):
    n += 2**20
    while n > 0:
        yield n
        n //= 2


def between(a, b):
    b = min(b, 2**20 - 1)
    a += 2**20
    b += 2**20
    while a < b:
        if a % 2 == 1:
            yield a
        if b % 2 == 0:
            yield b
        a = (a + 1) // 2
        b = (b - 1) // 2
    if a == b:
        yield a


def getleft(st, v):
    lb = v + 2**20 - 1
    if st[lb + 1] > v:
        return v
    llb = 2**20
    while lb >= llb and st[lb] == 0:
        lb = (lb - 1) // 2
        llb //= 2
    if lb < llb:
        return 0
    while lb < 2**20:
        lb = 2 * lb + 1
        if st[lb] == 0:
            lb -= 1
    return lb - 2**20


def getright(st, v):
    ub = v + 2**20 + 1
    if st[ub - 1] > v:
        return v
    uub = 2**21
    while ub < uub and st[ub] == 0:
        ub = (ub + 1) // 2
        uub //= 2
    if ub == uub:
        return -1
    while ub < 2**20:
        ub *= 2
        if st[ub] == 0:
            ub += 1
    return ub - 2**20


n, q = map(int, input().split())
stv = [0] * (2**21)
std = [0] * (2**21)
a = [int(i) for i in input().split()]


def works():
    ptw = -1
    ntw = 0
    while ntw > ptw:
        ptw = ntw
        nntw = sum(stv[i] for i in between(0, ntw))
        while nntw > ntw:
            ntw = nntw
            nntw = sum(stv[i] for i in between(0, ntw))
        nntw = sum(std[i] for i in between(0, ntw))
        ex = nntw - ntw
        if (
            ex < 2**20
            and stv[2**20 + ex] == ex
            and ntw == sum(stv[i] for i in between(0, ex - 1))
        ):
            nntw = ntw
        ntw = nntw
    miss = stv[1] - ntw
    if miss < 2**20 and stv[2**20 + miss] == miss:
        return "Yes"
    return "No"


for v in a:
    stv[v + 2**20] += v
for i in range(2**20 - 1, 0, -1):
    stv[i] = stv[2 * i] + stv[2 * i + 1]
for v in a:
    d = getleft(stv, v)
    for i in contains(v - d):
        std[i] += v
print(works())
for _ in range(q):
    s, b = input().split()
    b = int(b)
    if s == "+":
        r = b if stv[2**20 + b] > 0 else getright(stv, b)
        l = getleft(stv, b)
        for i in contains(b):
            stv[i] += b
        for i in contains(0 if r == b else b - l):
            std[i] += b
        if r > 0 and l < b and (r == b or stv[2**20 + r] == r):
            for i in contains(r - l):
                std[i] -= r
            for i in contains(r - b):
                std[i] += r
    else:
        r = getright(stv, b)
        for i in contains(b):
            stv[i] -= b
        l = getleft(stv, b)
        for i in contains(0 if r == b else b - l):
            std[i] -= b
        if r > 0 and l < b and stv[2**20 + r] == r:
            for i in contains(r - b):
                std[i] -= r
            for i in contains(r - l):
                std[i] += r
    print(works())
