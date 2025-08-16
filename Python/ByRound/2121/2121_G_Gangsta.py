# Contest 2121, Problem G: Gangsta
# URL: https://codeforces.com/contest/2121/problem/G

# https://codeforces.com/contest/2121

import sys

input = lambda: sys.stdin.readline().rstrip()  # faster!


def solve_case():
    n = int(input())
    s = input()

    pref = [0] * (n + 1)
    for i in range(n):
        pref[i + 1] = pref[i] + (-1 if s[i] == "0" else +1)
    pref.sort()

    ans = sum((pref[i + 1] - pref[i] + 1) * (i + 1) * (n - i) for i in range(n)) // 2
    return ans


ans = []
for _ in range(int(input())):
    ans.append(str(solve_case()))
print("\n".join(ans))
