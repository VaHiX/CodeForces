# Problem: CF 2081 F - Hot Matrix
# https://codeforces.com/contest/2081/problem/F

"""
F. Hot Matrix
time limit per test4 seconds
memory limit per test512 megabytes

Piggy Zhou loves matrices, especially those that make him get excited, called hot matrix.
A hot matrix of size n×n can be defined as follows. Let a i,j denote the element in the i-th row,
j-th column (1≤i,j≤n). Each column and row of the matrix is a permutation of all numbers from 0 to n−1.
For each pair of indices i, j, such that 1≤i,j≤n,
a i,j + a i,n−j+1 = n−1.
For each pair of indices i, j, such that 1≤i,j≤n,
a i,j + a n−i+1,j = n−1.
All ordered pairs (a i,j , a i,j+1 ), where 1≤i≤n, 1≤j<n, are distinct.
All ordered pairs (a i,j , a i+1,j ), where 1≤i<n, 1≤j≤n, are distinct.

Algorithm:
The solution uses an explicit construction method for even n >= 2 to generate the matrix.
For odd n > 1, no valid matrix exists due to the constraints.
For n = 1, returns a trivial 0 matrix.

Time Complexity: O(n^2)
Space Complexity: O(n^2)

"""

def generateMatrix(n):
    if n == 1:
        return "YES\n0"
    elif n % 2 == 1:
        return "NO"
    else:
        # Initialize matrix with zeros (1-indexed)
        matrix = [[0 for j in range(n + 1)] for i in range(n + 1)]
    
    # Fill the matrix using a block-based approach
    for i in range(0, n, 2):  # Process pairs of rows
        # First part: fill diagonal from top-left to bottom-right
        for j in range(1, i + 2):
            # Set value based on index and parity
            matrix[j][i + 2 - j] = i + (j % 2 == 0)
        
        # Second part: fill anti-diagonal from top-right to bottom-left  
        for j in range(n - i, n + 1):
            matrix[j][2 * n - i - j] = i + (j % 2 == 1)
        
        # Third part: fill diagonal from top-left to bottom-right (second section) 
        for j in range(1, n - i):
            matrix[j][i + 1 + j] = i + (j % 2 == 1)
        
        # Fourth part: fill anti-diagonal from bottom-left to top-right
        for j in range(i + 2, n + 1):
            matrix[j][j - i - 1] = i + (j % 2 == 0)
    
    res = ["YES"]  # Result starts with YES
    for i in range(1, n + 1):
        # Construct each row from the matrix data
        res.append(" ".join(str(matrix[i][j]) for j in range(1, n + 1)))
    
    # Join all lines into final output string
    return "\n".join(res)


t = int(input())
for _ in range(t):
    n = int(input())
    print(generateMatrix(n))


# https://github.com/VaHiX/codeForces/