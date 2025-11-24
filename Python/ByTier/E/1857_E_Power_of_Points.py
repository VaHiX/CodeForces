# Problem: CF 1857 E - Power of Points
# https://codeforces.com/contest/1857/problem/E

"""
Code Purpose:
This program computes the sum of powers of all integer points from 1 to 10^9 for each possible value of s,
where s is a point from the input array x. Each s forms segments [s, x_i] (or [x_i, s] if x_i < s) that cover
integer points. The power of a point p is defined as the number of segments covering it.

Algorithms/Techniques:
- Sorting the input points to enable efficient prefix sum calculations.
- Using binary search (`bisect_left`) to quickly find insertion point of s in sorted array.
- Calculating prefix sums for efficient range sum queries.
- For each s, compute the contribution of all points to the total sum of powers using math.

Time Complexity: O(n log n + n) per test case due to sorting and linear iteration.
Space Complexity: O(n) for storing the sorted array and prefix sums.
"""

import bisect


def main():
    import sys

    input = sys.stdin.read
    data = input().split()
    ptr = 0
    t = int(data[ptr])
    ptr += 1
    for _ in range(t):
        n = int(data[ptr])
        ptr += 1
        x = list(map(int, data[ptr : ptr + n]))
        ptr += n
        sorted_x = sorted(x)  # Sort input for prefix sums and binary search
        prefix = [0] * (n + 1)  # Prefix sum array to compute range sums quickly
        for i in range(n):
            prefix[i + 1] = prefix[i] + sorted_x[i]
        sum_x = prefix[-1]  # Total sum of all elements in sorted_x
        res = []
        for s in x:
            idx = bisect.bisect_left(sorted_x, s)  # Find how many elements are <= s
            left_sum = prefix[idx]  # Sum of all elements less than s
            left_count = idx  # Number of elements less than s
            right_sum = sum_x - left_sum  # Sum of all elements greater than or equal to s
            right_count = n - idx  # Number of elements greater than or equal to s

            # Compute total contribution of all points to the sum of powers
            # The absolute deviation from s is calculated:
            # left_sum contributes positively as s * left_count - left_sum
            # right_sum contributes negatively as right_sum - s * right_count
            total_abs = s * left_count - left_sum + (right_sum - s * right_count)
            total_sum = total_abs + n  # Add n because each segment contributes to at least 1 point
            res.append(str(total_sum))
        print(" ".join(res))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/