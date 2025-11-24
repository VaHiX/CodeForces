# Problem: CF 1070 A - Find a Number
# https://codeforces.com/contest/1070/problem/A

"""
A. Find a Number
time limit per test
3 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output
You are given two positive integers d and s. Find minimal positive integer n which is divisible by d and has sum of digits equal to s.
Algorithm: BFS (Breadth-First Search)
Time Complexity: O(d * s)
Space Complexity: O(d * s)

The problem is solved using BFS where each state represents (digit_sum % d, digit_sum) 
to efficiently explore all possible combinations of digits that satisfy the constraints.
"""

from collections import deque
from sys import exit

d, s = map(int, input().split())
p = d * (s + 1) * [None]  # Array to store parent information for path reconstruction
q = deque([0])  # BFS queue initialized with state 0
p[0] = -1  # Mark initial state as visited

while q:
    x, z = divmod(q.popleft(), d)  # x is digit sum so far, z is (digit_sum % d)
    if x == s and not z:  # Found a valid number with sum s and divisible by d
        y = x * d + z  # reconstruct the final state index
        ans = ""  # Build the answer string
        while p[y] != -1:  # Backtrack from final state to root
            ans += str(p[y][0])  # Append digit
            y = p[y][1]  # Move to parent state
        print(ans[::-1])  # Reverse and print the result
        exit(0)
    for i in range(10):  # Try appending each digit (0-9)
        nx_digits = x + i  # New digit sum
        nx_modulo = (10 * z + i) % d  # New modulo value (shift left and add digit, then mod d)
        nx = nx_digits * d + nx_modulo  # New state index
        if nx_digits <= s and not p[nx]:  # If state is valid and unvisited
            p[nx] = (i, x * d + z)  # Store parent (digit, previous_state_index)
            q.append(nx)  # Add to BFS queue

print(-1)  # No such number found


# https://github.com/VaHiX/codeForces/