# Problem: CF 1919 A - Wallet Exchange
# https://codeforces.com/contest/1919/problem/A

"""
Code Purpose:
This code solves the Wallet Exchange game problem where Alice and Bob take turns removing coins from their wallets,
with the option to swap wallets before each move. The game ends when a player cannot make a move, and the winner is determined
based on optimal play. The solution uses a mathematical approach to determine the winner without simulating the game.

Algorithms/Techniques:
- Mathematical analysis of game states
- Parity check (odd/even sum of coins)

Time Complexity:
O(1) - The solution performs a constant number of operations regardless of the input size.

Space Complexity:
O(1) - Only a constant amount of extra space is used.

"""

def sol():
    a, b = map(int, input().split())
    # If the total number of coins is odd, Alice wins; otherwise, Bob wins
    print(["Bob", "Alice"][(a + b) % 2])


tn = int(input())
for i in range(tn):
    sol()


# https://github.com/VaHiX/CodeForces/