# Problem: CF 1951 C - Ticket Hoarding
# https://codeforces.com/contest/1951/problem/C

"""
Algorithm: Greedy with Prefix Sum
Purpose: To minimize the total cost of purchasing k tickets over n days,
         where each day has a price, and buying x tickets on day i increases
         all subsequent day prices by x.

Time Complexity: O(n log n) due to sorting the prices.
Space Complexity: O(1) as we use only a constant amount of extra space.

Approach:
- Sort the ticket prices in ascending order to apply greedy strategy.
- For each price, calculate the current effective price (price + accumulated surge).
- Buy up to m tickets per day, minimizing cost by always choosing the cheapest available.
- Update the surge (s) after each purchase, which affects future prices.
"""

import sys


def main():
    input = sys.stdin.read().split()
    ptr = 0
    t = int(input[ptr])
    ptr += 1
    for _ in range(t):
        n, m, k = map(int, input[ptr : ptr + 3])
        ptr += 3
        a = list(map(int, input[ptr : ptr + n]))
        ptr += n
        # Sort prices to enable greedy selection of minimum costs
        a.sort()
        total = 0
        s = 0  # Surge effect on future prices
        remaining = k  # Number of tickets left to buy
        for price in a:
            if remaining <= 0:
                break
            current = price + s  # Effective price considering surge
            buy = min(m, remaining)  # Buy at most m tickets or remaining tickets
            total += buy * current  # Add cost of this batch
            remaining -= buy  # Reduce remaining tickets
            s += buy  # Increase surge for subsequent days
        print(total)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/