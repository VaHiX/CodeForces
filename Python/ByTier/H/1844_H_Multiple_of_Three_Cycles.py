# Problem: CF 1844 H - Multiple of Three Cycles
# https://codeforces.com/contest/1844/problem/H

"""
Purpose: 
    This code solves the problem of counting the number of valid ways to fill a permutation 
    such that all cycle lengths are multiples of 3, after a series of updates to the permutation.
    
    It uses Disjoint Set Union (DSU) to manage cycles and dynamic programming with precomputed 
    factorials and inverse factorials to calculate combinations efficiently.

Algorithms:
    - Disjoint Set Union (DSU) for cycle management
    - Preprocessing factorials and inverse factorials for combinatorics
    - Mathematical recurrence relations for calculating answers
    
Time Complexity: O(n log n + n)
Space Complexity: O(n)

The code maintains the counts of cycles of lengths mod 3 and updates them based on the DSU operations.
For each state, it calculates the number of valid completions using precomputed factorials.
"""

import sys

MOD = 998244353


def main():
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    it = iter(data)
    n = int(next(it))

    parent = list(range(n))
    siz = [1] * n

    def dsu_find(a):
        """Find root of element with path compression."""
        while parent[a] != a:
            parent[a] = parent[parent[a]]
            a = parent[a]
        return a

    # num[i] represents number of cycles with size % 3 == i
    num = [0, n, 0]

    queries = [None] * 600000
    bad = 10**9

    for i in range(n):
        x_val = int(next(it)) - 1
        y_val = int(next(it)) - 1
        rx = dsu_find(x_val)
        ry = dsu_find(y_val)
        if rx != ry:
            # Update cycle size counts
            num[siz[rx] % 3] -= 1
            num[siz[ry] % 3] -= 1
            siz[ry] += siz[rx]
            parent[rx] = ry
            num[siz[ry] % 3] += 1
        else:
            # If already in same cycle, check if cycle became invalid
            if siz[rx] % 3 == 0:
                num[0] -= 1
            elif bad == 10**9:
                bad = i

        queries[i] = (num[0], num[1], num[2])

    m = n

    # Extend query list with additional states
    while num[1] + num[2] > 0:
        if num[1] > 0:
            a_val = 1
        else:
            a_val = 2
        num[a_val] -= 1
        if num[1] > 0:
            b_val = 1
        else:
            b_val = 2
        num[b_val] -= 1
        num[(a_val + b_val) % 3] += 1
        queries[m] = (num[0], num[1], num[2])
        m += 1

    # Precompute factorials and inverse factorials
    N = n
    fact = [1] * (N + 1)
    for i in range(1, N + 1):
        fact[i] = fact[i - 1] * i % MOD
    invfact = [1] * (N + 1)
    invfact[N] = pow(fact[N], MOD - 2, MOD)
    for i in range(N - 1, -1, -1):
        invfact[i] = invfact[i + 1] * (i + 1) % MOD
    invn = [0] * (N + 1)
    for i in range(1, N + 1):
        invn[i] = invfact[i] * fact[i - 1] % MOD

    ans = [0] * m

    x = 1
    y = 1
    u = 1
    v = 8

    # Functions for calculating recurrence
    def f():
        nonlocal x, y, u, v
        temp = ((y + 1) * (x + y + 1)) % MOD
        temp2 = (temp * u) % MOD
        diff = (v - temp2) % MOD
        nu = (diff * invn[x]) % MOD
        nv = ((x * (x + y + 2)) % MOD * nu + (y + 2) * v) % MOD
        x = x - 1
        y = y + 2
        u = nu
        v = nv

    def g():
        nonlocal x, y, u, v
        temp = ((x + 1) * (x + y + 1)) % MOD
        temp2 = (temp * u) % MOD
        nu = ((v - temp2) % MOD * invn[y]) % MOD
        nv = ((y * (x + y + 2)) % MOD * nu + (x + 2) * v) % MOD
        x = x + 2
        y = y - 1
        u = nu
        v = nv

    for i in range(m - 1, -1, -1):
        num0, a_val, b_val = queries[i]
        c = num0
        if a_val == 0 and b_val == 0:
            ans_val = 1
        elif a_val == x and b_val == y:
            ans_val = u
        elif a_val == x - 1 and b_val == y + 2:
            f()
            ans_val = u
        elif a_val == x + 2 and b_val == y - 1:
            g()
            ans_val = u
        elif a_val == x + 1 and b_val == y + 1:
            if x > 0:
                f()
                g()
            else:
                g()
                f()
            ans_val = u
        else:
            raise Exception(
                "Unexpected state at query index %d: query=(%d, %d) vs current (x=%d, y=%d)"
                % (i, a_val, b_val, x, y)
            )
        tot = a_val + b_val + c
        ans_val = ans_val * fact[tot] % MOD
        ans_val = ans_val * invfact[a_val + b_val] % MOD
        ans[i] = ans_val

    output_lines = []
    for i in range(n):
        if i >= bad:
            output_lines.append("0")
        else:
            output_lines.append(str(ans[i]))
    sys.stdout.write("\n".join(output_lines))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/