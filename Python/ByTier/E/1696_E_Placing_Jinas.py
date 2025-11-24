# Problem: CF 1696 E - Placing Jinas
# https://codeforces.com/contest/1696/problem/E

# Purpose: Solve the problem of placing Jinas on a grid to make all white cells have 0 dolls.
#          The grid is defined by a non-increasing sequence a, where cell (x,y) is white if y < a[x].
#          Each operation splits one doll into two dolls at (x,y+1) and (x+1,y).
#          The goal is to compute the minimum number of operations needed.
#
# Algorithms/Techniques: 
#   - Dynamic Programming with Combinatorics
#   - Precompute factorials for modular inverse calculations
#   - Use the formula for combinations to compute required operations
#
# Time Complexity: O(n + max(a_i)) where n is input size and max(a_i) is maximum value in the sequence.
# Space Complexity: O(max(a_i)) for storing factorials and related data structures.

n, x, d, m, f = int(input()), 0, 0, 10**9 + 7, [1]
for i in range(1, 9**6):  # Precompute factorials up to a large number
    f.append(f[-1] * i % m)
for z in map(int, input().split()):
    # For each element in the sequence, calculate contribution to operations
    # using combination formula and modular inverse
    d += f[z + x] * pow(f[x + 1] * f[z - 1], -1, m) * (z > 0)
    x += 1
print(d % m)


# https://github.com/VaHiX/CodeForces/