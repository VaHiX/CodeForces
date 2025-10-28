# Problem: CF 2004 C - Splitting Items
# https://codeforces.com/contest/2004/problem/C

"""
C. Splitting Items

Purpose:
This problem involves optimizing a game between Alice and Bob where they take turns selecting items with costs.
Alice wants to maximize the difference A - B (where A is her total cost, B is Bob's),
and Bob wants to minimize it. Both play optimally. Bob can increase item costs by at most k total,
but cannot decrease them.

Algorithm:
- Sort items in descending order of cost.
- Simulate the game with optimal play.
- For each player's turn, decide whether to take the current item or wait (based on maximizing/minimizing A - B).
- Bob tries to increase costs in a way that leads to minimal score.
- The key idea is to simulate the turn-based selection and assign changes strategically.

Time Complexity: O(n log n) per test case due to sorting.
Space Complexity: O(1) excluding input/output storage.

"""

for _ in range(int(input())):
    n, k = map(int, input().split())
    a = sorted(map(int, input().split()), reverse=True)
    x = y = 0  # x: Alice's total cost, y: Bob's total cost
    for i in range(n):
        if i & 1:  # Bob's turn (odd index)
            # Calculate how much we can increase the previous item's value 
            # to make it closer to current item's value (so Bob takes lower-value item)
            d = min(k, a[i - 1] - a[i])
            y += a[i] + d  # Add actual value of item plus increase
            k -= d  # Decrease remaining allowed increase
        else:  # Alice's turn (even index)
            x += a[i]  # Alice takes item with max value in optimal play
    print(x - y)  # Final score difference A - B


# https://github.com/VaHiX/codeForces/