# Problem: CF 2019 C - Cards Partition
# https://codeforces.com/contest/2019/problem/C

"""
C. Cards Partition

Algorithm: Greedy + Binary Search / Brute Force
Time Complexity: O(n * log(max_sum)) where max_sum is up to 10^16
Space Complexity: O(1)

The problem asks us to find the maximum possible deck size after buying at most k cards,
such that all decks have equal size and no two cards with same value are in the same deck.

Key Insight:
- If we want decks of size d, each deck must contain distinct values.
- So for a deck of size d, we need exactly d distinct card types.
- Total available card types = n
- We can buy at most k new cards to support larger decks.

Approach:
1. Initially compute sum of all cards (total cards), max card count.
2. Compute an initial upper bound: s + k // max_card_count (this is the maximum deck size).
3. Then try to find if we can actually form a valid partition for that deck size.
4. If not, decrease deck size and repeat.

The solution iterates from potential maximum deck size down to 1,
checking if it's possible to form a valid arrangement using buyable cards and existing ones.
"""

from sys import stdin

inp = stdin.readline
t = int(inp())
for _ in range(t):
    n, k = map(int, inp().split())
    arr = [int(x) for x in inp().split()]
    s = sum(arr)
    m = max(arr)
    ans = min((s + k) // m, n)
    while (s + k) % ans > k and k < ans:
        ans -= 1
    print(ans)


# https://github.com/VaHiX/codeForces/