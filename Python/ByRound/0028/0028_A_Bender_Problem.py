# Contest 28, Problem A: Bender Problem
# URL: https://codeforces.com/contest/28/problem/A

import sys


def calc(arr, begin):
    cnt = {}
    ans = [-1] * (n + 1)
    for i in range(1, n + 1, 2):
        l = abs(arr[i] - arr[i - 1]) + abs(arr[i] - arr[i + 1])
        cnt[l] = cnt.get(l, 0) + 1
        ans[i] = l
        if cnt[l] > len(rmap.get(l, [])):
            return False
    print("YES")
    print(
        " ".join(
            ["-1" if x == -1 else str(rmap[x].pop()) for x in ans[begin : begin + n]]
        )
    )
    return True


input = sys.stdin.buffer.readline
n, m = map(int, input().split())
ps = [sum(map(int, input().split())) for _ in range(n)]
rmap = {}
for i, l in enumerate(map(int, input().split()), start=1):
    if l in rmap:
        rmap[l].append(i)
    else:
        rmap[l] = [i]
if calc([ps[-1]] + ps, 1) == False and calc(ps + [ps[0]], 0) == False:
    print("NO")
