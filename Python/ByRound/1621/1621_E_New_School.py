# Problem: CF 1621 E - New School
# https://codeforces.com/contest/1621/problem/E

"""
Algorithm: Greedy assignment with binary search optimization
Time Complexity: O(sum(k_i) * log(sum(k_i)) + n * m)
Space Complexity: O(sum(k_i) + n + m)

The problem requires determining whether it's possible to assign teachers to student groups such that 
the average age of students in each group doesn't exceed the age of the assigned teacher, 
after removing any one student from any group.

Approach:
1. For each group, compute the average age.
2. Sort teachers in descending order of age.
3. For each student, simulate their removal and check if there exists a valid teacher assignment.
4. Use binary search on sorted teacher ages to efficiently check valid assignments.
"""

from bisect import bisect
from itertools import accumulate

if __name__ == "__main__":
    T = int(input())
    for _ in range(T):
        n, m = [int(i) for i in input().split()]
        a = [0] + [int(i) for i in input().split()] + [0]
        c = [[0]] * m
        b = [0] * n
        B = [(0, 0)] * m
        p, d, e, f = [0] * m, [0] * (n + 2), [0] * (n + 2), [0] * (n + 2)

        for i in range(m):
            k = int(input())
            c[i] = [int(i) for i in input().split()]
            b[i] = sum(c[i]) / k
            B[i] = (-b[i], i + 1)

        # Sort teachers in descending order and add sentinel values
        a = [0] + sorted(a)[::-1] + [0]
        B = sorted(B)
        B1 = [i for i, _ in B]  # negative averages
        B2 = [j for _, j in B]  # group indices
        ans = []

        # Precompute prefix sums for efficient range queries
        for i in range(1, m + 1):
            e[i] = e[i - 1] + (-B1[i - 1] > a[i])
            f[i] = f[i - 1] + (-B1[i - 1] > a[i - 1])
            p[B2[i - 1] - 1] = i  # group to position mapping

        # Compute cumulative differences for efficient querying
        d = [0] + list(accumulate(-B1[i - 1] > a[i + 1] for i in range(1, m + 1))) + [0]

        # For each student, simulate their removal and check validity
        for i in range(1, m + 1):
            for x in c[i - 1]:
                # New average after removing student x
                t = (b[i - 1] * len(c[i - 1]) - x) / (len(c[i - 1]) - 1)
                # Find position in sorted group averages
                o = bisect(B1, -t) + 1
                if o > p[i - 1]:
                    # Check if assignment is valid using precomputed values
                    if (
                        t > a[o - 1]
                        or e[p[i - 1] - 1] + f[o - 1] - f[p[i - 1]] + e[m] - e[o - 1]
                    ):
                        ans += ["0"]
                    else:
                        ans += ["1"]
                else:
                    # Check if assignment is valid using precomputed values
                    if (
                        t > a[o]
                        or e[o - 1] + d[p[i - 1] - 1] - d[o - 1] + e[m] - e[p[i - 1]]
                    ):
                        ans += ["0"]
                    else:
                        ans += ["1"]

        print("".join(ans))


# https://github.com/VaHiX/CodeForces/