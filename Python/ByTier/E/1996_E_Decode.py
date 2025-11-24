# Problem: CF 1996 E - Decode
# https://codeforces.com/contest/1996/problem/E

"""
Algorithm: Offline prefix sum with difference array technique
Technique: Transform the problem into counting subarrays with equal 0s and 1s
by using a running balance (prefix sum of 1s minus 0s), and then counting how many
previous positions have the same balance to form valid subarrays.

Time Complexity: O(n) per test case, where n is the length of the string
Space Complexity: O(n) for the auxiliary array b

The key insight is to convert the problem of finding subarrays with equal 0s and 1s
into a problem of finding pairs of indices with same running balance.
"""

import sys

input = lambda: sys.stdin.readline().strip()


p = 10**9 + 7


T = int(input())
for _ in range(T):
    s = input()
    n = len(s)
    # b is an auxiliary array to store counts of prefix balances
    b = [0] * (2 * n + 1)
    b[0] = 1  # base case: balance 0 at index 0
    k = 0  # running count of 1s
    ans = 0  # final answer
    for i in range(n):
        # Update k (number of 1s so far)
        k += int(s[i])
        # Calculate balance: 2*k - i - 1 (this transforms the problem nicely)
        # For a subarray from x to y, the number of 0s = number of 1s iff
        # (sum of 1s from x to y) = (sum of 0s from x to y)
        # Which is true iff (sum of 1s from 0 to y) - (sum of 1s from 0 to x-1) 
        # = (y - x + 1) - (sum of 1s from 0 to y) + (sum of 1s from 0 to x-1)
        # After rearranging, this leads to balance condition:
        # 2 * (sum_1s[0..x-1]) = x + 2 * (sum_1s[0..y]) - y - 1
        # So we calculate balance = 2 * sum_1s[0..y] - y - 1
        # For a valid subarray [x..y], this should equal balance of [0..x-1]
        # Let balance of [0..y] = 2 * k - y - 1
        # Then balance of [0..x-1] = 2 * sum_1s[0..x-1] - x + 1 = 2 * k - i - 1
        # Wait, that's confusing!
        # Instead, let's define balance = 2 * sum_1s - index - 1
        # If balance at i is same as at j, then subarray [j+1..i] has equal 0 and 1
        # That's why we're looking at b[2*k - i - 1] to see how many such j exist before i.

        # Query: Count how many previous positions had the same balance as current
        # We add (n - i) because of how the math works in this specific transformation
        ans += b[2 * k - i - 1] * (n - i)
        ans %= p
        # Update b: increment count of current balance
        b[2 * k - i - 1] += i + 2
        b[2 * k - i - 1] %= p
    print(ans)


# https://github.com/VaHiX/CodeForces/