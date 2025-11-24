# Problem: CF 2108 B - SUMdamental Decomposition
# https://codeforces.com/contest/2108/problem/B

"""
B. SUMdamental Decomposition
time limit per test1 second
memory limit per test256 megabytes

Algorithm/Techniques:
- Bit manipulation and greedy approach
- The key idea is to use the properties of XOR and bit decomposition to minimize the sum
- For n=1, only valid x=0 has a solution; otherwise impossible
- For n>1, we try to construct an array with minimal sum using the bits of x:
    - If n <= number of 1-bits in x, we can distribute those bits among n elements
    - If n > number of 1-bits in x, we need to add extra zeros or ones depending on parity
    - Special handling of small cases like n=2 and x=1

Time Complexity: O(1) per test case (constant time operations)
Space Complexity: O(1) (only using fixed amount of variables)
"""

import sys

input = sys.stdin.buffer.readline
for _ in range(int(input())):
    n, x = map(int, input().split())
    bits = bin(x).count("1")  # Count number of 1-bits in x
    
    if n <= bits:
        # We can form a valid array with sum equal to x itself
        print(x)
    elif (n - bits) % 2 == 0:
        # Even difference: we can add pairs of 1s without increasing sum significantly
        print(x + n - bits)
    else:
        # Odd difference: adjust to preserve minimality, with special case for x=1
        if x > 1:
            # If x is greater than 1, we can make one more adjustment
            print(x + n - bits + 1)
        elif x == 1:
            # Special case when x = 1 and n = 2 (minimum valid case for even n >= 2)
            print(n + 3)
        else:
            # x == 0, n > 1 => check if array can be formed with sum -1
            print(-1 if n == 1 else n + 3)


# https://github.com/VaHiX/codeForces/