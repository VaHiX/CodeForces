# Problem: CF 1922 C - Closest Cities
# https://codeforces.com/contest/1922/problem/C

"""
Algorithm/Technique:
- Preprocessing: For each city, determine its closest city using the given condition.
- Dynamic Programming with Prefix Sums:
    - F[i] stores the cost to travel from city i to city i+1 using the "closest" rule.
    - B[i] stores the cost to travel from city i to city i-1 using the "closest" rule.
    - Prefix sums are computed for F and B arrays to quickly calculate cost between any two cities.
- Time Complexity: O(n + m) per test case, where n is the number of cities and m is the number of queries.
- Space Complexity: O(n) for storing arrays F, B, prefixF, prefixB, and next_arr.

Approach:
1. For each city, compute the closest city (left or right).
2. Build F and B arrays to store costs for "closest" transitions.
3. Compute prefix sums for efficient range query.
4. For each query, determine the direction and calculate cost using prefix sums.
"""

import sys


def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    results = []
    for _ in range(t):
        n = int(data[index])
        index += 1
        a = list(map(int, data[index : index + n]))
        index += n
        m = int(data[index])
        index += 1
        next_arr = [0] * n  # next_arr[i] = index of closest city to city i
        for i in range(n):
            left_diff = 10**18
            right_diff = 10**18
            if i > 0:
                left_diff = a[i] - a[i - 1]  # Distance to left neighbor
            if i < n - 1:
                right_diff = a[i + 1] - a[i]  # Distance to right neighbor
            # Choose the closer neighbor
            if left_diff < right_diff:
                next_arr[i] = i - 1
            else:
                next_arr[i] = i + 1
        F = [0] * (n - 1)  # F[i] = cost to go from city i to i+1
        for i in range(n - 1):
            # If the next closest city is to the right
            if next_arr[i] == i + 1:
                F[i] = 1  # Pay 1 coin for "closest" travel
            else:
                F[i] = a[i + 1] - a[i]  # Pay distance for direct travel
        prefixF = [0] * n  # Prefix sum of F
        if n - 1 > 0:
            for i in range(n - 1):
                prefixF[i + 1] = prefixF[i] + F[i]
        B = [0] * n  # B[i] = cost to go from city i to i-1
        for i in range(1, n):
            # If the next closest city is to the left
            if next_arr[i] == i - 1:
                B[i] = 1  # Pay 1 coin for "closest" travel
            else:
                B[i] = a[i] - a[i - 1]  # Pay distance for direct travel
        prefixB = [0] * n  # Prefix sum of B
        if n > 1:
            for i in range(1, n):
                prefixB[i] = prefixB[i - 1] + B[i]
        for _ in range(m):
            x = int(data[index])
            y = int(data[index + 1])
            index += 2
            x0 = x - 1  # Convert to 0-based index
            y0 = y - 1  # Convert to 0-based index
            if x0 < y0:
                # Traveling from left to right: use prefixF
                res = prefixF[y0] - prefixF[x0]
                results.append(str(res))
            else:
                # Traveling from right to left: use prefixB
                res = prefixB[x0] - prefixB[y0]
                results.append(str(res))
    sys.stdout.write("\n".join(results))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/