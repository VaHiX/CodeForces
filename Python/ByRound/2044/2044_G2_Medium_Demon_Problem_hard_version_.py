# Contest 2044, Problem G2: Medium Demon Problem (hard version)
# URL: https://codeforces.com/contest/2044/problem/G2

# https://codeforces.com/contest/2044

import sys

input = lambda: sys.stdin.readline().rstrip()  # faster!


def solve_case():
    n = int(input())
    r = list(map(lambda x: int(x) - 1, input().split()))

    cnt = [0] * n
    for i in range(n):
        cnt[r[i]] += 1

    q = [i for i in range(n) if cnt[i] == 0]
    if not q:
        return 2

    t = [1] * n
    while q:
        qn = []
        for i in q:
            cnt[r[i]] -= 1
            t[r[i]] += t[i]
            if cnt[r[i]] == 0:
                qn.append(r[i])
        q = qn

    ans = max(t[i] for i in range(n) if cnt[i] == 0) + 2
    return ans


ans = []
for _ in range(int(input())):
    ans += [str(solve_case())]
print("\n".join(ans))
