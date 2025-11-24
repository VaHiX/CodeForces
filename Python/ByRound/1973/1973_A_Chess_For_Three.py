# Problem: CF 1973 A - Chess For Three
# https://codeforces.com/contest/1973/problem/A

"""
Chess For Three

Algorithm:
The problem involves determining the maximum number of draws possible among three players in a chess tournament, given their final scores.
Each game between two players awards either:
- 2 points to the winner and 0 to the loser (1 draw in total),
- 1 point to each player in case of a draw (2 draws in total).

Approach:
1. Let us denote the scores of the three players as p1 <= p2 <= p3.
2. We compute the total number of points from all games. Since a win gives 2 points and a draw gives 1 point to each player, the sum of all points is equal to 2 * number_of_games.
3. The key idea is to use a greedy approach to find the maximum number of draws.
4. Let S = p1 + p2. In the best case (maximum draws), we want to consider how we can distribute the points among the three players optimally.

Complexity:
Time Complexity: O(1) per test case. We perform constant time arithmetic operations.
Space Complexity: O(1). Only a constant amount of additional space is used.
"""

import sys

input = sys.stdin.readline
T = int(input())
for _ in range(T):
    p1, p2, p3 = map(int, input().split())
    a = p1 + p2
    ans = 0
    if a > p3:
        # When sum of p1 and p2 is greater than p3
        # This means p3 must have gained some points from draws or wins
        # The maximum number of draws is based on the surplus (a - p3)
        ans = p3
        if (a - p3) % 2 == 0:
            # If the surplus is even, we can fully convert it into draws
            ans += (a - p3) // 2
        else:
            # If the surplus is odd, it's impossible to form a valid state
            ans = -1
    elif a == p3:
        # When sum of p1 and p2 equals p3
        # The simplest case where all games are draws between p1 and p2
        ans = p3
    else:
        # When sum of p1 and p2 is less than p3
        # This means that p3 must have obtained points through wins
        # The maximum number of draws is limited by how many games can be allocated
        ans = a
        if (p3 - a) % 2 != 0:
            # If the difference is odd, it's impossible to construct valid games
            ans = -1
    print(ans)


# https://github.com/VaHiX/CodeForces/