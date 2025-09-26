# Contest 2123, Problem F: Minimize Fixed Points
# URL: https://codeforces.com/contest/2123/problem/F

import sys

input = sys.stdin.readline
print = sys.stdout.write


def primes(n):
    a = [0] * (n + 1)
    for i in range(2, n + 1):
        if a[i] == 0:
            for j in range(i, n + 1, i):
                a[j] = i
    return a


d = primes(10**5)
d[1] = 1
t = int(input())
for _ in range(t):
    n = int(input())
    ans = [i for i in range(n + 1)]
    for i in range(2, n + 1):
        ans[i], ans[d[i]] = ans[d[i]], ans[i]
    print(f"{' '.join(map(str, ans[1:]))}\n")
