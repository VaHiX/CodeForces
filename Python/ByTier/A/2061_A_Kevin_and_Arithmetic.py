# Problem: CF 2061 A - Kevin and Arithmetic
# https://codeforces.com/contest/2061/problem/A

# Flowerbox:
# Problem: Maximizing Points in Kevin's Arithmetic Game
# Algorithm/Techniques: Greedy approach with parity analysis
# Time Complexity: O(n) per test case, where n is the number of integers
# Space Complexity: O(1), only using a few variables for computation

for s in [*open(0)][2::2]:  # Read input lines starting from index 2, step 2 (skip n and read arrays)
    a = s.split()           # Split the line into array of strings (integers)
    m = sum(int(x) % 2 for x in a)  # Count number of odd integers in the list
    print(m + (m < len(a)) * 2 - 1)  # Compute and output maximum points


# https://github.com/VaHiX/codeForces/