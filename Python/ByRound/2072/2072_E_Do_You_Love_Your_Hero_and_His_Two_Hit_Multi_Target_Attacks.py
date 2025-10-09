# Problem: CF 2072 E - Do You Love Your Hero and His Two-Hit Multi-Target Attacks?
# https://codeforces.com/contest/2072/problem/E

"""
E. Do You Love Your Hero and His Two-Hit Multi-Target Attacks?

Purpose:
This code solves a problem where we need to place n staffs at distinct integer coordinates such that exactly k pairs of points satisfy the condition ρ(i,j) = d(i,j). Here,
- ρ(i,j) is the Euclidean distance between points i and j.
- d(i,j) is the Manhattan distance between points i and j.

The key insight is that ρ(i,j) = d(i,j) if and only if the points are aligned either vertically or horizontally (i.e., one coordinate is equal). Hence, we need to arrange points so that precisely k such pairs exist.

Algorithm:
1. Decompose k into a sum of triangular numbers (m * (m - 1) // 2), where m represents how many points align in a straight line.
2. For each such group of m points, place them in a vertical or horizontal line to ensure all pairs satisfy the condition.
3. Distribute these groups across coordinate space.

Time Complexity: O(sqrt(k)) for decomposition per test case (since we process k by subtracting triangular numbers)
Space Complexity: O(sqrt(k)) to store coordinates

"""

t = int(input())
for _ in range(t):
    k = int(input())
    if not k:
        print(1)
        print("0 0")
        continue
    g = []
    while k:
        m = 2
        # Find the largest m such that m*(m-1)//2 <= k
        while m * (m - 1) // 2 <= k:
            m += 1
        m -= 1
        g += [m]
        k -= m * (m - 1) // 2  # Subtract the count of pairs represented by this group
    
    # Create coordinate list for each point in each line group
    c = [(i * 10000 + j, i) for i, m in enumerate(g) for j in range(m)]
    print(len(c))
    print("\n".join(f"{x} {y}" for x, y in c))


# https://github.com/VaHiX/codeForces/