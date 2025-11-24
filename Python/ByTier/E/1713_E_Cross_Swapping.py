# Problem: CF 1713 E - Cross Swapping
# https://codeforces.com/contest/1713/problem/E

"""
Algorithm: Union-Find (Disjoint Set Union) with Matrix Symmetry
Purpose: Find the lexicographically smallest matrix by swapping symmetric elements
Technique:
- For each pair (i,j) where i < j, compare A[i][j] and A[j][i]
- If A[i][j] < A[j][i], add an edge to group i and j in union-find
- If A[i][j] > A[j][i], add an edge to group j and i in union-find  
- If A[i][j] == A[j][i], no edge added
- After processing, for each group, swap rows and columns to minimize result
Time Complexity: O(n^2 * α(n)) where α is inverse Ackermann function
Space Complexity: O(n)
"""

import sys

input = sys.stdin.buffer.readline


def find_root(root_dict, x):
    # Find root of x with path compression
    L = []
    while x != root_dict[x]:
        L.append(x)
        x = root_dict[x]
    for y in L:
        root_dict[y] = x
    return x


def process(A):
    n = len(A)
    # Initialize Union-Find structure (size 2*n to allow pairing)
    root_dict = [i for i in range(2 * n)]
    
    # Process all pairs (i,j) where i < j
    for i in range(n):
        for j in range(i + 1, n):
            if A[i][j] < A[j][i]:
                edge_type = 0
            elif A[i][j] > A[j][i]:
                edge_type = 1
            else:
                edge_type = 2  # Equal values, no operation needed
            
            if edge_type < 2:
                # Find root of i and j in the Union-Find
                i1 = find_root(root_dict, i)
                j1 = find_root(root_dict, j)
                
                # Compute corresponding indices for row/col swap
                if i1 >= n:
                    i2 = i1 - n
                else:
                    i2 = i1 + n
                if j1 >= n:
                    j2 = j1 - n
                else:
                    j2 = j1 + n
                
                # Union operation based on comparison result
                if j1 not in [i1, i2]:
                    if edge_type == 0:
                        root_dict[j1] = i1
                        root_dict[j2] = i2
                    elif edge_type == 1:
                        root_dict[j1] = i2
                        root_dict[j2] = i1
                        
    # Apply swaps for each root group
    for i in range(n):
        if find_root(root_dict, i) >= n:  # If in column group
            # Swap row i with column i (in-place)
            for k in range(n):
                A[i][k], A[k][i] = A[k][i], A[i][k]
    
    # Output the final matrix
    for row in A:
        row = " ".join(map(str, row))
        sys.stdout.write(f"{row}\n")


t = int(input())
for i in range(t):
    n = int(input())
    A = []
    for j in range(n):
        row = [int(x) for x in input().split()]
        A.append(row)
    process(A)


# https://github.com/VaHiX/CodeForces/