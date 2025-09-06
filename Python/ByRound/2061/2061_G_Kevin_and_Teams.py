# Contest 2061, Problem G: Kevin and Teams
# URL: https://codeforces.com/contest/2061/problem/G

import sys

input = lambda: sys.stdin.readline().rstrip()
printerr = (
    lambda *args, **kwargs: print(
        "\u001b[31m", *args, "\u001b[0m", file=sys.stderr, **kwargs
    )
    or len(args) == 1
    and args[0]
    or args
)


def main():
    n = int(input())
    k = (n + 1) // 3
    print(k, flush=True)
    t = []
    s = []
    c = 0
    for i in range(1, n + 1):
        if not s:
            s.append(i)
        else:
            print("?", s[-1], i, flush=True)
            x = int(input())
            assert x != -1
            if len(s) < 2 or x == c:
                s.append(i)
                c = x
            else:
                m = s.pop()
                v = s.pop()
                t.append((v, i, m) if x else (i, v, m))
    a = s[: min(len(s) // 2 * 2, k * 2)]
    a += [x for p in t[: (k * 2 - len(a)) // 2] for x in (p[c], p[2])]
    print("!", *a, flush=True)


tcs = int(input())
for tc in range(tcs):
    main()
