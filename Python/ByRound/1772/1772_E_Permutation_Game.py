# Problem: CF 1772 E - Permutation Game
# https://codeforces.com/contest/1772/problem/E

"""
Problem: E. Permutation Game
Algorithms/Techniques: Greedy, Game Theory, Sorting Analysis

Time Complexity: O(n) per test case
Space Complexity: O(1) extra space (excluding input/output storage)

This solution analyzes the permutation to determine the winner of a game where:
- Players take turns modifying a permutation
- First player wins if it becomes sorted ascending
- Second player wins if it becomes sorted descending
- The game is analyzed using greedy strategy based on positions of elements

The key insight is to classify elements into three categories:
1. Fixed elements (correct position for ascending or descending)
2. Forward elements (only correct in ascending order)
3. Backward elements (only correct in descending order)

Based on counts of these categories, we decide the outcome.
"""

import sys

input = sys.stdin.readline

T = int(input())
ans = [""] * T

for t in range(T):
    n = int(input())
    p = [0] + list(map(int, input().split()))  # 1-indexed array

    f = 0  # count of elements that are only correct in forward (ascending) order
    s = 0  # count of elements that are only correct in backward (descending) order
    b = 0  # count of elements that are correct in both orders

    for i in range(1, n + 1):
        if p[i] != i and p[i] != n - i + 1:
            # Element is not in correct position for either ascending or descending
            b += 1
        elif p[i] != i:
            # Element is in correct ascending position but not descending
            f += 1
        elif p[i] != n - i + 1:
            # Element is in correct descending position but not ascending
            s += 1

    # Determine the winner based on the counts
    if f + b <= s:
        # First player can win by focusing on forward elements
        ans[t] = "First"
    elif s + b < f:
        # Second player can win by focusing on backward elements
        ans[t] = "Second"
    else:
        # Neither side has clear advantage, it's a tie
        ans[t] = "Tie"

print("\n".join(ans))


# https://github.com/VaHiX/CodeForces/