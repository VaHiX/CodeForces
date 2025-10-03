# Contest 2034, Problem D: Darius' Wisdom
# URL: https://codeforces.com/contest/2034/problem/D

#!/usr/local/bin/python3

import sys

input = sys.stdin.readline


def ri():
    return int(input())


def rl(v_type=int):
    return list(map(v_type, input().split()))


def rs():
    return input().rstrip()


def out(x, sep=" "):
    return sep.join(map(str, x))


def process(a, n, path, phase):
    l, r = 1, n
    z = 1 if phase else n

    while l < r:
        if phase:
            while l < r and a[l] != 2:
                l += 1
            while l < r and a[r] == 2:
                r -= 1
        else:
            while l < r and a[l] == 0:
                l += 1
            while l < r and a[r] != 0:
                r -= 1

        if l < r:
            if a[r] == 1 if phase else a[l] == 1:
                a[l], a[r] = a[r], a[l]
                path.append((l, r))
            else:
                while a[z] != 1 if phase else a[z] != 1:
                    z += 1 if phase else -1
                a[z], a[r] = a[r], a[z]
                a[r], a[l] = a[l], a[r]
                path.append((z, r))
                path.append((r, l))
                z = min(z, l) if phase else max(z, r)


def solve_case():
    n = ri()
    a = [0] + rl()

    path = []

    # Phase 1: Move 2s to the right
    process(a, n, path, True)

    # Phase 2: Move 0s to the left
    process(a, n, path, False)

    path = [len(path)] + [out(x) for x in path]
    return out(path, "\n")


if __name__ == "__main__":
    T = int(input())
    ret = [solve_case() for ti in range(1, T + 1)]
    print(out(ret, "\n"))
