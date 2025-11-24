# Problem: CF 2072 F - Goodbye, Banker Life
# https://codeforces.com/contest/2072/problem/F

"""
F. Goodbye, Banker Life

Purpose:
This code computes the n-th row of a special triangular array called the "Great Magical Triangle".
Each element in the triangle is generated based on previous elements using XOR operations,
with specific rules for the first and last elements of each row.

The triangle follows these recurrence relations:
- T[i][1] = T[i-1][1] (first element of row i is same as first element of row i-1)
- T[i][j] = T[i-1][j-1] XOR T[i-1][j] (middle elements are XOR of adjacent elements from previous row)
- T[i][i] = T[i-1][i-1] (last element of row i is same as last element of row i-1)

Time Complexity: O(n) for each test case, where n is the row number.
Space Complexity: O(n) to store and output the n-th row.

Algorithms/Techniques:
- Dynamic Programming with bit manipulation
- XOR operation properties

"""

t = int(input())
for z in range(t):
    n, k = map(int, input().split())
    # Generate the n-th row using a list comprehension.
    # For each index i from 0 to n-1:
    #   if (i & (n - 1)) == i, then use k (this condition is true only when i = 0 or i = n-1)
    #   otherwise set it to 0
    ll = [k if (i & (n - 1)) == i else 0 for i in range(n)]
    print(" ".join(map(str, ll)))


# https://github.com/VaHiX/codeForces/