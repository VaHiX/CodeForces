# Problem: CF 1899 A - Game with Integers
# https://codeforces.com/contest/1899/problem/A

# Problem: Determine winner of a game where players alternate adding/subtracting 1 from n
# Algorithm: Mathematical analysis of modulo 3 patterns
# Time Complexity: O(1) per test case
# Space Complexity: O(1)

# Game rules:
# - Vanya starts first
# - Players can add or subtract 1 each turn
# - Vanya wins if number becomes divisible by 3 after his move
# - If 10 moves pass without Vanya winning, Vova wins
# Analysis shows pattern based on n % 3

for n in [*open(0)][1:]:  # Read all lines except first (test count), process each number
    print("SFeicrosntd"[int(n) % 3 > 0 :: 2])  # Use modulo to determine winner (0=Second, 1=First, 2=First)


# https://github.com/VaHiX/codeForces/