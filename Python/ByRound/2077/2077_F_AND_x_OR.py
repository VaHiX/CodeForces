# Contest 2077, Problem F: AND x OR
# URL: https://codeforces.com/contest/2077/problem/F

import sys

input = sys.stdin.readline

t = int(input())
for _ in range(t):
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))

    out = 0
    for i in range(n):
        out += abs(a[i] - b[i])

    z = 1
    bt = 0
    while m >= z:
        z *= 2
        bt += 1

    b.sort()
    for i in range(n - 1):
        out = min(out, b[i + 1] - b[i])

    curr = [m] * z
    curr3 = [z] * z
    for v in b:
        curr[v] = 0
        curr3[v] = v

    for i in range(1, z):
        curr[i] = min(curr[i], curr[i - 1] + 1)

    curr2 = [m] * z

    for k in range(bt):
        mask = 1 << k
        for i in range(z):
            if mask & i == 0:
                j = i | mask
                curr2[j] = min(curr2[j], curr[i], curr2[i])
                curr3[j] = min(curr3[j], curr3[i])

    for v in b:
        out = min(out, curr2[v])

    st = []

    for i in range(z)[::-1]:
        if curr3[i] == z:
            continue

        assert curr3[i] <= i

        while st and curr3[st[-1]] >= i:
            st.pop()

        if st and curr3[i] == i:
            out = min(out, st[-1] - i)

        while st and curr3[st[-1]] >= curr3[i]:
            st.pop()

        st.append(i)

    """
    for v in b:
        ind = xx[v]
        if curr3[ind] < v:
            out = min(out, ind - v)"""

    print(out)

"""
1
3 30
1 1 1
4 9 24
"""
