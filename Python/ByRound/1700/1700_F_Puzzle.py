# Problem: CF 1700 F - Puzzle
# https://codeforces.com/contest/1700/problem/F

"""
Algorithm: Puzzle
Purpose: Determine the minimum number of adjacent swaps needed to transform a 2xN puzzle from current to desired state.
Techniques: Greedy approach with tracking of imbalance between rows.

Time Complexity: O(n)
Space Complexity: O(n)

The algorithm works by:
1. Calculating the net difference in each row between current and target states.
2. Using a greedy approach to balance the differences by swapping elements.
3. Counting the total number of swaps required to resolve the discrepancies.
4. Returning -1 if the transformation is impossible (imbalance in total elements).

This solution efficiently tracks row imbalances and calculates minimal swaps without simulating actual moves.
"""

def solve():
    n = int(input())

    matrix = []

    for _ in range(4):
        matrix.append([int(data) for data in input().split()])

    top = 0
    bottom = 0
    total = 0

    for i in range(n):
        # Calculate difference in top row (current vs target)
        top += matrix[0][i] - matrix[2][i]
        # Calculate difference in bottom row (current vs target)
        bottom += matrix[1][i] - matrix[3][i]

        # Greedily resolve imbalances between rows
        # If top has excess 1s and bottom has excess 0s, we need to move a 1 from top to bottom
        if bottom < 0 and 0 < top:
            top -= 1
            bottom += 1
            total += 1
        # If bottom has excess 1s and top has excess 0s, we need to move a 1 from bottom to top
        elif top < 0 and 0 < bottom:
            top += 1
            bottom -= 1
            total += 1

        # Add absolute imbalances (remaining differences)
        total += abs(top) + abs(bottom)

    # If total imbalance is not zero, transformation is impossible
    if top + bottom != 0:
        return -1

    return total


print(solve())


# https://github.com/VaHiX/CodeForces/