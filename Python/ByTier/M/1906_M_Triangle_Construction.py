# Problem: CF 1906 M - Triangle Construction
# https://codeforces.com/contest/1906/problem/M

# M. Triangle Construction
# Algorithm/Technique: Greedy approach with preprocessing
# Time Complexity: O(N), where N is the number of sides
# Space Complexity: O(N), for storing the array A

n = int(input())  # Read the number of sides
l = list(map(int, input().split()))  # Read the array A containing special points on each side

# The maximum number of triangles is limited by:
# 1. The total number of special points divided by 3 (each triangle uses 3 points)
# 2. The largest side, because we cannot form more triangles than the longest side allows
print(min(sum(l) // 3, sum(l) - max(l)))


# https://github.com/VaHiX/codeForces/