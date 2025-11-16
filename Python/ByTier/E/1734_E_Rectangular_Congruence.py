# Problem: CF 1734 E - Rectangular Congruence
# https://codeforces.com/contest/1734/problem/E

"""
Matrix Construction with Rectangular Congruence

Algorithm:
- The solution uses a specific formula to construct the matrix elements.
- For each element a[i][j], we compute: (i * j + b[i] - i * i) % n
- This approach ensures that the diagonal elements match the given values b[i]
- The formula helps in satisfying the constraint that for any 2x2 submatrix,
  the sum of the diagonal elements is not congruent to the sum of the anti-diagonal elements modulo n.
- This works particularly well when n is prime due to the properties of modular arithmetic.

Time Complexity: O(n^2) - We iterate through all n*n elements of the matrix.
Space Complexity: O(n^2) - We store the n*n matrix.
"""

n = int(input())
b = list(map(int, input().split()))
l = []
for i in range(n):
    l1 = []
    for j in range(n):
        # Formula to construct matrix elements ensuring the constraints
        l1.append((i * j + b[i] - i * i) % n)
    l.append(l1)
for i in l:
    print(*i)


# https://github.com/VaHiX/CodeForces/