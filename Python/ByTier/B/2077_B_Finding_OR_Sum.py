# Problem: CF 2077 B - Finding OR Sum
# https://codeforces.com/contest/2077/problem/B

"""
B. Finding OR Sum
Interactive problem to determine two hidden integers x and y using at most 2 queries.

Algorithms/Techniques:
- Bit manipulation and binary representation
- Query-based deduction using bitwise OR operations
- Systematic bit-by-bit reconstruction of values

Time Complexity: O(1) - constant time for each test case as we only make 2 queries and process fixed-size data (30 bits)
Space Complexity: O(1) - constant space used regardless of input size

The approach uses two masks A and B to isolate even and odd bits respectively,
allowing us to reconstruct the hidden values bit by bit.
"""

import sys

input = lambda: sys.stdin.readline()[:-1]
ni = lambda: int(input())
na = lambda: list(map(int, input().split()))
yes = lambda: print("yes")
Yes = lambda: print("Yes")
YES = lambda: print("YES")
no = lambda: print("no")
No = lambda: print("No")
NO = lambda: print("NO")

# Create masks to isolate even and odd bits
A = 0  # mask for even bits (0, 2, 4, ...)
B = 0  # mask for odd bits (1, 3, 5, ...)
m = 30

# Build A mask with 1s at even positions
for i in range(0, m, 2):
    A |= 1 << i

# Build B mask with 1s at odd positions
for i in range(1, m, 2):
    B |= 1 << i


def ask(x):
    # Query the judge for (x | x) + (x | y)
    print(x, flush=True)
    y = ni()
    return y


for _ in range(ni()):
    # First query: get l = A | x + A | y
    l = ask(A)
    # Second query: get r = B | x + B | y
    r = ask(B)
    
    # Initialize array to store reconstructed bits
    f = [0] * m
    
    # Process even bits of l (subtract 2<<i from l and extract bits)
    for i in range(0, m, 2):
        l -= 2 << i  # Adjust value to get actual bits

    # Process odd bits of r  
    for i in range(1, m, 2):
        r -= 2 << i  # Adjust value to get actual bits

    # Extract bit patterns from adjusted l and r
    for i in range(1, m, 2):  # For odd indices: store l>>i&3 into f[i]
        f[i] = l >> i & 3
    
    for i in range(0, m, 2):  # For even indices: store r>>i&3 into f[i]
        f[i] = r >> i & 3

    # Print result marker
    print("!", flush=True)
    
    # Read the target number m
    p = ni()
    
    # Reconstruct the answer using the determined bit pattern
    ans = 0
    for i in range(m):
        if p >> i & 1:  # If bit i of p is set, add 2 << i to ans
            ans += 2 << i
        else:  # Else, add f[i] << i to ans
            ans += f[i] << i
    
    print(ans, flush=True)


# https://github.com/VaHiX/codeForces/