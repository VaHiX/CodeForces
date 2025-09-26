# Contest 2031, Problem E: Penchick and Chloe's Trees
# URL: https://codeforces.com/contest/2031/problem/E

for _ in range(int(input())):
    n = int(input())
    par = [0] + [int(t) - 1 for t in input().split()]
    child = [[] for _ in range(n)]
    for i in range(1, n):
        child[par[i]].append(i)

    depth = [0] * n
    for i in range(1, n):
        depth[i] = depth[par[i]] + 1

    ans = [0] * n
    for i in range(n - 1, -1, -1):
        if not child[i]:
            ans[i] = 0
            continue
        if len(child[i]) == 1:
            ans[i] = 1 + ans[child[i][0]]
            continue

        bitz = sorted(ans[j] for j in child[i])
        cur = 0
        v = 0
        for t in bitz:
            if v < t:
                d = t - v
                cur = (cur - 1) >> d
                cur += 1
            cur += 1
            v = t
        ans[i] = v + (cur - 1).bit_length()

    print(ans[0])
