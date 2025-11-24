# Problem: CF 1875 B - Jellyfish and Game
# https://codeforces.com/contest/1875/problem/B

"""
Problem: Jellyfish and Game

Algorithms/Techniques: Greedy approach, Analysis of optimal swaps in alternating turns.

Time Complexity: O(n + m) per test case, where n and m are the sizes of arrays a and b.
Space Complexity: O(1) - only using a few variables for tracking max/min values.

The problem involves two players (Jellyfish and Gellyfish) taking turns to swap apples in a game
with k rounds. Jellyfish plays on odd rounds, Gellyfish on even rounds.
Both players play optimally to maximize their own sum of apple values.

Key observations:
1. On odd rounds (Jellyfish's turn), she wants to improve her sum.
2. On even rounds (Gellyfish's turn), he wants to improve his sum.
3. The optimal strategy is to find the best swap between players' apples.

Approach:
- Track max and min values in both arrays.
- If k is odd: Jellyfish moves first and can improve her total sum.
- If k is even: Gellyfish moves first.
"""

for _ in range(int(input())):
    n, m, k = list(map(int, input().split()))
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    amax = max(a)
    amin = min(a)
    bmax = max(b)
    bmin = min(b)
    if k % 2:
        # Odd rounds: Jellyfish goes first.
        # Jellyfish can get the best value from Gellyfish's apples.
        print(sum(a) - amin + max(amin, bmax))
    elif amin >= bmax:
        # If all of Jellyfish's apples are >= all of Gellyfish's apples,
        # and it's Gellyfish's turn, then Gellyfish can only hurt his own sum.
        print(sum(a) - amax + bmin)
    else:
        # In other even cases, the best swap depends on optimal values.
        print(sum(a) - amax - amin + min(amax, bmax) + min(amin, bmin))


# https://github.com/VaHiX/CodeForces/