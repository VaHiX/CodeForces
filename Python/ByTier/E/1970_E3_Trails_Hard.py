# Problem: CF 1970 E3 - Trails (Hard)
# https://codeforces.com/contest/1970/problem/E3

"""
Code Purpose:
This code solves a dynamic programming problem involving trail combinations in a graph where cabins are connected to a central lake by short and long trails. The solution uses matrix exponentiation to compute the number of valid trail sequences over n days, starting from cabin 1.

Algorithms/Techniques:
- Matrix exponentiation for fast computation of linear recurrence relations
- Dynamic programming with state transitions encoded in a 2x2 matrix
- Modular arithmetic for handling large numbers

Time Complexity: O(m + log(n))
Space Complexity: O(1)

The problem models transitions between states using a 2x2 matrix, and the matrix is raised to the power (n-1) using fast exponentiation.
"""

MOD = 10**9 + 7


def main():
    import sys

    data = sys.stdin.read().split()
    m = int(data[0])
    n = int(data[1])
    s = list(map(int, data[2 : 2 + m]))
    l_list = list(map(int, data[2 + m : 2 + 2 * m]))
    S_sum = sum(s) % MOD
    L_sum = sum(l_list) % MOD
    p = sum(s_i * s_i for s_i in s) % MOD
    q = sum(s_i * l_i for s_i, l_i in zip(s, l_list)) % MOD
    r = sum(l_i * l_i for l_i in l_list) % MOD
    v1_x = (S_sum + L_sum) % MOD
    v1_y = S_sum % MOD
    s1 = s[0]
    l1 = l_list[0]
    if n == 1:
        result = (v1_x * s1 + v1_y * l1) % MOD
    else:
        M = [[(p + q) % MOD, (q + r) % MOD], [p, q]]
        exp = n - 1
        res_mat = [[1, 0], [0, 1]]
        base_mat = M
        while exp:
            if exp & 1:
                res_mat = matrix_mult(res_mat, base_mat, MOD)
            base_mat = matrix_mult(base_mat, base_mat, MOD)
            exp //= 2
        x_n = (res_mat[0][0] * v1_x + res_mat[0][1] * v1_y) % MOD
        y_n = (res_mat[1][0] * v1_x + res_mat[1][1] * v1_y) % MOD
        result = (x_n * s1 + y_n * l1) % MOD
    print(result)


def matrix_mult(A, B, mod):
    C = [[0, 0], [0, 0]]
    for i in range(2):
        for k in range(2):
            if A[i][k]:
                for j in range(2):
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod
    return C


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/