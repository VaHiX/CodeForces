# Problem: CF 1772 G - Gaining Rating
# https://codeforces.com/contest/1772/problem/G

"""
Algorithm: Greedy with Mathematical Optimization
Time Complexity: O(n * log(n)) due to sorting and iterative processing
Space Complexity: O(n) for storing opponent ratings

Approach:
1. First check if it's even possible to reach the target rating y.
   This is done by simulating a greedy approach where Monocarp plays against opponents with
   ratings <= current rating to gain 1 point, and lose 1 point otherwise.
2. If reaching y is possible:
   - Traverse the sorted list of opponent ratings.
   - When an opponent's rating is <= current rating, win (gain 1 point).
   - When opponent's rating > current rating:
     - Calculate how many games (with current strategy) are required to make progress.
     - Use mathematical formulas to compute minimum steps needed.
   - After processing all opponents, handle remaining points to reach y.

The key insight uses the constraint that moves against opponents must be balanced:
i.e., if Monocarp starts playing with a set of opponents, he shouldn't have played
more games against one opponent than another.

So we model:
- For each opponent, compute how much we gain/lose depending on current rating.
- Optimize by calculating minimal games using linear progression.
"""

import sys

input = lambda: sys.stdin.buffer.readline().decode().strip()
inp = lambda dtype: [dtype(x) for x in input().split()]
debug = lambda *x: print(*x, file=sys.stderr)
ceil1 = lambda a, b: (a + b - 1) // b
Mint, Mlong = 2**31 - 1, 2**63 - 1
get_bit = lambda x, i: (x >> i) & 1
out = []


def possible():
    cur = x
    for i in range(n):
        cur += pow(-1, a[i] > cur)  # Gain 1 if win, else lose 1
        if cur == y:
            return 1
    return cur > x


for _ in range(int(input())):
    n, x, y = inp(int)
    a = sorted(inp(int))  # Sort opponents by rating

    if possible():
        ans, cur = 0, x
        for i in range(n):
            if cur == y:
                break
            if a[i] <= cur:
                cur += 1
                ans += 1
            else:
                # Find the number of games needed when rating is too low
                delta = i - (n - i)
                # If 'delta' is positive, it's better to start playing all opponents
                # Else, it means too many high-rated opponents to balance.
                games = ceil1(a[i] - cur, delta)  # Compute how many full cycles

                if cur + games * delta >= y:
                    # Optimization: calculate exact needed steps
                    div, mod = divmod(y - cur, delta)
                    ans += div * n + mod + (n - i) * bool(mod) * 2
                    cur = y
                    break

                ans += games * n + 1  # Each cycle uses n games + 1 more for the final step
                cur += games * delta + 1  # Update current rating based on full cycles

        # Now, after all games played, we compute last stretch to hit y
        div, mod = divmod(y - cur, n)
        out.append(ans + div * n + mod)
    else:
        out.append(-1)

print("\n".join(map(str, out)))


# https://github.com/VaHiX/CodeForces/