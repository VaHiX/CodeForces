# Contest 2027, Problem D2: The Endspeaker (Hard Version)
# URL: https://codeforces.com/contest/2027/problem/D2

import sys
import heapq
from collections import *

input = iter(sys.stdin.read().splitlines()).__next__

P = 1000000007


def main():
    T = int(input())

    for _ in range(T):
        n, m = map(int, input().split())
        a = [int(i) for i in input().split()]
        b = [int(i) for i in input().split()]
        a.reverse()
        b.reverse()
        a = [0] + a
        for i in range(1, n + 1):
            a[i] += a[i - 1]
        dp = [1000000] * (n + 1)
        dp[0] = 0

        cnt = [0] * (n + 1)
        cnt[0] = 1
        for k in range(m):
            l = 0
            c = Counter()
            c[0] = 1
            for r in range(1, n + 1):
                while a[r] - a[l] > b[k]:
                    c[dp[l]] = (c[dp[l]] - cnt[l] + P) % P
                    l += 1
                if l == r:
                    break
                if dp[l] + k < dp[r]:
                    dp[r] = dp[l] + k
                    cnt[r] = c[dp[l]]
                elif dp[l] + k == dp[r]:
                    cnt[r] = (cnt[r] + c[dp[l]]) % P
                c[dp[r]] = (c[dp[r]] + cnt[r]) % P

        if dp[n] == 1000000:
            print(-1)
        else:
            print(dp[n], cnt[n])


if __name__ == "__main__":
    main()
