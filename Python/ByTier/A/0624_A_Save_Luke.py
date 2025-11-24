# Problem: CF 624 A - Save Luke
# https://codeforces.com/contest/624/problem/A

"""
Problem: Save Luke
Algorithm: Simple simulation of two approaching objects.
Time Complexity: O(1)
Space Complexity: O(1)

The problem involves two presses moving toward each other at speeds v1 and v2,
starting at positions 0 and L respectively. Luke, with width d, needs to find
the optimal position to survive as long as possible. The key insight is that
Luke dies when the distance between the presses is less than d. The maximum
survival time is when the presses are at distance d from each other, which
happens after time (L - d) / (v1 + v2), since they approach each other at
combined speed v1 + v2. Luke should choose a position where he is safe from
both directions until the presses meet.
"""

d, l, v1, v2 = map(int, input().split())
print(float((l - d) / (v1 + v2)))


# https://github.com/VaHiX/CodeForces/