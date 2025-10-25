# Contest 2006, Problem C: Eri and Expanded Sets
# URL: https://codeforces.com/contest/2006/problem/C

from math import gcd

class RangeQuery:
    def __init__(self, data, func=min):
        self.func = func
        self._data = _data = [list(data)]
        i, n = 1, len(_data[0])
        while 2 * i <= n:
            prev = _data[-1]
            _data.append([func(prev[j], prev[j + i]) for j in range(n - 2 * i + 1)])
            i <<= 1

    def query(self, start, stop):
        """func of data[start, stop)"""
        depth = (stop - start).bit_length() - 1
        return self.func(self._data[depth][start], self._data[depth][stop - (1 << depth)])


def solve():
    n = int(input())
    arr = list(map(int, input().split()))
    ar = []
    for i in range(1, n):
        a = abs(arr[i]-arr[i-1])
        while a and a&1 == 0:
            a >>= 1
        ar.append(a)
    rmq = RangeQuery(ar, gcd)
    i = 0
    ans = 0
    while i < n:
        j = i
        while j < n and arr[j] == arr[i]:
            j += 1
        ans += (j-i+1)*(j-i)//2
        if j == n:
            break
        le = j
        ri = n-1
        if rmq.query(j-1, ri) != 1:
            i = j
            continue
        while le < ri:
            mid = (le+ri)//2
            if rmq.query(j-1, mid) == 1:
                ri = mid
            else:
                le = mid+1
        ans += (j-i)*(n-le)
        i = j
    return ans


import sys
input = lambda: sys.stdin.readline().rstrip()
t = int(input())
for i in range(t):
    print(solve())
