# Problem: CF 1713 F - Lost Array
# https://codeforces.com/contest/1713/problem/F

"""
Reconstructs the original array 'a' from the given last column of matrix 'b'.
The matrix 'b' is constructed using the rules:
- b[i][0] = 0 for all i
- b[0][i] = a[i] for all i
- b[i][j] = b[i][j-1] XOR b[i-1][j] for i,j > 0

This implementation uses a technique based on XOR properties and bit manipulation.
The approach is to reverse the process of building the matrix by propagating XORs
through levels using a specific order and bit masks to recover elements of array 'a'.

Time Complexity: O(n * log n)
Space Complexity: O(n)
"""

a = [*map(int, [*open(0)][1].split())]
n = len(a)
for k in 0, 1:  # Iterate over two phases to process bits
    for i in range(19):  # Process up to 19 bits (since values < 2^30)
        z = 1 << i  # Mask for current bit position
        for j in range(n):  # Iterate through all indices
            if j & z:  # If bit i is set in index j
                a[j - k * z] ^= a[j + k * z - z]  # XOR operation to update values
print(*reversed(a))  # Output the reconstructed array in reverse order


# https://github.com/VaHiX/CodeForces/