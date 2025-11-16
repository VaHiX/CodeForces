# Problem: CF 1955 F - Unfair Game
# https://codeforces.com/contest/1955/problem/F

"""
Code Purpose:
This code solves the problem of determining the maximum number of times Bob can win 
in a game where Alice and Bob play with a sequence of numbers (0-4), and Eve removes 
numbers optimally to maximize Bob's wins. The key insight is to use the XOR properties 
of the numbers and simulate optimal removals.

Algorithm:
- The core idea is to analyze how many times we can form a sequence where XOR is zero.
- For each number type (0, 1, 2, 3, 4), we can pair them optimally such that their XOR equals zero.
- Specifically:
  - Numbers 0, 2, and 4 can be paired to contribute 0 to XOR.
  - For numbers 1 and 3, pairing them together gives XOR = 2 (non-zero), so we need to pair them in a way to allow zero XORs.
- The main formula uses integer division and modulo to count valid pairs and remaining unpaired elements.

Time Complexity: O(1) per test case
Space Complexity: O(1)

Authors: Based on solution approach
"""

from sys import stdin, stdout


def solve():
    # Read the count of numbers 0, 1, 2, 3, 4 in the sequence
    a, b, c, d = map(int, stdin.readline().split())
    
    # Calculate maximum number of Bob's wins using optimal removals
    # Each pair of same numbers (0, 2, 4) contributes to a zero XOR
    # For 1s and 3s, we can pair them up and check if a leftover pair is possible
    # If all of a, b, c are odd, one more win for Bob can be achieved.
    stdout.write(
        str(
            a // 2  # Count pairs of 1s
            + b // 2  # Count pairs of 2s
            + c // 2  # Count pairs of 3s
            + d // 2  # Count pairs of 4s
            + (a % 2 == 1 and b % 2 == 1 and c % 2 == 1)  # Check if we can have one more win with odd counts
        )
        + "\n"
    )


def main():
    # Read number of test cases
    t = int(stdin.readline())
    for _ in range(t):
        solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/