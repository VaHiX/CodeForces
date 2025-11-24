# Problem: CF 2131 G - Wafu!
# https://codeforces.com/contest/2131/problem/G

"""
Problem: CF2131G - Wafu
This program solves a problem involving combinatorial mathematics and modular arithmetic.
It processes multiple test cases to calculate a specific value based on given constraints.

Approach:
1. Precompute values using dynamic programming to optimize calculations
2. Process each test case with the given n and k values
3. Use precomputed values to efficiently determine the result

Algorithms/Techniques:
- Dynamic Programming (DP)
- Modular Arithmetic
- Greedy Strategy with Precomputation

Time Complexity: O(T * n), where T is the number of test cases
Space Complexity: O(1) for precomputation of constant-sized arrays

"""

import sys

input = sys.stdin.readline
MOD = 10**9 + 7


def debug_print(*args, **kwargs):
    """Helper function for debug printing in red color."""
    print("\033[91m" + " ".join(map(str, args)) + "\033[0m", file=sys.stderr, **kwargs)


# Precompute values for efficient lookup
values = [1, 1]
product_sums = [1, 1]
operation_counts = [0, 1]
prefix_operation_sums = [0, 1]
current_size = 2
while operation_counts[-1] <= 10**9:
    next_value = current_size * product_sums[-1] % MOD
    values.append(next_value)
    next_product = product_sums[-1] * next_value % MOD
    product_sums.append(next_product)
    next_ops = prefix_operation_sums[-1] + 1
    operation_counts.append(next_ops)
    next_prefix = prefix_operation_sums[-1] + next_ops
    prefix_operation_sums.append(next_prefix)
    current_size += 1


def solve_test_case():
    """
    Solves a single test case for the Wafu problem.
    Returns:
        int: The computed result for the test case, modulo MOD
    """
    n, max_operations = map(int, input().split())
    elements = sorted(map(int, input().split()))
    result = 1
    for element in elements:
        # If the current element is within the precomputed range and we have enough operations
        if element < current_size and operation_counts[element] <= max_operations:
            result = result * values[element] % MOD
            max_operations -= operation_counts[element]
            if max_operations == 0:
                break
        else:
            # If not enough operations or element exceeds precomputation, process manually
            while max_operations > 0:
                max_operations -= 1
                result = result * element % MOD
                x = min(current_size - 1, element - 1)
                # Find the largest x such that we can use it without exceeding remaining operations
                while x > 0 and prefix_operation_sums[x] > max_operations:
                    x -= 1
                if x > 0 and prefix_operation_sums[x] <= max_operations:
                    max_operations -= prefix_operation_sums[x]
                    result = result * product_sums[x] % MOD
                    element = x + 1
                else:
                    break
            if max_operations == 0:
                break
    return result


def main():
    """
    Main function to handle multiple test cases.
    Reads the number of test cases and processes each one.
    """
    num_test_cases = int(input())
    for _ in range(num_test_cases):
        print(solve_test_case())


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/