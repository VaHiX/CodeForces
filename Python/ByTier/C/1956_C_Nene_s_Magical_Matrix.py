# Problem: CF 1956 C - Nene's Magical Matrix
# https://codeforces.com/contest/1956/problem/C

"""
Purpose: To solve the problem of maximizing the sum of elements in an n x n matrix 
         using specific operations on rows and columns. The operations allow setting 
         a row or column to a permutation of numbers from 1 to n.

Algorithms/Techniques: 
- Greedy approach to maximize sum by filling each row and column optimally
- For each row/column, assign a permutation to achieve maximum value.
- For a row/column, to maximize sum, assign the largest unused number at each position.

Time Complexity: O(n^2) - generating permutations and printing operations
Space Complexity: O(n) - storing a permutation of size n

The solution uses a pattern where:
- First, assign the largest values to the last rows/columns.
- Then, for each row/column, repeat it twice to get maximum utility.
"""

T = int(input())

for t in range(T):
    n = int(input())

    # Calculate the maximum sum that can be achieved
    # This is based on a greedy approach where we aim to fill the matrix with highest values
    suma = 0
    for i in range(1, n + 1):
        suma += n**2 - (i - 1) ** 2

    print(suma, 2 * n)

    # Create a string of permutation 1, 2, ..., n
    r = ""
    for j in range(1, n + 1):
        r += str(j) + " "
    r = r[:-1]  # Remove trailing space
    pos = len(r) - 1  # Unused variable in this context

    # For each row/column, apply operations twice (once for row, once for column)
    for i in range(1, n + 1):
        # Operation type 1: assign permutation to row (n-i+1)th row
        print(1, n - i + 1, r)
        # Operation type 2: assign permutation to column (n-i+1)th column
        print(2, n - i + 1, r)


# https://github.com/VaHiX/CodeForces/