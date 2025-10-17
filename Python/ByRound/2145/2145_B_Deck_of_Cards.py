# Problem: CF 2145 B - Deck of Cards
# https://codeforces.com/contest/2145/problem/B

"""
B. Deck of Cards
Algorithm: Simulation with interval tracking
Time Complexity: O(n + k) per test case
Space Complexity: O(n) for output string

This problem simulates a deck of cards being manipulated by removing cards from the top or bottom,
or choosing either depending on the operation type. For each card in the deck, we determine whether it:
- Remains in the deck (+)
- Was definitely removed (-)
- Might have been removed or not (?)

The approach tracks intervals of potential positions for cards that could survive,
considering all possible choices represented by '2'. The algorithm maintains ranges
of valid positions at each step and updates them accordingly.
"""

import sys


def solve():
    data = sys.stdin.read().strip().split()
    it = iter(data)
    t = int(next(it))
    out_lines = []
    for _ in range(t):
        n = int(next(it))
        k = int(next(it))
        s = next(it).strip()
        c0 = s.count("0")  # Count of top removals
        c2 = s.count("2")  # Count of ambiguous operations
        remain = n - k
        if remain == 0:
            out_lines.append("-" * n)
            continue
        Lmin = c0 + 1  # Minimum position that can survive (after all top removals)
        Lmax = c0 + c2 + 1  # Maximum position that can survive (accounting for 2s)
        Rmin = Lmin + remain - 1  # Leftmost possible surviving position after removings
        Rmax = Lmax + remain - 1  # Rightmost possible surviving position
        res = ["?"] * n  # Initialize result array with '?'
        for i in range(1, Lmin):  # Cards before Lmin are definitely removed
            res[i - 1] = "-"
        for i in range(Rmax + 1, n + 1):  # Cards after Rmax are definitely removed
            res[i - 1] = "-"
        if Lmax <= Rmin:  # There's an interval where cards could be both in and out
            for i in range(Lmax, Rmin + 1):
                res[i - 1] = "+"  # Cards in this range are definitely in deck
        out_lines.append("".join(res))
    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/