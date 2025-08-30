# Contest 2084, Problem H: Turtle and Nediam 2
# URL: https://codeforces.com/contest/2084/problem/H

import sys


def main():
    import sys

    input = sys.stdin.readline
    mod = 10**9 + 7
    Nmax = 2000005
    a = [0] * Nmax
    nxt = [0] * Nmax
    f = [0] * Nmax
    g = [0] * Nmax
    d = [0] * Nmax

    def calc(m):
        # build nxt array
        stk = []
        for i in range(m, 0, -2):
            ai = a[i] - (i // 2)
            while stk and a[stk[-1]] - (stk[-1] // 2) < ai:
                stk.pop()
            nxt[i] = stk[-1] if stk else 0
            stk.append(i)
        stk.clear()
        for i in range(m - 1, 0, -2):
            ai = a[i] - (i // 2)
            while stk and a[stk[-1]] - (stk[-1] // 2) < ai:
                stk.pop()
            nxt[i] = stk[-1] if stk else 0
            stk.append(i)

        # dp
        for i in range(1, m):
            f[i] = g[i] = d[i] = 0
        f[1] = a[1]
        for i in range(3, m, 2):
            f[i] = 1

        ans = 0
        for i in range(1, m):
            if i >= 3:
                d_i = d[i] + d[i - 2]
                d[i] = d_i if d_i < mod else d_i - mod
            fi = f[i] + d[i]
            if fi >= mod:
                fi -= mod
            f[i] = fi

            gi = g[i]
            ni = nxt[i]

            # regular transitions
            g[i + 1] = (g[i + 1] + fi) % mod
            f[i + 1] = (f[i + 1] + fi * a[i + 1]) % mod
            d[i + 2] = (d[i + 2] + gi) % mod

            # jump transition
            if ni:
                g[ni] = (g[ni] + gi) % mod
                tmp = a[ni] - a[i] - ((ni - i) // 2) + 1
                f[ni] = (f[ni] + gi * tmp) % mod
                d[ni] = (d[ni] - gi) % mod

            if (m - i) & 1:
                ans += fi
                if ans >= mod:
                    ans -= mod

        return ans * a[m] % mod

    T = int(input())
    for _ in range(T):
        n = int(input())
        s = input().strip()

        # build run-length encoding
        m = 0
        prev = s[0]
        cnt = 1
        for c in s[1:]:
            if c == prev:
                cnt += 1
            else:
                m += 1
                a[m] = cnt
                cnt = 1
                prev = c
        m += 1
        a[m] = cnt

        if m == 1:
            print(n - 1)
            continue
        if m == 2:
            print(a[1] * a[2] % mod)
            continue

        total = calc(m)
        # second scenario: starting char flipped
        m -= 1
        for i in range(1, m + 1):
            a[i] = a[i + 1]
        a[1] = 1
        total = (total + calc(m)) % mod

        print(total)


if __name__ == "__main__":
    main()
