# Problem: CF 2022 D2 - Asesino (Hard Version)
# https://codeforces.com/contest/2022/problem/D2

"""
Algorithm: Adaptive Query Strategy to Identify Impostor

This solution uses an adaptive querying strategy to identify the impostor among n players.
The key insight is to use pairwise queries to determine the roles of players and then
identify the impostor based on inconsistencies in responses.

Time Complexity: O(n) average case, O(n^2) worst case due to adaptive queries
Space Complexity: O(1) - only using a few variables for tracking

Approach:
1. For large n (>5), use a greedy strategy to reduce the search space
2. For small n (<=5), use predetermined queries based on small cases
3. The strategy uses the fact that:
   - Knights always tell truth
   - Knaves always lie
   - Impostor always lies to others but claims others are knights (inconsistent responses)
   - When two players have contradictory answers about each other, one is impostor
4. Queries are designed to minimize the number of questions needed in the worst case
"""

import sys

input = lambda: sys.stdin.readline().rstrip("\r\n")
sint = lambda: int(input())
mint = lambda: map(int, input().split())
aint = lambda: list(map(int, input().split()))


def query(x, y):
    print("?", x, y, flush=True)
    return sint()


def answer(x):
    print("!", x, flush=True)


T = sint()
for _ in range(T):
    n = sint()
    while n > 5:
        # Check if n-1 and n are impostors by asking about each other
        # If only one of them claims the other is a knight, then one of them is impostor
        if query(n - 1, n) + query(n, n - 1) == 1:
            # Determine which one is actually the impostor by checking with player 1
            answer(n if query(1, n) + query(n, 1) == 1 else n - 1)
            break
        else:
            # If both claim each other is Knight, or both lie, reduce search space
            n -= 2
    else:
        # For small n (3, 4, or 5), use specific cases
        # The following logic exploits specific patterns found in small groups
        if n == 3:
            # For n=3, we look at responses between 1,2,3 and check consistency
            if query(1, 2) + query(2, 1) == 1:
                # If only one claims other is knight, use further queries
                answer(1 if query(1, n) + query(n, 1) == 1 else 2)
            else:
                # If both claim each other is knight, third must be impostor
                answer(n)
        elif n == 4:
            # Check for inconsistent answers between 1 and 2
            if query(1, 2) + query(2, 1) == 1:
                answer(1 if query(1, n) + query(n, 1) == 1 else 2)
            else:
                # If no contradiction, then either n or 3 is impostor
                answer(n if query(1, n) + query(n, 1) == 1 else 3)
        else:
            # n == 5 case - use a more complex strategy with triangle queries
            v = [query(1, 2), query(2, 3), query(3, 1)]
            # Determine if even or odd number of "yes" answers in triangle
            if sum(v) % 2:
                # Odd sum means the impostor is at position n or 4
                answer(n if query(1, n) + query(n, 1) == 1 else 4)
            else:
                # Even sum implies a relationship between positions 1,2,3
                # Special handling for this case
                if v[0] + query(2, 1) == 1:
                    # Use consistent pattern to determine impostor
                    answer(1 if query(1, 3) + v[2] == 1 else 2)
                else:
                    answer(3)


# https://github.com/VaHiX/CodeForces/