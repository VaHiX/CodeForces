# Problem: CF 2018 A - Cards Partition
# https://codeforces.com/contest/2018/problem/A

"""
Algorithm: Binary search on the answer + greedy validation
Approach:
- We binary search on the possible deck sizes (from n down to 1).
- For each candidate deck size `i`, we check if it's possible to form decks of size `i`:
    - We need at least `i` cards in total, but we can buy up to `k` more.
    - So, total cards after buying should be at least `i`.
    - A greedy way to determine: compute the minimal number of cards per deck (a).
    - If `a * i >= total_cards` and `a >= max_card_value`, then it's possible.

Time Complexity: O(n log n) per test case due to binary search over deck size,
                 where each check involves computing sum and max which is O(n).
Space Complexity: O(1), only using a few variables.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
for _ in range(int(input())):
    n, k = map(int, input().split())
    w = list(map(int, input().split()))
    x, y = max(w), sum(w)
    for i in range(n, 0, -1):  # Try decreasing deck sizes from n down to 1
        a = (y + k) // i     # Estimate minimum cards needed per type to fill i decks
        if a * i >= y and a >= x:  # Check if we can form valid partitions with size i
            print(i)
            break


# https://github.com/VaHiX/codeForces/