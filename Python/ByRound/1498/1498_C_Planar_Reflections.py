# Problem: CF 1498 C - Planar Reflections
# https://codeforces.com/contest/1498/problem/C

"""
Code Purpose:
This program calculates the number of particles in the final multiset after a particle with decay age k is shot at n planes, 
where each plane produces a copy of the particle with reduced decay age (k-1) moving in the opposite direction, 
unless the decay age is 1, in which case no copy is produced.

Algorithm:
Dynamic Programming (DP) approach is used to compute the number of particles for each combination of decay age and plane index.
- A 2D DP table 'matrix' is defined where matrix[i][j] represents the number of particles with decay age i after passing through j planes.
- Base cases are set where any decay age 1 or no planes will always result in 1 particle.
- Transitions are computed based on recurrence relation:
    - The current state can come from the previous state moving left (matrix[i][j-1])
    - Or from a copy with reduced decay age from the opposite side (matrix[i-1][n-j])
- The final result is stored in matrix[k][n].

Time Complexity: O(n * k)
Space Complexity: O(n * k)

Note: The matrix size is fixed at 1009x1009 as per constraints (n,k <= 1000), and modular arithmetic is applied using p = 10^9 + 7.
"""

p = 10**9 + 7
for _ in range(int(input())):
    n, k = map(int, input().split())
    # Initialize a 2D DP table with zeros
    matrix = [[0 for i in range(1009)] for i in range(1009)]
    # Fill the DP table
    for i in range(k + 1):
        for j in range(n + 1):
            # Base case: if decay age is 1 or no planes, only one particle exists
            if i == 1 or j == 0:
                matrix[i][j] = 1
            else:
                # Transition: sum of particles coming from left and from right (with decay reduced)
                matrix[i][j] = (matrix[i][j - 1] + matrix[i - 1][n - j]) % 1000000007
    # Output the final count of particles with decay age k and n planes
    print(matrix[k][n])


# https://github.com/VaHiX/CodeForces/