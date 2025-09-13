# Contest 2138, Problem B: Antiamuny Wants to Learn Swap
# URL: https://codeforces.com/contest/2138/problem/B


def solve():
    n, q = map(int, input().split())
    arr = list(map(int, input().split()))
    ans = []
    le = [-1] * n
    st = []
    for i, a in enumerate(arr):
        while st and arr[st[-1]] <= a:
            st.pop()
        if st:
            le[i] = st[-1]
        st.append(i)
    ri = [n] * n
    st = []
    for i in range(n - 1, -1, -1):
        a = arr[i]
        while st and arr[st[-1]] >= a:
            st.pop()
        if st:
            ri[i] = st[-1]
        st.append(i)
    seg = [n] * n
    for i in range(n):
        if le[i] >= 0:
            seg[le[i]] = min(seg[le[i]], ri[i])
    res = [n] * n
    m = n
    for i in range(n - 1, -1, -1):
        m = min(m, seg[i])
        res[i] = m
    for i in range(q):
        l, r = map(int, input().split())
        l -= 1
        r -= 1
        if r >= res[l]:
            ans.append("NO")
        else:
            ans.append("YES")
    print("\n".join(ans))


import sys

input = lambda: sys.stdin.readline().rstrip()
t = int(input())
for i in range(t):
    solve()
