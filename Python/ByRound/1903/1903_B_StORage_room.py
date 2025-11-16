# Problem: CF 1903 B - StORage room
# https://codeforces.com/contest/1903/problem/B

"""
Code Purpose:
This code solves the problem of reconstructing an array from a symmetric matrix where each element M[i][j] equals a[i] | a[j] for i != j.
The approach is based on the idea that for any row i, the value at position (i, j) where j != i is equal to a[i] | a[j].
By exploiting the XOR property and symmetric structure, we can compute potential values of a[i] by intersecting all other elements in the same row.
We also verify the consistency of the array by checking previous entries against computed values.

Algorithms/Techniques:
- Bitwise operations (OR, AND)
- Matrix symmetry property exploitation
- Linear scan with verification

Time Complexity: O(n^2) per test case, where n is the size of the matrix.
Space Complexity: O(n) for storing the result array.
"""

for t in range(1, int(input()) + 1):
    n = int(input())

    ans = []
    flag = True
    if n == 1:
        print("YES")
        print(input())
        continue
    for i in range(n):
        arr = [int(x) for x in input().split()]
        if i == 0:
            val = arr[1]  # Start with first non-diagonal element in first row
        else:
            val = arr[0]  # Start with first non-diagonal element in this row
        # Intersect all other non-diagonal elements in the current row to get candidate a[i]
        for j in range(n):
            if i != j:
                val &= arr[j]
        # Check if this computed value is consistent with already computed values
        for j in range(i):
            if arr[j] != val | ans[j]:  # Check constraint a[i] | a[j] == M[i][j]
                flag = False
        ans.append(val)
    if not flag:
        print("NO")
    else:
        print("YES")
        print(*ans)


# https://github.com/VaHiX/CodeForces/