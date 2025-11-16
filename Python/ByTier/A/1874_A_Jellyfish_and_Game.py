# Problem: CF 1874 A - Jellyfish and Game
# https://codeforces.com/contest/1874/problem/A

"""
Algorithm: Jellyfish and Game
Purpose: Determine the maximum possible sum of values of Jellyfish's apples after k rounds of optimal swapping between two players.
Techniques:
- Greedy approach to maximize sum by swapping smallest value of Jellyfish with largest value of Gellyfish (when it's Jellyfish's turn)
- Swap smallest value of Gellyfish with largest value of Jellyfish (when it's Gellyfish's turn)
- Only first few rounds matter because after a certain point, the optimal swaps will stabilize.

Time Complexity: O(n + m + min(k, 2)) where n and m are sizes of arrays
Space Complexity: O(n + m) for storing the arrays
"""

def jellyfishandGame(n, m, k, ns, ms):
    # Determine how many rounds to simulate based on parity of k
    loop = 0
    if k % 2 == 0:
        loop = 2  # Even k -> simulate 2 rounds to see pattern
    else:
        loop = 1  # Odd k -> simulate 1 round
    
    # Simulate the game up to min(k, 2) rounds since after 2 rounds, further rounds will not change outcome
    for i in range(1, loop + 1):
        if i % 2 == 1:  # Jellyfish's turn (odd round)
            # Find min in Jellyfish's apples and max in Gellyfish's apples
            minVal = min(ns)
            maxVal = max(ms)
            minIndex = ns.index(minVal)
            maxIndex = ms.index(maxVal)
            # Perform swap only if beneficial
            if minVal < maxVal:
                ns[minIndex] = maxVal
                ms[maxIndex] = minVal
        else:  # Gellyfish's turn (even round)
            # Find min in Gellyfish's apples and max in Jellyfish's apples
            minVal = min(ms)
            maxVal = max(ns)
            minIndex = ms.index(minVal)
            maxIndex = ns.index(maxVal)
            # Perform swap only if beneficial
            if minVal < maxVal:
                ms[minIndex] = maxVal
                ns[maxIndex] = minVal
    return sum(ns)  # Return final sum of Jellyfish's apples


def playGame():
    t = int(input())
    results = ""
    for i in range(t):
        n, m, k = map(int, input().split())
        ns = list(map(int, input().split()))[:n]
        ms = list(map(int, input().split()))[:m]
        if i == (t - 1):
            results = results + str(jellyfishandGame(n, m, k, ns, ms))
        else:
            results = results + str(jellyfishandGame(n, m, k, ns, ms)) + "\n"
    print(results)


playGame()


# https://github.com/VaHiX/CodeForces/