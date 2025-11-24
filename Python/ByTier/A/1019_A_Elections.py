# Problem: CF 1019 A - Elections
# https://codeforces.com/contest/1019/problem/A

"""
A. Elections

Algorithm: Greedy with Priority Queue (Heap)
Time Complexity: O(n * log n)
Space Complexity: O(n)

The problem involves selecting minimum cost to ensure Party 1 wins by getting strictly more votes than any other party.
We use a greedy approach:
1. For each party (except 1), collect all voters and sort their costs in ascending order.
2. We try to build the smallest number of votes for party 1 such that it exceeds all others.
3. To do this efficiently, we maintain a max heap (using min-heap with negative values) of the most expensive voters
   that we could have bought but did not yet buy for party 1.
4. We iterate over possible vote counts for party 1 and try to minimize total cost by swapping expensive voters 
   from other parties to party 1 when needed.

This greedy approach works because we sort voters by descending cost for each party, ensuring we only need to consider 
adding minimal cost votes to win.
"""

import sys
from heapq import *

input = lambda: sys.stdin.readline().rstrip()
sint = lambda: int(input())
mint = lambda: map(int, input().split())
ints = lambda: list(map(int, input().split()))


def solve() -> None:
    n, m = mint()
    cost = [[] for _ in range(m + 1)]
    s = 0
    for _ in range(n):
        p, c = mint()
        if p != 1:
            cost[p].append(c)
            s += c
    d = [[] for _ in range(n + 1)]
    for i in range(2, m + 1):  # Loop through all parties except 1 (United Party)
        cost[i].sort()         # Sort costs in ascending order
        for j in range(len(cost[i]) - 1, -1, -1):  # Reverse loop to fill d with descending costs
            d[len(cost[i]) - j].append(cost[i][j])
    ans, cnt = s, n   # ans: minimum cost to win, cnt: current number of voters that support party 1 (including those not bought)
    h = []
    for k in range(1, n + 1):  # Try to find optimal number of votes for party 1
        for c in d[k]:         # Process all voters that can be shifted to party 1 if needed
            heappush(h, c)     # Add current cost (largest so far) into max heap
            s -= c             # Remove from total
            cnt -= 1           # Decrease count of voters supporting other parties
        while h and cnt <= k:  # While we haven't enough supporters for party 1 yet, recover most expensive voter from others
            cnt += 1         # Take one from others to support party 1
            s += heappop(h)  # Add back the cost of that voter (heappop removes the smallest value in min-heap)
        if cnt <= k:           # If even after all actions there's no way party 1 wins
            break
        ans = min(ans, s)      # Update answer with the minimal total cost
    
    print(ans)


solve()


# https://github.com/VaHiX/codeForces/