# Problem: CF 1895 E - Infinite Card Game
# https://codeforces.com/contest/1895/problem/E

"""
Infinite Card Game Solution

Algorithms/Techniques:
- Sorting both players' cards by defense (Monocarp) and attack (Bicarp) respectively
- Preprocessing maximum attack values for Monocarp and maximum defense values for Bicarp
- Two-pointer technique to determine cutoff points for winning, drawing, and losing moves
- Binary search or scanning approach to find optimal strategies

Time Complexity: O(n log n + m log m) due to sorting 
Space Complexity: O(n + m) for storing card data and auxiliary arrays

The problem involves a two-player game where each player chooses cards strategically. 
Monocarp starts first, and the game continues until one player cannot respond, 
with the game being a draw if it exceeds 100 moves. 
This solution analyzes the card strengths to classify starting moves into win/draw/lose outcomes.
"""

from sys import *

input = stdin.readline
inputlist = lambda: map(int, stdin.readline().split())


def solve():
    m = int(input())
    monocarpattack = list(inputlist())
    monocarpdefense = list(inputlist())
    b = int(input())
    bicarpattack = list(inputlist())
    bicarpdefense = list(inputlist())

    monocarp = list(zip(monocarpattack, monocarpdefense))
    bicarp = list(zip(bicarpattack, bicarpdefense))

    # Sort Monocarp's cards by defense in descending order
    monocarp.sort(key=lambda x: x[1], reverse=True)
    # Sort Bicarp's cards by attack in descending order
    bicarp.sort(key=lambda x: x[0], reverse=True)

    # Precompute prefix maximums for attack (Monocarp) and defense (Bicarp)
    bestattackmonocarp = [0] * (m + 1)
    bestdefensebicarp = [0] * (b + 1)
    
    # Build prefix max of attack values for Monocarp
    for i in range(m):
        bestattackmonocarp[i + 1] = max(bestattackmonocarp[i], monocarp[i][0])
    
    # Build prefix max of defense values for Bicarp
    for i in range(b):
        bestdefensebicarp[i + 1] = max(bestdefensebicarp[i], bicarp[i][1])

    temp, wincutoff, drawcutoff = 0, 0, 0
    
    # Iterative process to find cutoff points
    for i in range(m):
        # Move temp pointer until Monocarp's card defense < Bicarp's card attack
        while temp < b and monocarp[i][1] < bicarp[temp][0]:
            temp += 1
            
        # If no valid Bicarp card, current Monocarp move wins
        if temp == 0:
            wincutoff = i + 1
        else:
            # Check if we can win by comparing attack and defense
            if bestattackmonocarp[wincutoff] > bestdefensebicarp[temp]:
                wincutoff = i + 1
            elif bestattackmonocarp[i + 1] > bestdefensebicarp[temp]:
                drawcutoff = i + 1

    # Return wins, draws, losses for Monocarp's starting moves
    return [wincutoff, max(0, drawcutoff - wincutoff), m - max(wincutoff, drawcutoff)]


for _ in range(int(input())):
    print(*solve())


# https://github.com/VaHiX/CodeForces/