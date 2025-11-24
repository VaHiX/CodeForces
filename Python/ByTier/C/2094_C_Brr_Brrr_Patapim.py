# Problem: CF 2094 C - Brr Brrr Patapim
# https://codeforces.com/contest/2094/problem/C

"""
C. Brr Brrr Patapim

Purpose:
This code recovers a permutation of 2*n integers from an n×n grid where each element G[i][j] corresponds to the (i+j)-th element of the permutation.
The approach uses the fact that elements along diagonals (i + j = constant) can be used to deduce values in the permutation.

Algorithms/Techniques:
- Grid traversal with diagonal grouping
- Set operations to find missing elements
- Reconstruction of permutation using known values

Time Complexity: O(n^2) per test case (for reading grid and processing)
Space Complexity: O(n^2) for storing the grid and intermediate data structures

Input Format:
- First line: number of test cases t
- For each test case:
  - First line: n (size of grid)
  - Next n lines: n integers representing the grid G[i][j]

Output Format:
- For each test case: 2*n integers representing the permutation p[1] to p[2n]
"""

t = int(input())  # Read number of test cases
for _ in range(t):
    n = int(input())  # Read size of the grid
    l = list(map(int, input().split()))  # Read first row of the grid
    
    # Process remaining rows of the grid
    for _ in range(n - 1):
        # Append last element of each subsequent row to the list 'l'
        l.append(int(input().split()[-1]))
    
    # Find missing numbers in range [1, 2*n] that are not present in list 'l'
    missing = set(range(1, 2 * n + 1)) - set(l)
    
    # Add missing elements to the front of the list
    l = list(missing) + l
    
    # Print the result as space-separated integers
    print(" ".join(map(str, l)))


# https://github.com/VaHiX/codeForces/