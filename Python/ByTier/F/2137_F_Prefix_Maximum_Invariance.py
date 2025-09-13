# Contest 2137, Problem F: Prefix Maximum Invariance
# URL: https://codeforces.com/contest/2137/problem/F

import sys

input = lambda: sys.stdin.readline().rstrip()


def solve646():
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    s = []
    res = 0
    for i in range(n):
        while s and a[i] > a[s[-1]]:
            s.pop()
        t = 0
        if a[i] ^ b[i]:
            # print(s, i, b[i])
            if s and a[s[0]] >= b[i]:
                # bs
                l, r = 0, len(s)
                while l + 1 < r:
                    m = l + r >> 1
                    if a[s[m]] >= b[i]:
                        l = m
                    else:
                        r = m
                # print(s, b[i], l, r)
                t = (n - i) * (s[l] + 1)
            # if s and a[s[-1]] >= b[i]:
            #     t = (n-i) * (s[-1]+1)
        else:
            t = (i + 1) * (n - i)
        # print(i, t)
        res += t
        s.append(i)
    return res


res_test = []
for _ in range(int(input())):
    res_test.append(solve646())
sys.stdout.write("\n".join(map(str, res_test)))  # output all test
