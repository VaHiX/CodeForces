# Contest 2064, Problem F: We Be Summing
# URL: https://codeforces.com/contest/2064/problem/F

from sys import stdin

input = lambda: stdin.readline().rstrip()


def solve():
    n, k = map(int, input().split())
    a = list(map(int, input().split()))

    put = [[] for _ in range(n)]
    delete = [[] for _ in range(n)]
    cmn = [0] * (2 * n)
    cmx = [0] * (2 * n)

    st = [n]
    for i in range(n - 1, -1, -1):
        while len(st) > 1 and a[st[-1]] < a[i]:
            put[i].append((k - a[st[-1]], st[-2] - st[-1]))
            st.pop()
        delete[i].append((k - a[i], st[-1] - i))
        st.append(i)

    for i in range(len(st) - 1):
        cmx[k - a[st[i + 1]]] += st[i] - st[i + 1]
    st = [-1]
    ans = 0

    for i in range(n):
        while len(st) > 1 and a[st[-1]] > a[i]:
            v = a[st[-1]]
            cmn[v] -= st[-1] - st[-2]
            st.pop()
        for x, y in delete[i]:
            cmx[x] -= y
        for x, y in put[i]:
            cmx[x] += y
            ans += y * cmn[x]
        cmn[a[i]] += i - st[-1]
        st.append(i)
        ans += (st[-1] - st[-2]) * cmx[a[i]]

    return ans


for _ in range(int(input())):
    print(solve())
