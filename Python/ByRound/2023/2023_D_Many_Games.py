# Contest 2023, Problem D: Many Games
# URL: https://codeforces.com/contest/2023/problem/D

import sys
from collections import defaultdict


def solve():
    n = int(sys.stdin.readline())
    games = []
    sum_p100 = 0
    for _ in range(n):
        p, w = map(int, sys.stdin.readline().split())
        if p == 100:
            sum_p100 += w
        else:
            games.append((p, w))
    
    C = 200000 * 100 // 99  # 202020

    if sum_p100 > C:
        print("{0:.8f}".format(sum_p100))
        return
    
    groups = defaultdict(list)
    for p, w in games:
        groups[p].append(w)
    
    processed = []
    for p in groups:
        lst = sorted(groups[p], reverse=True)
        denominator = 100 - p
        K = 100 // denominator
        take = min(K, len(lst))
        processed.extend((p, w) for w in lst[:take])
    
    C_DP = C
    dp = [0.0] * (C_DP + 1)
    dp[0] = 1.0
    for p, w in processed:
        q = p / 100.0
        for s in range(C_DP, w - 1, -1):
            if dp[s - w] * q > dp[s]:
                dp[s] = dp[s - w] * q
    
    max_expected = 0.0
    for s in range(C_DP + 1):
        if dp[s] == 0.0:
            continue
        current = (sum_p100 + s) * dp[s]
        if current > max_expected:
            max_expected = current
    
    print("{0:.8f}".format(max_expected))


if __name__ == "__main__":
    solve()
