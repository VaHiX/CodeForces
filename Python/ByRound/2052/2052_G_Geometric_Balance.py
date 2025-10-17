# Contest 2052, Problem G: Geometric Balance
# URL: https://codeforces.com/contest/2052/problem/G


import sys

input = lambda: sys.stdin.readline().strip()

from functools import cmp_to_key

# def tmpcmp(a, b):
#     return a<b
# a = [3 ,5, 1, 2, 4]
# a.sort(key=cmp_to_key(tmpcmp))
# print(a)
# exit()


n = int(input())
op = []
for i in range(n):
    s, d = input().split()
    d = int(d)

    # if s != "rotate":
    #     d *= 128

    if len(op) and op[-1][0] == s:
        op[-1][1] += d
        continue

    op.append([s, d])

# print(op)

pts = set()

dir = 0
dx = [[2, 0], [0, 1], [0, 0], [0, -1], [-2, 0], [0, -1], [0, 0], [0, 1]]
dy = [[0, 0], [0, 1], [2, 0], [0, 1], [0, 0], [0, -1], [-2, 0], [0, -1]]

x, y = [0, 0], [0, 0]
pts.add((tuple(x), tuple(y)))

for [s, d] in op:
    if s == "rotate":
        dir = (dir + d // 45) % 8
    else:
        x[0] += d * dx[dir][0]
        x[1] += d * dx[dir][1]
        y[0] += d * dy[dir][0]
        y[1] += d * dy[dir][1]

    pts.add((tuple(x), tuple(y)))


def cmp2(p1, p2):
    def cmp(pp1, pp2):
        a, b = pp1
        c, d = pp2

        # a-c | (d-b) v2

        if a >= c:
            if d >= b:
                if pow(a - c, 2) <= 2 * pow(d - b, 2):
                    return -1
                else:
                    return 1
            else:
                return 1
        else:
            if d >= b:
                return -1
            else:
                if pow(a - c, 2) >= 2 * pow(d - b, 2):
                    return -1
                else:
                    return 1

    if p1[0] == p2[0]:
        return cmp(p1[1], p2[1])
    return cmp(p1[0], p2[0])


def cmp3(p1, p2):
    def cmp2(p1, p2):
        def cmp(pp1, pp2):
            a, b = pp1
            c, d = pp2

            # a + b v2 <= c + d v2
            # a-c <= (d-b) v2

            if a >= c:
                if d >= b:
                    if pow(a - c, 2) <= 2 * pow(d - b, 2):
                        return -1
                    else:
                        return 1
                else:
                    return 1
            else:
                if d >= b:
                    return -1
                else:
                    if pow(a - c, 2) >= 2 * pow(d - b, 2):
                        return -1
                    else:
                        return 1

        if p1[0] == p2[0]:
            return cmp(p1[1], p2[1])
        return cmp(p1[0], p2[0])

    return cmp2(p1[0], p2[0])


def cmp4(p1, p2):
    def cmp2(p1, p2):
        def cmp(pp1, pp2):
            a, b = pp1
            c, d = pp2

            # a + b v2 <= c + d v2
            # a-c <= (d-b) v2

            if a >= c:
                if d >= b:
                    if pow(a - c, 2) <= 2 * pow(d - b, 2):
                        return -1
                    else:
                        return 1
                else:
                    return 1
            else:
                if d >= b:
                    return -1
                else:
                    if pow(a - c, 2) >= 2 * pow(d - b, 2):
                        return -1
                    else:
                        return 1

        if p1[0] == p2[0]:
            return cmp(p1[1], p2[1])
        return cmp(p1[0], p2[0])

    if p1[0] == p2[0]:
        return cmp2(p1[1], p2[1])
    return cmp2(p1[0], p2[0])


pts = list(pts)
pts.sort(key=cmp_to_key(cmp2))

ptidx = dict()
idxpt = dict()
for i, p in enumerate(pts):
    ptidx[p] = i
    idxpt[i] = p

l = len(pts)
# print(ptidx)
# print(pts)

line_contaier = [dict() for _ in range(4)]

x = [0, 0]
y = [0, 0]
dir = 0
for i, [s, d] in enumerate(op):

    if s == "rotate":
        dir = (dir + d // 45) % 8
    else:
        pidx = ptidx[(tuple(x), tuple(y))]

        x[0] += d * dx[dir][0]
        x[1] += d * dx[dir][1]
        y[0] += d * dy[dir][0]
        y[1] += d * dy[dir][1]

        cidx = ptidx[(tuple(x), tuple(y))]

        if s == "draw":

            line = sorted([idxpt[pidx], idxpt[cidx]], key=cmp_to_key(cmp2))
            lidx = dir % 4

            # print(line)

            if lidx == 0:
                if tuple(y) in line_contaier[lidx].keys():
                    line_contaier[lidx][tuple(y)].append(line)
                else:
                    line_contaier[lidx][tuple(y)] = [line]
            elif lidx == 2:
                if tuple(x) in line_contaier[lidx].keys():
                    line_contaier[lidx][tuple(x)].append(line)
                else:
                    line_contaier[lidx][tuple(x)] = [line]
            elif lidx == 1:
                yy = [y[0] - x[0], y[1] - x[1]]

                if tuple(yy) in line_contaier[lidx].keys():
                    line_contaier[lidx][tuple(yy)].append(line)
                else:
                    line_contaier[lidx][tuple(yy)] = [line]
            elif lidx == 3:
                yy = [y[0] + x[0], y[1] + x[1]]
                if tuple(yy) in line_contaier[lidx].keys():
                    line_contaier[lidx][tuple(yy)].append(line)
                else:
                    line_contaier[lidx][tuple(yy)] = [line]

# for i in range(4):
#     for lkey in line_contaier[i].keys():
#         print(i, lkey)
#         for x, y in line_contaier[i][lkey]:
#             print(x, y)
# print(lkey, line_contaier[i][lkey])

# print(line_contaier)

for lidx in range(4):
    for lkey in line_contaier[lidx].keys():
        pt = line_contaier[lidx][lkey]

        pt.sort(key=cmp_to_key(cmp4))

        # print(lidx, pt)

        npt = [pt[0]]
        lpt = len(pt)

        for i in range(1, lpt):
            if npt[-1][1] == pt[i][0]:
                npt[-1][1] = pt[i][1]
            elif cmp2(npt[-1][1], pt[i][0]) > 0:
                npt[-1][1] = pt[i][1]
            else:
                npt.append(pt[i])

        # print(lidx, npt)

        line_contaier[lidx][lkey] = npt

# for i in range(4):
#     for lkey in line_contaier[i].keys():
#         print(i, lkey)
#         for x, y in line_contaier[i][lkey]:
#             print(x, y)
#         # print(lkey, line_contaier[i][lkey])

# print(line_contaier)

rpts = set()
for lidx in range(4):
    for lkey in line_contaier[lidx].keys():
        for [p1, p2] in line_contaier[lidx][lkey]:

            rpts.add((tuple(p1[0]), tuple(p1[1])))
            rpts.add((tuple(p2[0]), tuple(p2[1])))

rpts = list(rpts)

# print(rpts)))
rpts.sort(key=cmp_to_key(cmp2))
l = len(rpts)

rptidx = dict()
for i in range(l):
    rptidx[tuple(rpts[i])] = i

rpts = [[list(x), list(y)] for [x, y] in rpts]
# print(rpts)

edge = []
gg = [[False for _ in range(l)] for __ in range(l)]

for lidx in range(4):
    for lkey in line_contaier[lidx].keys():
        for [p1, p2] in line_contaier[lidx][lkey]:
            gg[rptidx[p1]][rptidx[p2]] = True
            gg[rptidx[p2]][rptidx[p1]] = True

            edge.append([rptidx[p1], rptidx[p2]])

# print(gg)


def rot(p, k):
    for i in range(k - 1):
        p = rot(p, 1)

    a, b = p[0]
    c, d = p[1]

    nx = [b - d, a // 2 - c // 2]
    ny = [b + d, a // 2 + c // 2]
    return [nx, ny]


ans = [360]
for k in [1, 2, 4]:
    npt = []
    for i in range(l):
        npt.append([rot(rpts[i], k), i])

    npt.sort(key=cmp_to_key(cmp3))
    # print(npt)

    dx = [rpts[0][0][0] - npt[0][0][0][0], rpts[0][0][1] - npt[0][0][0][1]]
    dy = [rpts[0][1][0] - npt[0][0][1][0], rpts[0][1][1] - npt[0][0][1][1]]

    for i in range(l):
        npt[i][0][0][0] += dx[0]
        npt[i][0][0][1] += dx[1]
        npt[i][0][1][0] += dy[0]
        npt[i][0][1][1] += dy[1]

    # print(npt)
    # print(rpts)

    idxinv = [-1 for _ in range(l)]
    for i in range(l):
        idxinv[npt[i][1]] = i

    check = True
    for i in range(l):
        if npt[i][0] != rpts[i]:
            check = False
            break

    # print(k, check)

    for [i, j] in edge:
        if not gg[npt[i][1]][npt[j][1]]:
            check = False
            break
    for [i, j] in edge:
        if not gg[idxinv[i]][idxinv[j]]:
            check = False
            break

    if check:
        ans.append(45 * k)
print(min(ans))
