# Contest 2082, Problem C: Math Division
# URL: https://codeforces.com/contest/2082/problem/C

import sys

input = sys.stdin.readline


def main():
    MOD = 10**9 + 7
    BASE = 500000004
    MAX_N = 10**5

    power = [1] * MAX_N
    for i in range(1, MAX_N):
        power[i] = (power[i - 1] * BASE) % MOD

    t = int(input().strip())
    for _ in range(t):
        n = int(input().strip())
        m = int(input().strip(), 2)

        print((n - 2 + m * power[n - 1]) % MOD)


if __name__ == "__main__":
    main()
