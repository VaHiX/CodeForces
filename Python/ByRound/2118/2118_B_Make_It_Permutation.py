# Problem: CF 2118 B - Make It Permutation
# https://codeforces.com/contest/2118/problem/B

"""
B. Make It Permutation

Purpose:
This code solves the problem of transforming an n×n matrix where A[i][j] = j into a matrix such that every column 
contains a permutation of integers from 1 to n. The allowed operation is reversing any subarray in any row.

Algorithm/Techniques:
- For each row i (from 1 to n), we perform two operations:
    1. Reverse the subarray from column 1 to column i (i.e., A[i][1..i])
    2. Reverse the subarray from column i to column n (i.e., A[i][i..n])
- This ensures that after applying these operations, each column will contain a permutation of [1, 2, ..., n].

Time Complexity:
O(n^2) - We perform at most 2*n operations, and each operation is a reverse on a subarray of size up to n.

Space Complexity:
O(1) - No extra space used apart from input/output.

"""

t = int(input())
for _ in range(t):
    n = int(input())
    print(2 * n - 1)  # Total number of operations needed
    
    # Perform operations for rows 1 to n-1
    for i in range(1, n):
        # Reverse subarray from column 1 to column i in row i
        print(i, 1, i)
        # Reverse subarray from column i to column n in row i
        print(i, i + 1, n)
    
    # For the last row, reverse entire row (from column 1 to n)
    print(n, 1, n)


# https://github.com/VaHiX/CodeForces/