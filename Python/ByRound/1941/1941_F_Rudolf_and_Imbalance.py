# Problem: CF 1941 F - Rudolf and Imbalance
# https://codeforces.com/contest/1941/problem/F

"""
Code Purpose:
This code solves the problem of minimizing the imbalance of a set of problems after adding at most one new problem.
The imbalance is defined as the maximum difference between consecutive elements in the sorted array of problem complexities.
The approach uses binary search on the answer combined with a greedy check function that determines if a given imbalance can be achieved.

Algorithms/Techniques:
- Binary Search on Answer: We binary search over the possible values of imbalance (from 1 to 2*10^9).
- Greedy Check Function: For a given target imbalance, it determines whether we can add one problem such that the resulting array has maximum difference not exceeding the target.
- Sorting: The models and functions are sorted to enable efficient two-pointer technique.

Time Complexity:
- Overall: O((n + m + k) * log(MAX_VALUE)) where MAX_VALUE = 2 * 10^9
- Sorting: O(m * log(m) + k * log(k))
- Binary search iterations: O(log(MAX_VALUE))
- Each check function call: O(n + m + k)

Space Complexity:
- O(n + m + k) for storing arrays
"""

from random import randint
from sys import stdin

input = stdin.readline

rd = randint(10**9, 10**10)


def main():
    t = int(input())
    for _ in range(t):
        n, m, k = map(int, input().split())
        a_L = list(map(int, input().split()))
        d_L = list(map(int, input().split()))
        f_L = list(map(int, input().split()))
        d_L.sort()  # Sort the models
        f_L.sort()  # Sort the functions
        left = 1
        right = 2 * 10**9

        def check(aim):
            # Initialize boundaries for the range to insert new problem
            left_bound = -1
            right_bound = -1
            for i in range(1, n):
                # If difference is too large, impossible to fix
                if a_L[i] - a_L[i - 1] > 2 * aim:
                    return False
                # If difference is within aim but not strictly under 2*aim
                if a_L[i] - a_L[i - 1] > aim:
                    if left_bound != -1:
                        return False  # More than one gap
                    else:
                        left_bound = a_L[i] - aim  # Calculate possible new problem insertion range
                        right_bound = a_L[i - 1] + aim

            # If no gap to fill, all differences are within aim
            if left_bound == -1:
                return True

            # Use two pointers to check if there exists a new problem which fits in the gap
            i = 0  # Pointer for models
            j = k - 1  # Pointer for functions
            while i < m and j >= 0:
                current_sum = d_L[i] + f_L[j]  # Combination of model and function
                if current_sum > right_bound:
                    j -= 1  # Reduce function complexity
                elif current_sum < left_bound:
                    i += 1  # Increase model complexity
                else:
                    return True  # Found a valid combination within the gap

            return False  # No valid combination found

        # Binary search on the minimum possible imbalance
        while left < right:
            middle = (left + right) // 2  # Midpoint of current search range
            if check(middle) is True:  # If this imbalance is achievable
                right = middle  # Try to find a smaller one
            else:
                left = middle + 1  # This imbalance is not achievable, try higher
        print(left)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/