# Problem: CF 1869 B - 2D Traveling
# https://codeforces.com/contest/1869/problem/B

"""
Algorithm: Greedy with Manhattan Distance
Purpose: Find minimum cost to travel from city 'a' to city 'b' on a 2D plane,
         where major cities have free travel between each other.

Time Complexity: O(n*k) per test case, where n is number of cities and k is number of major cities.
Space Complexity: O(n) for storing city coordinates.

Approach:
1. Calculate direct cost between cities a and b.
2. For each major city, compute the Manhattan distance from city a and b.
3. The minimum cost is either:
   - Direct travel cost (if no major city is involved)
   - Cost via a major city (min distance from a to any major city + min distance from b to any major city)
"""

import sys


def solve():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    results = []
    for _ in range(t):
        n = int(data[index])
        k = int(data[index + 1])
        a = int(data[index + 2])
        b = int(data[index + 3])
        index += 4
        coords = []
        for i in range(n):
            x = int(data[index])
            y = int(data[index + 1])
            index += 2
            coords.append((x, y))
        xa, ya = coords[a - 1]  # Get coordinates of city a (1-indexed)
        xb, yb = coords[b - 1]  # Get coordinates of city b (1-indexed)
        direct_cost = abs(xa - xb) + abs(ya - yb)  # Manhattan distance directly
        if k == 0:
            # No major cities, must take direct path
            results.append(str(direct_cost))
        else:
            # Find the minimum distances from a and b to any major city
            min_a = float("inf")
            min_b = float("inf")
            for i in range(k):
                x, y = coords[i]  # Coordinates of major city
                d_a = abs(xa - x) + abs(ya - y)
                if d_a < min_a:
                    min_a = d_a
                d_b = abs(xb - x) + abs(yb - y)
                if d_b < min_b:
                    min_b = d_b
            total_via = min_a + min_b  # Cost via a major city
            if total_via < direct_cost:
                # Traveling via a major city is cheaper
                results.append(str(total_via))
            else:
                # Direct travel is cheaper
                results.append(str(direct_cost))
    print("\n".join(results))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/