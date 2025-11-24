# Problem: CF 1916 C - Training Before the Olympiad
# https://codeforces.com/contest/1916/problem/C

"""
Algorithm: Greedy + Math
Time Complexity: O(n)
Space Complexity: O(n)

The problem involves a game where players (Masha and Olya) take turns reducing an array
by combining two elements. The operation performed is:
floor((a[i] + a[j]) / 2) * 2

This effectively rounds the sum down to the nearest even number.

Key insight:
- If we have an odd number of odd elements, the final result is affected.
- The optimal strategy involves greedily combining elements to minimize or maximize
  the final value.
- We maintain counts of even and odd elements, and process them to compute
  the total sum after optimal play.

Approach:
1. For each element, add to the total sum and update even/odd counters.
2. If we have 3 or more odd numbers, we can reduce the sum by 1 as we can form
   pairs that contribute zero to the final even sum.
3. After processing, if there are 2 odd numbers, we can combine them with even ones
   to potentially increase or decrease the sum.
4. If there is 1 odd number, check if there are even numbers to pair with.
   If no even numbers, the value stays as is.
5. Otherwise, all numbers can be paired up without loss.
"""

import sys


def solve():
    inp = sys.stdin.readline
    int(inp())
    s = 0
    even = 0
    odd = 0
    res = []
    for i in map(int, inp().split()):
        s += i
        if i % 2 == 0:
            even += 1
        else:
            odd += 1
        # While we have at least 3 odd numbers, we can always reduce the sum by 1
        # by combining 3 odds into an even number (which reduces the total sum by 1)
        while odd >= 3:
            s -= 1
            odd -= 3
            even += 1
        # If we have exactly 2 odds left, we must pair them with an even number
        # to get a final even sum. If there is no even number, we simply take the sum
        if odd == 2:
            res.append(s)
        elif odd == 1:
            # If there is no even number, we don't reduce the sum as we're left with
            # an odd number that can't be reduced further
            if even == 0:
                res.append(s)
            else:
                # Pair the odd with an even and reduce the sum by 1
                res.append(s - 1)
        else:
            # No odd numbers or even number of odds: no reduction needed
            res.append(s)
    print(" ".join(map(str, res)))


def main():
    for i in range(int(sys.stdin.readline())):
        solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/