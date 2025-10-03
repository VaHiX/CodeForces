# Problem: CF 2084 H - Turtle and Nediam 2
# https://codeforces.com/contest/2084/problem/H

"""
Problem: Turtle and Nediam 2
Task: Count the number of different binary sequences that can be obtained after performing operations on a binary string.

Algorithms/Techniques:
- Segment tree / stack-based approach for maintaining next greater element information
- Dynamic Programming with memoization and prefix sums
- String compression to handle run-length encoding of consecutive characters

Time Complexity: O(n) where n is the length of input string
Space Complexity: O(n) for arrays storing precomputed values and stacks

The algorithm uses a combination of:
1. Run-length encoding of input binary string
2. Stack-based computation of next greater elements
3. Dynamic Programming with state tracking for different configurations
4. Modular arithmetic to prevent overflow
"""

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
        stk = []
        # Process from right to left for odd indices to build stack of next greater elements
        for i in range(m, 0, -2):
            ai = a[i] - (i // 2)
            while stk and a[stk[-1]] - (stk[-1] // 2) < ai:
                stk.pop()
            nxt[i] = stk[-1] if stk else 0
            stk.append(i)
        stk.clear()
        # Process from right to left for even indices
        for i in range(m - 1, 0, -2):
            ai = a[i] - (i // 2)
            while stk and a[stk[-1]] - (stk[-1] // 2) < ai:
                stk.pop()
            nxt[i] = stk[-1] if stk else 0
            stk.append(i)
        # Initialize DP arrays
        for i in range(1, m):
            f[i] = g[i] = d[i] = 0
        f[1] = a[1]
        # Base case handling for DP
        for i in range(3, m, 2):
            f[i] = 1
        ans = 0
        # Dynamic Programming transition
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
            # Update following indices with DP value
            g[i + 1] = (g[i + 1] + fi) % mod
            f[i + 1] = (f[i + 1] + fi * a[i + 1]) % mod
            d[i + 2] = (d[i + 2] + gi) % mod
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
        m = 0
        prev = s[0]
        cnt = 1
        # Compress consecutive characters into counts (run-length encoding)
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
        # Special handling for single character cases
        if m == 1:
            print(n - 1)
            continue
        if m == 2:
            print(a[1] * a[2] % mod)
            continue
        total = calc(m)
        m -= 1
        # Shift array elements to simulate removal of one element in next iteration
        for i in range(1, m + 1):
            a[i] = a[i + 1]
        a[1] = 1
        total = (total + calc(m)) % mod
        print(total)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/