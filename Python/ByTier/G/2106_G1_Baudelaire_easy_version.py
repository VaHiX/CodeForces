# Problem: CF 2106 G1 - Baudelaire (easy version)
# https://codeforces.com/contest/2106/problem/G1

"""
Interactive problem to determine values of nodes in a tree.

Algorithms/Techniques:
- Use of XOR-based randomization for query obfuscation
- Query type 1: Sum of path values from root to specified nodes
- Query type 2: Toggle value of a node
- Strategy:
    - First query to get sum of path values from root to all nodes (including root itself)
    - Use toggle operations to infer the individual node values
    - Handle special cases for root node value determination

Time Complexity: O(n^2) worst case due to querying each node multiple times and potential flips.
Space Complexity: O(n) for storing node values and intermediate results.

"""

import sys
from random import randint
from time import time_ns

input = lambda: sys.stdin.readline().rstrip()
inp = lambda: list(map(int, input().split()))
I = lambda: int(input())
xor = randint(1, 2**32 - 1) ^ time_ns()  # XOR-based randomization


def ask(u):
    print("?", 1, 1, u)  # Query type 1 with one node
    sys.stdout.flush()
    return int(input())


def flip(u):
    print("?", 2, u)  # Query type 2 to toggle a node
    sys.stdout.flush()


def ans(o):
    print("!", *o)  # Output the final answer with all node values
    sys.stdout.flush()


for _ in range(I()):
    n = I()
    for _ in range(n - 1):
        __ = input()  # Read tree edges but do nothing with them
    v = ask(1)  # Initial query to get value related to path sums
    o = [-2] * n  # Initialize output array with placeholder values
    
    if abs(v) == 1:
        # If the root sum is +/-1, we know root value directly
        o[0] = v
        for i in range(1, n):
            # For remaining nodes, compute difference to determine their value
            o[i] = ask(i + 1) - v
        ans(o)
    elif v:
        # If v is not 0 and not +/-1, we use toggle strategy
        o[0] = 1 if v == 2 else -1
        flip(1)  # Toggle root to infer actual value
        o[0] = -o[0]  # Adjust based on toggle effect
        for i in range(1, n):
            # Recompute values after toggle
            o[i] = ask(i + 1)
        ans(o)
    else:
        # v is 0, which implies a more complex case requiring careful handling.
        flip(1)  # Toggle to test what happens with root
        o[0] = 1 if ask(1) == -2 else -1  # Determine value from new path sum
        flip(1)  # Flip back to restore original state
        for i in range(1, n):
            # Compute remaining values based on previous knowledge
            o[i] = ask(i + 1)
        ans(o)


# https://github.com/VaHiX/CodeForces/