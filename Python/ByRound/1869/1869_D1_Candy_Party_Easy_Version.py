# Problem: CF 1869 D1 - Candy Party (Easy Version)
# https://codeforces.com/contest/1869/problem/D1

"""
Code Purpose:
This code determines whether it's possible to redistribute candies among n people at a party such that:
1. Each person gives exactly one candy transfer and receives exactly one candy transfer.
2. After all transfers, everyone has the same number of candies.

The solution works by:
- Checking if total candies can be evenly divided among people (necessary condition).
- Using binary representation to determine how many candies to transfer (powers of 2).
- For each person, calculate how many candies they need to give or receive.
- Track operations using a difference array to detect if all transfers balance out.

Algorithms/Techniques:
- Binary decomposition to represent amounts as sums of powers of 2.
- Difference array technique for efficient range updates.
- Greedy approach with bit manipulation to find valid transfer combinations.

Time Complexity: O(n log C) where n is number of people and C is maximum candy count.
Space Complexity: O(log C) for storing the difference array.
"""

from sys import stdin


def input():
    return stdin.readline()[:-1]


def d2(n):
    # Function to decompose a number into sum of powers of 2
    # and check if it's a valid composition (all 1s in binary)
    l = 0
    t = 1
    while t <= n:
        l += 1
        t *= 2
    d = t - n  # Difference to next power of 2
    r = 0
    t = 1
    while t < d:
        r += 1
        t *= 2
    if t != d:  # If difference is not exact power of 2, invalid decomposition
        return False
    else:
        return l, r  # Return indices of powers of 2 in decomposition


for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    s = sum(a)
    if s % n != 0:
        print("NO")
        continue
    mean = s // n  # Calculate required average candies per person
    operations = [0] * 50  # Array to track operations for difference array technique
    for i in a:
        d = mean - i  # Difference from mean: negative means need to give, positive means need to receive
        t = d2(abs(d))  # Decompose absolute difference into powers of 2
        if not t:
            print("NO")
            break
        l, r = t
        if d < 0:
            # If negative difference, we're giving candies
            # so we need to increase l (giving more) and decrease r (receiving less)
            l, r = r, l
        operations[l] += 1  # Mark one transfer of power l
        operations[r] -= 1  # Mark one transfer of power r (opposite direction)
    else:
        # Apply difference array technique to check if total operations balance
        # If all operations are balanced (net 0) then redistribution is possible
        if not any(operations):
            print("YES")
        else:
            print("NO")


# https://github.com/VaHiX/CodeForces/