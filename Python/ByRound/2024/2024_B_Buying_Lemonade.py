# Problem: CF 2024 B - Buying Lemonade
# https://codeforces.com/contest/2024/problem/B

"""
B. Buying Lemonade

Algorithm: Greedy + Sorting
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing the array

The problem involves a vending machine with n slots, each containing some number of cans.
We want to find the minimum number of button presses to guarantee at least k cans.
Since we don't know which button corresponds to which slot, we must adopt a strategy that
works regardless of the unknown mapping.

Strategy:
1. Sort the array in descending order so we handle slots with more cans first.
2. For each slot, calculate how many times we need to press its button to guarantee
   getting one can from it (we may have to press until it's empty, which is `a[i]` times).
3. Use a greedy approach: press the buttons in order of decreasing number of cans,
   but optimize by keeping track of how many cans we still need and how many slots are left.

Key insight:
After pressing a button and getting a can, we reduce k, and we may also adjust our strategy
by reducing n (slots) and incrementing r (total presses). This loop continues until k <= 0.
"""

R = lambda: map(int, input().split())
(t,) = R()
while t:
    t -= 1
    n, k = R()
    r = k  # Start with the number of cans needed as an initial estimate
    a = sorted(R())  # Sort in ascending order, will access from end (largest first)
    p = 0  # Previous value, tracks how many cans we've seen in last slot
    while k > 0:
        # Adjust k by subtracting the number of cans taken in previous slot,
        # and add the remaining presses needed for this slot (a[-n] - p) * n
        k += (p - (p := a[-n])) * n
        r += 1  # Increment total presses
        n -= 1  # Reduce number of available slots
    print(r - 1)


# https://github.com/VaHiX/codeForces/