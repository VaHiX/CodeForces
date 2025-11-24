# Problem: CF 1970 E1 - Trails (Easy)
# https://codeforces.com/contest/1970/problem/E1

"""
Code Purpose:
This code solves the problem of counting the number of valid trail combinations Harry can take when hiking in the Alps over n days, starting from cabin 1. 
Each day, Harry moves from his current cabin to Lake Geneva and then to another cabin, such that at least one of the two trails is short.
The solution uses matrix exponentiation to efficiently compute the result in O(log n) time.

Algorithms/Techniques:
- Matrix exponentiation
- Dynamic Programming with state transitions

Time Complexity: O(m^3 * log n)
Space Complexity: O(m^2)

The recurrence relation is modeled using a 2x2 state transition matrix, and the matrix is exponentiated using binary exponentiation to achieve logarithmic time complexity.
"""

r = 1000000007


def muls(ma1, ma2, ro1, co1, ro2, co2):
    # Standard matrix multiplication with modulo operation
    res = [[0] * co2 for i in range(ro1)]
    for i in range(ro1):
        for j in range(co2):
            c = 0
            for t in range(co1):
                c += ma1[i][t] * ma2[t][j] % r
            res[i][j] = c % r
    return res


m, n = map(int, input().split())
lis = list(map(int, input().split()))
lil = list(map(int, input().split()))

# Precompute sums for constructing the transition matrix
r1, r2, r3 = 0, 0, 0
for i in range(m):
    r1 += (lis[i] + lil[i]) ** 2
    r2 += (lis[i] + lil[i]) * lil[i]
    r3 += lil[i] ** 2
    r1, r2, r3 = r1 % r, r2 % r, r3 % r

# Transition matrix for the states
mat = [[r1, r2], [-r2, -r3]]
me = [[1, 0], [0, 1]]  # Identity matrix for exponentiation

# Binary exponentiation of matrix
nb = bin(n - 1)[2:]  # Convert n-1 to binary string
for i in nb[::-1]:   # Iterate from least significant bit to most
    if i == "1":
        me = muls(me, mat, 2, 2, 2, 2)
    mat = muls(mat, mat, 2, 2, 2, 2)

# Initial state vector (short and long trails from cabin 1)
out = [[lis[i] + lil[i] for i in range(m)], [-lil[j] for j in range(m)]]
# Apply exponentiated matrix to initial state
out = muls(me, out, 2, 2, 2, m)

# Compute final answer using state values
a1, b1 = lis[0] + lil[0], lil[0]
cou = 0
for i in range(m):
    cou += out[0][i] * a1 + out[1][i] * b1
    cou = cou % r

print(cou)


# https://github.com/VaHiX/CodeForces/