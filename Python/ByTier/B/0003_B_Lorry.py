# Contest 3, Problem B: Lorry
# URL: https://codeforces.com/contest/3/problem/B

from heapq import nlargest
from itertools import accumulate, chain
import sys

n, v = map(int, sys.stdin.readline().split())
a1, a2 = [], []
i1, i2 = [], []
for i in range(n):
    t, p = map(int, sys.stdin.readline().split())
    if t == 1:
        a1.append(p)
        i1.append(i)
    else:
        a2.append(p)
        i2.append(i)
acc1 = list(accumulate(sorted(a1, reverse=True), initial=0))
acc2 = list(accumulate(sorted(a2, reverse=True), initial=0))
best = (0, 0, 0)
for n2 in range(min(v // 2, len(a2)) + 1):
    n1 = min(v - 2 * n2, len(a1))
    best = max(best, (acc1[n1] + acc2[n2], n1, n2))
ans, n1, n2 = best
sys.stdout.write(str(ans) + "\n")
ii1 = sorted(range(len(a1)), key=a1.__getitem__)[len(a1) - n1 :]
ii2 = sorted(range(len(a2)), key=a2.__getitem__)[len(a2) - n2 :]
sys.stdout.write(" ".join(str(i1[i] + 1) for i in ii1))
sys.stdout.write(" ")
sys.stdout.write(" ".join(str(i2[i] + 1) for i in ii2))
sys.stdout.write("\n")
