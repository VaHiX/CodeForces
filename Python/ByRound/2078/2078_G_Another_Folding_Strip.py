# Contest 2078, Problem G: Another Folding Strip
# URL: https://codeforces.com/contest/2078/problem/G

import sys
import threading


def solve():
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    MOD = 998244353
    t = int(data[0])
    idx = 1
    out_lines = []
    for _ in range(t):
        n = int(data[idx])
        idx += 1
        a = list(map(int, data[idx : idx + n]))
        idx += n

        m = n + 1
        # Build prefix array c with alternating signs:
        # c[i] = c[i-1] + (-1)^i * a[i] (1-indexed)
        c = [0] * m
        for i in range(1, m):
            if i & 1:
                c[i] = c[i - 1] - a[i - 1]
            else:
                c[i] = c[i - 1] + a[i - 1]

        # Prepare stacks and arrays for contributions.
        # We compute Smax (sum of maximum contributions) and Smin (sum of minimum contributions),
        # then answer = Smax - Smin.
        prev_g = [-1] * m
        stack = []
        for i in range(m):
            ci = c[i]
            while stack and c[stack[-1]] <= ci:
                stack.pop()
            prev_g[i] = stack[-1] if stack else -1
            stack.append(i)
        next_ge = [m] * m
        stack.clear()
        for i in range(m - 1, -1, -1):
            ci = c[i]
            while stack and c[stack[-1]] < ci:
                stack.pop()
            next_ge[i] = stack[-1] if stack else m
            stack.append(i)
        Smax = 0
        for i in range(m):
            left = i - prev_g[i]
            right = next_ge[i] - i
            val = c[i] % MOD
            Smax = (Smax + val * left % MOD * right) % MOD

        prev_s = [-1] * m
        stack.clear()
        for i in range(m):
            ci = c[i]
            while stack and c[stack[-1]] >= ci:
                stack.pop()
            prev_s[i] = stack[-1] if stack else -1
            stack.append(i)
        next_se = [m] * m
        stack.clear()
        for i in range(m - 1, -1, -1):
            ci = c[i]
            while stack and c[stack[-1]] > ci:
                stack.pop()
            next_se[i] = stack[-1] if stack else m
            stack.append(i)
        Smin = 0
        for i in range(m):
            left = i - prev_s[i]
            right = next_se[i] - i
            val = c[i] % MOD
            Smin = (Smin + val * left % MOD * right) % MOD

        ans = (Smax - Smin) % MOD
        out_lines.append(str(ans))
    sys.stdout.write("\n".join(out_lines))


def main():
    solve()


if __name__ == "__main__":
    main()
