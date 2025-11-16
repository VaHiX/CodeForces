# Problem: CF 1840 G1 - In Search of Truth (Easy Version)
# https://codeforces.com/contest/1840/problem/G1

"""
Algorithm: 
- The problem is to determine the number of sectors `n` in a circular arrangement.
- We start at some sector and can move the arrow clockwise or counterclockwise.
- The key idea is to detect the cycle length (which is `n`) by observing when we return to a previously visited sector.

Approach:
1. First, we move the arrow in steps of 1000 sectors to quickly get an approximate range. By tracking positions, we can find a pattern.
2. Then we incrementally move by 1 sector and observe when we return to a known position to deduce the exact cycle length `n`.

Time Complexity: O(log n) due to binary search-like behavior in detecting cycle length.
Space Complexity: O(n) for storing visited positions in the dictionary `vis`.

Techniques Used:
- Modular arithmetic to handle circular movement
- Dictionary to store visited sector positions and their step counts
- Iterative search to find cycle length
"""

import sys

inp = lambda dtype: [dtype(x) for x in input().split()]
debug = lambda *x: print(*x, file=sys.stderr)
sum_n = lambda n: (n * (n + 1)) // 2
get_bit = lambda x, i: (x >> i) & 1
ceil_ = lambda a, b: a // b if (a >= 0) ^ (b > 0) else (abs(a) + abs(b) - 1) // abs(b)
Mint, Mlong, out = 2**30 - 1, 2**62 - 1, []


def ask(q) -> int:
    sys.stdout.write(q)
    sys.stdout.write("\n")
    sys.stdout.flush()
    ret = int(input())
    return ret


def answer(q):
    sys.stdout.write(q)
    sys.stdout.write("\n")
    sys.stdout.flush()


def factorize(n) -> list:
    c, ans = 1, []
    while c * c < n:
        if n % c == 0:
            ans.extend([c, n // c])
        c += 1

    if c * c == n:
        ans.append(c)
    return sorted(ans)


def prime_fac(n):
    dist, ext = n, 0
    for i in factorize(n)[1:]:
        while n % i == 0:
            n //= i
            if ask(f"+ {dist //i +ext }") == cur:
                dist //= i
                ext = 0
            else:
                ext = dist - dist // i

    return dist


for _ in range(1):
    x = int(input())
    vis = dict()
    cur, vis[x], dist = x, 0, 0

    for i in range(1000):
        dist += 1000
        cur = ask("+ 1000")
        vis[cur] = dist

    for i in range(1000):
        dist += 1
        cur = ask("+ 1")
        if cur in vis:
            break

    dist -= vis[cur]
    ext = 0
    out.append(f"! {prime_fac (dist )}")
print("\n".join(map(str, out)))


# https://github.com/VaHiX/CodeForces/