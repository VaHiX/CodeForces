# Contest 890, Problem A: ACM ICPC
# URL: https://codeforces.com/contest/890/problem/A

import itertools

a = list(map(int, input().split()))
s = sum(a)
ans = "NO"
for i in itertools.combinations(a, 3):
    if sum(i) * 2 == s:
        ans = "YES"
        break
print(ans)
