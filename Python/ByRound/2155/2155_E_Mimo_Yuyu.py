# Problem: CF 2155 E - Mimo & Yuyu
# https://codeforces.com/contest/2155/problem/E

"""
E. Mimo & Yuyu

This problem is a classic impartial game theory problem, specifically about Grundy numbers (Nimbers) in combinatorial game theory.

The key insight is that each token contributes to the game state based on its column position. For any token at position (x, y), we can perform a move if:
1. The starting column b1 > b2 (i.e., b2 = b1 - 1)
2. All intermediate columns are non-increasing
3. The final column is 1

We observe that tokens in column 1 cannot be moved, and tokens in column 2 can only move to columns 1 and 2.
For tokens in column ≥ 3, we consider the "exponent" (column - 2) as a key indicator of move possibilities.

Each token's position contributes to a "xor-sum" of exponents:
- If n = 1: The number of tokens in column 2 determines the outcome directly.
- If n > 1: The XOR of all exponents determines who wins:
  - If XOR is 0, first player (Mimo) loses → Yuyu wins
  - If XOR is non-zero, first player (Mimo) wins → Mimo wins

Time Complexity: O(k) per test case where k is the number of tokens
Space Complexity: O(k) for storing exponent counts in worst-case scenario

Algorithms/Techniques:
- Combinatorial Game Theory (Nimber calculation)
- XOR operations for determining winning/losing positions
"""

import sys


def solve():
    try:
        line = sys.stdin.readline()
        if not line:
            return
        n, m, k = map(int, line.split())
    except (IOError, ValueError):
        return
    if n == 1:
        # Special case: Only one row
        col2_count = 0
        for _ in range(k):
            x, y = map(int, sys.stdin.readline().split())
            if y == 2:
                col2_count += 1
        # If odd number of tokens are in column 2, Mimo loses (Yuyu wins)
        if col2_count % 2 != 0:
            print("Mimo")
        else:
            print("Yuyu")
    else:
        # General case: More than one row
        exponent_counts = {}
        for _ in range(k):
            x, y = map(int, sys.stdin.readline().split())
            if y > 1:
                # Calculate exponent as (y - 2) and count occurrences
                exponent = y - 2
                exponent_counts[exponent] = exponent_counts.get(exponent, 0) + 1
        winner = "Yuyu"
        # Check if any exponent occurs an odd number of times
        for count in exponent_counts.values():
            if count % 2 != 0:
                winner = "Mimo"
                break
        print(winner)


def main():
    try:
        num_tests_str = sys.stdin.readline()
        if num_tests_str:
            num_tests = int(num_tests_str)
            for _ in range(num_tests):
                solve()
    except (IOError, ValueError):
        return


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/