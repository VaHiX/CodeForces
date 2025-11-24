# Problem: CF 2078 E - Finding OR Sum
# https://codeforces.com/contest/2078/problem/E

# Flowerbox: 
# Problem: Finding OR Sum
# Purpose: This code solves an interactive problem where two hidden integers x and y (0 <= x, y < 2^30) are to be discovered using at most two queries of the form (n | x) + (n | y). 
# The goal is then to compute (m | x) + (m | y) for a given m.
# Algorithms/Techniques:
#   - Use bitwise operations and properties of OR to deduce values
#   - Query with specific masks to isolate bits
#   - Time Complexity: O(1) per test case (constant number of operations)
#   - Space Complexity: O(1) (only using fixed-size variables)

for _ in range(int(input())):
    M = (1 << 30) - 1  # Mask all 30 bits to 1
    ns = sum(1 << i for i in range(0, 30, 2))  # Sum of even bit positions (0, 2, 4, ..., 28)
    nt = sum(1 << i for i in range(1, 30, 2))  # Sum of odd bit positions (1, 3, 5, ..., 29)
    print(ns)  # Query using even bit mask
    a = int(input())  # Store result of query with ns
    print(nt)  # Query using odd bit mask
    b = int(input())  # Store result of query with nt
    print("!")  # Signal end of queries
    m = int(input())  # Get the target value of m
    s = a + b - 2 * M  # Compute s = (ns | x) + (ns | y) + (nt | x) + (nt | y) - 2 * M, which gives us x + y
    r = s  # Initialize result with the computed sum of x and y
    for i in range(30):  # Iterate through all 30 bits
        if m & (1 << i):  # If bit i is set in m
            # Extract the effect of this bit on either x or y using precomputed values
            d = ((a - s) >> i) & 3 if i % 2 == 0 else ((b - s) >> i) & 3  # Get contribution of bits to determine mask
            r += (1 << i) * d  # Add the computed value to result
    print(r)  # Output final answer for (m | x) + (m | y)


# https://github.com/VaHiX/codeForces/