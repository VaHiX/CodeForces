# Problem: CF 1869 C - Fill in the Matrix
# https://codeforces.com/contest/1869/problem/C

"""
Code purpose: This solution aims to maximize the "beauty" of a matrix filled with permutations of length m.
The beauty is defined as the MEX (minimum excludant) of all column values, where each column value is the MEX of its column entries.
The algorithm constructs a matrix such that the resulting column MEXs result in a maximum possible MEX value for the row of column MEXs.

Algorithms/Techniques:
- Construct a matrix with rows as permutations of [0, 1, ..., m-1] arranged cyclically to minimize repetition.
- For small cases (m=1), a trivial solution is used.
- Key idea is to cycle through permutations to distribute values such that column MEXs have a maximized MEX across them.

Time Complexity: O(n * m) - since we are filling a matrix of size n x m.
Space Complexity: O(n * m) - for storing the matrix.
"""

def main():
    t = int(input())
    r = [str(solution(i, t)) for i in range(t)]

    print("\n".join(r))


def solution(ti, tn):
    n, m = map(int, input().split())

    if m == 1:
        # For m=1, we just put 0 in every cell to have column MEX = 1, resulting in beauty 0.
        return "0" + ("\n" + "0") * n

    xx = list(range(m))  # Initial permutation [0, 1, ..., m-1]
    mm = [[0] * m for _ in range(n)]  # Initialize matrix

    # Determine how many rows we can fill with the initial permutation before cycling
    d = max(0, n - m + 1)  # Number of rows that will be filled with the same permutation

    # Fill first d rows with same permutation
    for i in range(d):
        mm[i] = xx.copy()  # Copy the initial permutation

    # Fill the remaining rows with cyclically shifted permutations
    for i in range(d, n):
        mm[i] = [xx[(j + i - d) % m] for j in range(m)]  # Shift permutation cyclically

    # Return the maximum possible beauty (which is min(n+1, m)) and the matrix
    return "\n".join([str(min(m, n + 1)), *(" ".join(map(str, row)) for row in mm)])


main()


# https://github.com/VaHiX/CodeForces/