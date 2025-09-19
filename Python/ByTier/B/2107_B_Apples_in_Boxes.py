# Contest 2107, Problem B: Apples in Boxes
# URL: https://codeforces.com/contest/2107/problem/B

I = lambda: (*map(int, input().split()),)


def s():
    n, k = I()
    a = I()
    R = (m := max(a)) - min(a) - (not (a.count(m) - 1))
    return 0 if R > k else sum(a) & 1


print("\n".join("Tom" if s() else "Jerry" for ti in int(input()) * (1,)))
