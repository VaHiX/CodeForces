# Contest 630, Problem O: Arrow
# URL: https://codeforces.com/contest/630/problem/O

px, py, vx, vy, a, b, c, d = map(int, input().split())
a = a / 2
xl = vx / (vx**2 + vy**2) ** 0.5
yl = vy / (vx**2 + vy**2) ** 0.5


def sus(aa, bb):
    print(str(px + aa) + " " + str(py + bb))


sus(xl * b, yl * b)
sus(-yl * a, xl * a)
sus(-yl * c / 2, xl * c / 2)
sus(-yl * c / 2 - xl * d, xl * c / 2 - yl * d)
sus(yl * c / 2 - xl * d, -xl * c / 2 - yl * d)
sus(yl * c / 2, -xl * c / 2)
sus(yl * a, -xl * a)
