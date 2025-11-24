# Problem: CF 1972 B - Coin Games
# https://codeforces.com/contest/1972/problem/B

"""
Code Purpose:
This code solves the Coin Games problem where two players (Alice and Bob) play a game on a circular arrangement of coins. 
Each coin is either facing up (U) or down (D). Players take turns removing a facing-up coin and flipping its adjacent coins.
The game ends when no more moves can be made. The winner is determined based on optimal play.
The key insight is that the game's outcome depends only on the parity (odd/even) of the number of facing-up coins.
If the number of U's is odd, Alice wins; otherwise, Bob wins.

Algorithms/Techniques:
- Simple parity check based on the count of 'U' coins.
- No complex game theory or dynamic programming needed due to the problem's properties.

Time Complexity: O(n) where n is the length of the string s, because we need to count the number of 'U's.
Space Complexity: O(n) for storing the string s and the list representation of s.

"""
t = int(input())
for _ in range(t):
    n = int(input())
    s = str(input())
    ct_1 = list(s).count("U")  # Count the number of facing-up coins
    print("YES" if ct_1 % 2 == 1 else "NO")  # Alice wins if count of U is odd, else Bob wins


# https://github.com/VaHiX/CodeForces/