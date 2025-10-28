# Problem: CF 2033 B - Sakurako and Water
# https://codeforces.com/contest/2033/problem/B

# B. Sakurako and Water
# Purpose: Given an n×n matrix where negative values represent lakes, determine the minimum number of operations
#          to make all values non-negative. Each operation increases the height of elements on a main diagonal
#          of a square submatrix by 1.
# Algorithm: Use a difference array technique over the diagonals to efficiently compute the required number
#            of operations. The key insight is that for each element in the matrix, we need to know how many
#            times it was covered by an operation.
# Time Complexity: O(n^2) per test case
# Space Complexity: O(n) for the difference array

for _ in range(int(input())):
    n = int(input())
    a = [0] * (2 * n)  # Difference array for diagonals, indexed from 0 to 2*n-1
    for i in range(n):
        line = list(map(int, input().split()))
        for j in range(n):
            # Indexing the diagonal: diagonal id = n + i - j
            # We store the negative of the value since we want to know how much we need to increase it
            a[n + i - j] = max(a[n + i - j], -line[j])
    print(sum(a))


# https://github.com/VaHiX/codeForces/