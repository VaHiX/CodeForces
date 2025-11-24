# Problem: CF 1765 J - Hero to Zero
# https://codeforces.com/contest/1765/problem/J

"""
Algorithm: Minimum Coins to Zero Matrix
Techniques: Sorting, Binary Search, Prefix Sums

Time Complexity: O(n log n) due to sorting and binary search operations
Space Complexity: O(n) for storing sorted arrays and prefix sums

The problem involves transforming a matrix of absolute differences into a zero matrix
using specific operations that cost or provide coins. The key insight is to model
this as a minimum cost assignment problem where we want to minimize the total
operations needed to reduce all matrix elements to zero.

The approach uses the fact that the optimal solution can be derived from:
1. Optimal assignment of elements from 'a' to 'b' (minimal matching cost)
2. Cost of adjusting the positions using row/column operations
3. Combining these costs to compute final answer

The 'sum_C' calculation computes the total cost of shifting elements using
row and column operations, while the final formula combines this with the
minimal matching cost.
"""

import bisect


def main():
    import sys

    input = sys.stdin.read
    data = input().split()
    idx = 0
    n = int(data[idx])
    idx += 1
    a = list(map(int, data[idx : idx + n]))
    idx += n
    b = list(map(int, data[idx : idx + n]))

    # Sort both arrays to facilitate optimal matching
    a_sorted = sorted(a)
    b_sorted = sorted(b)

    # Compute minimal cost of matching elements from a to b
    minimal_matching_cost = sum(abs(a_sorted[i] - b_sorted[i]) for i in range(n))

    # Build prefix sum array for efficient range sum queries
    prefix_sum = [0] * (n + 1)
    for i in range(n):
        prefix_sum[i + 1] = prefix_sum[i] + b_sorted[i]

    # Calculate sum_C which represents the operational cost of row/column adjustments
    sum_C = 0
    for ai in a_sorted:
        # Find how many elements in b_sorted are greater than ai
        k = bisect.bisect_right(b_sorted, ai)
        # Cost of moving elements less than ai
        sum_less = ai * k - prefix_sum[k]
        # Cost of moving elements greater than ai
        sum_greater = (prefix_sum[n] - prefix_sum[k]) - ai * (n - k)
        sum_C += sum_less + sum_greater

    # Final formula combining all costs
    answer = sum_C + (1 - n) * minimal_matching_cost
    print(answer)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/