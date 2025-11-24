# Problem: CF 2161 A - Round Trip
# https://codeforces.com/contest/2161/problem/A

"""
Purpose: Determine the maximum number of rated rounds Vasya can participate in given
         his initial rating R0, threshold X for div.2 rounds, and rating change delta D.
         Div.1 rounds are always rated. Div.2 rounds are rated only if rating < X.
         After each rated round, Vasya's rating decreases by D (minimum 0).

Algorithms/Techniques:
- Greedy approach: For each round, decide whether to participate based on rating
  and round type.
- Track current rating and count of rated rounds.

Time Complexity: O(n) per test case, where n is the number of rounds.
Space Complexity: O(1) excluding input/output storage.
"""

import sys


def solve1():
    it = iter(sys.stdin.read().strip().split())
    t = int(next(it))
    out_lines = []
    for _ in range(t):
        R0 = int(next(it))
        X = int(next(it))
        D = int(next(it))
        int(next(it))  # unused n
        s = next(it).strip()
        ans = 0
        rating = R0  # Start with initial rating
        for ch in s:
            if ch == "1":
                # Div.1 round is always rated
                ans += 1
                rating = max(0, rating - D)  # Decrease rating by D (min 0)
            else:
                # Div.2 round is rated only if current rating < X
                if rating < X:
                    ans += 1
                    rating = max(0, rating - D)  # Decrease rating by D (min 0)

        out_lines.append(str(ans))
    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    solve1()


# https://github.com/VaHiX/CodeForces/