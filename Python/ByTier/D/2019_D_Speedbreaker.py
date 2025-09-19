# Contest 2019, Problem D: Speedbreaker
# URL: https://codeforces.com/contest/2019/problem/D

import sys
def rs(): return sys.stdin.readline().rstrip()
def ri(): return int(sys.stdin.readline())
def ria(): return list(map(int, sys.stdin.readline().split()))
def ria1(): return list(map(lambda x: int(x)-1, sys.stdin.readline().split()))
def ria2d(n): return [list(map(int, sys.stdin.readline().split())) for _ in range(n)]
def rg(directed=False):
    n, m = ria()
    g = [[] for _ in range(n)]
    for _ in range(m):
        u, v = ria1()
        g[u].append(v)
        if not directed:
            g[v].append(u)
    return n, m, g
def ws(s): sys.stdout.write(s); sys.stdout.write('\n')
def wi(n): sys.stdout.write(str(n)); sys.stdout.write('\n')
def wia(a, sep=' '): sys.stdout.write(sep.join([str(x) for x in a])); sys.stdout.write('\n')
def wia1(a, sep=' '): sys.stdout.write(sep.join([str(x+1) for x in a])); sys.stdout.write('\n')


def solve(n, a):
    l = 0
    r = n - 1
    for i in range(n, 0, -1):
        while l < r and a[l] > i:
            l += 1
        while l < r and a[r] > i:
            r -= 1
        if r - l >= i:
            return 0

    # intersect segments [i-a[i]+1, i+a[i]-1]
    l = 0
    r = n - 1
    for i, num in enumerate(a):
        l = max(l, i - num + 1)
        r = min(r, i + num - 1)
    return r - l + 1


def main():
    for _ in range(ri()):
        n = ri()
        a = ria()
        wi(solve(n, a))


if __name__ == '__main__':
    main()
