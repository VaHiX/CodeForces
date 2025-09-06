# Contest 1741, Problem A: Compare T-Shirt Sizes
# URL: https://codeforces.com/contest/1741/problem/A

for s in [*open(0)][1:]:
    x, y = ("ML".find(x[-1]) * len(x) for x in s.split())
    print("=<>"[(x < y) - (y < x)])
