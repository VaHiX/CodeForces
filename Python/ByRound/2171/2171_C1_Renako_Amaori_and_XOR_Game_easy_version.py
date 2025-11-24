# Problem: CF 2171 C1 - Renako Amaori and XOR Game (easy version)
# https://codeforces.com/contest/2171/problem/C1

"""
Algorithm: XOR Game Analysis
Purpose: Determine the winner of a game between Ajisai and Mai where they take turns swapping elements in arrays a and b at specific indices, aiming to maximize their respective XOR scores.

Techniques:
- Greedy approach based on parity of element differences
- Analysis of turn-based decisions using XOR properties

Time Complexity: O(n) per test case, where n is the length of the arrays
Space Complexity: O(n) for storing input arrays

The key insight is:
1. If the total number of 1s in both arrays is even, the game must end in a tie.
2. Otherwise, we determine who wins by analyzing the last differing position between a and b.
   - If the last differing index is even (Ajisai's turn), Ajisai wins.
   - If the last differing index is odd (Mai's turn), Mai wins.
"""

def ints():
    return [int(x) for x in input().split(" ")]

def solve():
    n = int(input())
    a = ints()
    b = ints()
    # If the total number of 1s is even, the game must end in a tie
    if (sum(a) + sum(b)) % 2 == 0:
        return print("Tie")
    # Find the last index where a[i] != b[i]
    for i in range(n - 1, -1, -1):
        if a[i] != b[i]:
            # If this index is even, Ajisai's turn; else, Mai's turn
            return print("Ajisai" if i % 2 == 0 else "Mai")

for i in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/