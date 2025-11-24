# Problem: CF 1673 F - Anti-Theft Road Planning
# https://codeforces.com/contest/1673/problem/F

"""
Code Purpose:
This code solves an interactive problem where we need to assign road lengths in a grid such that we can uniquely determine the locations of thefts based on XOR values returned by a tracker. 

The approach uses a specific encoding scheme:
1. Assign horizontal road lengths based on bit manipulation using the function 'gan'
2. Assign vertical road lengths using similar bit manipulation 
3. For each query, decode the XOR result to determine the position of the theft

Algorithms/Techniques:
- Bit manipulation and XOR properties
- Encoding scheme to uniquely identify positions via XOR paths
- Grid traversal and decoding based on bit positions

Time Complexity:
- Preprocessing: O(n^2) for assigning road lengths
- Query processing: O(k * log(max_value)) where max_value is around 2^20 for typical inputs
- Overall: O(n^2 + k * log(max_value))

Space Complexity:
- O(n^2) for storing road lengths
- O(1) additional space for processing queries
"""

n, k = map(int, input().split())


def gan(x):
    # Function to transform a number using base-4 representation
    t = 1
    r = 0
    while x > 0:
        r += x % 2 * t  # Extract least significant bit and multiply by power of 4
        t *= 4          # Move to next power of 4
        x //= 2         # Shift x right by 1 bit
    return r


s = 0
# Assign horizontal road lengths
for i in range(n):
    a = []
    for j in range(1, n):
        # For each horizontal edge, use bit manipulation
        a.append(gan(j & -j))  # j & -j gives the lowest set bit of j
    print(*a)
    s += sum(a)

# Assign vertical road lengths  
for i in range(1, n):
    a = []
    for j in range(n):
        # For each vertical edge, use bit manipulation scaled by 2
        a.append(gan(i & -i) * 2)  # i & -i gives lowest set bit of i, scaled by 2
    print(*a)
    s += sum(a)

# Process queries
x = 0
y = 0
for i in range(k):
    z = int(input())
    # Decode the XOR value to determine the position of the theft
    for j in range(10):  # Up to 10 bits should be sufficient for small grids
        if z >> j & 1:  # If j-th bit is set
            if j & 1:   # If j is odd
                # XOR with a mask to decode vertical component
                x ^= (1 << ((j // 2) + 1)) - 1
            else:       # If j is even
                # XOR with a mask to decode horizontal component  
                y ^= (1 << ((j // 2) + 1)) - 1
    # Output the decoded position (1-indexed)
    print(x + 1, y + 1, flush=True)


# https://github.com/VaHiX/CodeForces/