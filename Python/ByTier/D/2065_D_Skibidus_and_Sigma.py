# Problem: CF 2065 D - Skibidus and Sigma
# https://codeforces.com/contest/2065/problem/D

"""
Purpose: 
This code solves the problem of maximizing the "sigma score" of a concatenated array formed by arranging n given arrays in some order.
The score of an array b of length k is defined as the sum of prefix sums: S_1 + S_2 + ... + S_k, where S_i is the sum of first i elements.

The solution uses the following approach:
- For each array, compute its total sum.
- Compute the cumulative sum of the array (used to calculate its contribution to the score in context of concatenation).
- Sort the arrays in descending order of their final sums (arr_sums) to maximize the benefit of earlier placements.
- Use a greedy strategy to assign each array to a position in the optimal order.

Algorithms/Techniques:
- Greedy sorting
- Prefix sum calculation
- Optimal arrangement based on contribution to final score

Time Complexity: O(n log n + nm)
Space Complexity: O(n)

Where n is the number of arrays and m is the length of each array.
"""
import sys


def solve():
    data = sys.stdin.read().split()
    t = int(data[0])
    pos = 1
    out = []
    for _ in range(t):
        n = int(data[pos])
        m = int(data[pos + 1])
        pos += 2
        arr_sums = [0] * n
        totalF = 0
        for i in range(n):
            s = 0
            f = 0
            for j in range(m):
                x = int(data[pos])
                pos += 1
                s += x  # Compute prefix sum for array i
                f += s  # Accumulate prefix sums = contribution to total score
            arr_sums[i] = s  # Final sum of array i
            totalF += f  # Add contribution of array i to total
        arr_sums.sort(reverse=True)  # Sort arrays by final sum to maximize contribution in optimal arrangement
        bonus = 0
        for i, s in enumerate(arr_sums):
            # i-th largest array gets multiplied by (n - 1 - i) times m
            # because of how prefix sums will be added in the concatenated sequence
            bonus += (n - 1 - i) * s
        bonus *= m  # Scale bonus by m (length of each array)
        out.append(str(totalF + bonus))
    sys.stdout.write("\n".join(out))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/