# Problem: CF 1934 D2 - XOR Break --- Game Version
# https://codeforces.com/contest/1934/problem/D2

"""
Game theory problem involving XOR operations and binary representation.
The key idea is to use the number of set bits (popcount) to determine winning/losing positions.
If the number of set bits in n is even, the first player (Alice) is in a winning position.
Otherwise, the second player (Bob) is in a winning position.

Algorithm:
1. For each test case, determine if n has even or odd number of set bits.
   - If even, Alice plays first and wins.
   - If odd, Alice plays second.
2. If Alice plays first, she makes a move that ensures an even number of set bits.
3. For subsequent moves, Alice always splits the current number into two parts such that
   one part is a power of 2 and the other is the remainder.
4. This way, Alice keeps the number of set bits even for her turn and forces 
   Bob to make moves with odd number of set bits, leading to eventual loss.

Time Complexity: O(log n) per test case
Space Complexity: O(1)
"""

import sys

input = sys.stdin.readline
from sys import stdout

tt = int(input())
for _ in range(tt):
    n = int(input())
    if n.bit_count() % 2 == 0:
        # If number of set bits is even, Alice plays first and has winning strategy
        print("first")
        stdout.flush()
    else:
        # If number of set bits is odd, Alice plays second
        print("second")
        stdout.flush()
        # Read Bob's move
        p1, p2 = [int(_) for _ in input().split()]
        if p1 == -1:
            sys.exit()
        if p1 == 0:
            continue
        # Determine which value Bob chose based on set bits
        if p1.bit_count() % 2 == 0:
            n = p1
        else:
            assert p2.bit_count() % 2 == 0
            n = p2
    # Alice's turn continues indefinitely until game ends
    while True:
        # Split n into a power of 2 and its complement to maintain even number of set bits
        power_of_2 = 1 << (n.bit_length() - 1)
        print(power_of_2, n - power_of_2)
        stdout.flush()
        # Read Bob's response
        p1, p2 = [int(_) for _ in input().split()]
        if p1 == -1:
            sys.exit()
        if p1 == 0:
            break
        # Again choose the value with even number of set bits to continue the strategy
        if p1.bit_count() % 2 == 0:
            n = p1
        else:
            assert p2.bit_count() % 2 == 0
            n = p2


# https://github.com/VaHiX/CodeForces/