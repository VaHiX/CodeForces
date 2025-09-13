# Contest 2050, Problem F: Maximum modulo equality
# URL: https://codeforces.com/contest/2050/problem/F


class SparseTable_quick:
    def __init__(self, lst, fun):
        self.fun = fun  # min max and_ or_ math.lcm math.gcd
        self.st = st = [list(lst)]
        i, N = 1, len(st[0])
        while 2 * i <= N + 1:
            qz = st[-1]
            st.append([fun(qz[j], qz[j + i]) for j in range(N - 2 * i + 1)])
            i <<= 1
        return

    def query(self, left, right):
        if left >= right:
            return 0
        lg = (right - left).bit_length() - 1
        return self.fun(self.st[lg][left], self.st[lg][right - (1 << lg)])


from sys import stdin

input = lambda: stdin.buffer.readline().rstrip()
from math import gcd

for _ in range(int(input())):
    n, q = map(int, input().split())
    a = list(map(int, input().split()))
    l = [abs(a[i] - a[i + 1]) for i in range(n - 1)]
    st = SparseTable_quick(l, gcd)
    ans = [None] * q
    for i in range(q):
        l, r = map(int, input().split())
        ans[i] = str(st.query(l - 1, r - 1))
    print(" ".join(ans))
