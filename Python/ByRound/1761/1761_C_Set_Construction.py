# Problem: CF 1761 C - Set Construction
# https://codeforces.com/contest/1761/problem/C

"""
Set Construction Problem

This problem asks us to construct n sets such that the relationship between sets
matches a given binary matrix. Specifically, b[i][j] = 1 if and only if A_i is a proper subset of A_j.

Algorithm:
1. Initialize each set A_i with the element i+1 (1-indexed).
2. For each pair (i, j) where b[i][j] = 1, add element i+1 to set A_j.
   This ensures that if A_i ⊂ A_j, then A_j contains all elements of A_i plus possibly more.
3. Output each set in the required format.

Time Complexity: O(n^2) per test case due to nested loops for processing the matrix.
Space Complexity: O(n^2) for storing the matrix and O(n^2) for the sets in worst case.

The approach leverages the transitive property of subset relationships:
- If A_i ⊂ A_j and A_j ⊂ A_k, then A_i ⊂ A_k.
- By adding elements based on the matrix entries, we build the required subset relationships.
"""

T = int(input())

for _ in range(T):
    n = int(input())
    mat = [input() for i in range(n)]
    # Initialize each set with its own index (1-indexed)
    ans = [[i + 1] for i in range(n)]
    # Process the matrix to determine subset relationships
    for i in range(n):
        for j in range(n):
            if mat[i][j] == "1":
                # If A_i is a proper subset of A_j, add i+1 to A_j
                ans[j].append(i + 1)

    for i in ans:
        print(len(i), *i)


# https://github.com/VaHiX/CodeForces/