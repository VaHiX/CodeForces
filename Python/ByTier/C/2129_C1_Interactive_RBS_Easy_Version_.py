# Contest 2129, Problem C1: Interactive RBS (Easy Version)
# URL: https://codeforces.com/contest/2129/problem/C1


import sys

for t in range(int(input())):
    n = int(input())
    l, r = 2, n
    got = False
    while l <= r:
        m = (l + r) // 2
        print("?", m, *range(1, m + 1))
        sys.stdout.flush()
        res = int(input())
        if res > 0:
            p = m
            r = m - 1
            got = True
        else:
            l = m + 1

    if got:
        ro, rc = p - 1, p
    else:
        ro, rc = n, 1

    mp = {1: [")", ")"], 2: [")", "("], 3: ["(", ")"], 4: ["(", "("]}

    ans = []
    for i in range(1, n, 2):
        print("?", 7, i, rc, ro, rc, rc, i + 1, rc)
        sys.stdout.flush()
        v = int(input())
        ans += mp[v]

    if n % 2 == 1:
        print("?", 2, ro, n)
        sys.stdout.flush()
        last = int(input())
        ans.append(")" if last == 1 else "(")

    print("!", *ans, sep="")
    sys.stdout.flush()
