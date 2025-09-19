# Contest 2030, Problem D: QED's Favorite Permutation
# URL: https://codeforces.com/contest/2030/problem/D

# ruff: noqa: E731, E741
from itertools import accumulate
import sys

read = sys.stdin.readline
input = lambda: read().strip()
ir = lambda: int(read())
rir = lambda: range(int(read()))
mir = lambda: map(int, read().split())
lmir = lambda: list(map(int, read().split()))


def main():
    for _ in rir():
        n, q = mir()
        p = [x - 1 for x in mir()]
        s = [c == "R" for c in input()]

        allowed = {i + 1 for i, x in enumerate(accumulate(p, max)) if i == x != n - 1}
        forbidden = {
            i for i in range(1, n) if not s[i - 1] and s[i] and i not in allowed
        }

        for _ in range(q):
            idx = ir() - 1
            s[idx] = not s[idx]
            for j in (idx, idx + 1):
                if not s[j - 1] and s[j] and j not in allowed:
                    forbidden.add(j)
                else:
                    forbidden.discard(j)
            print("NO" if forbidden else "YES")


if __name__ == "__main__":
    main()
