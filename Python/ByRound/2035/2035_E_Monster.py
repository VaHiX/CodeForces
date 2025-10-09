# Contest 2035, Problem E: Monster
# URL: https://codeforces.com/contest/2035/problem/E

from sys import stdin, stdout

t = int(stdin.readline())

for _ in range(t):
    x, y, z, k = [int(b) for b in stdin.readline().split()]

    lowest = 10**18

    q = 0
    while True:
        h = z - (q * (q + 1) * k) // 2

        if h <= 0:
            cost = q * y + q * k * x
            lowest = min(lowest, cost)
            break

        if q > 0:
            r = 0
        else:
            r = 1
        while True:
            denom = q * k + r
            cost = q * y + ((h - 1) // denom + 1) * y + denom * x
            lowest = min(lowest, cost)

            if denom * denom >= h or r == k:
                break

            r += 1

        if r < k:
            for l in range(h // (q * k + r), 0, -1):
                r = (h - l * q * k - 1) // l + 1
                if r > k:
                    break

                cost = q * y + ((h - 1) // (q * k + r) + 1) * y + (q * k + r) * x

                lowest = min(lowest, cost)

        q += 1

    stdout.write(str(lowest) + "\n")
