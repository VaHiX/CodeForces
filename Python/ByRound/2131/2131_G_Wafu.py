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

Time Complexity: O(T * n), where T is the number of test cases
Space Complexity: O(1) for precomputation of constant-sized arrays

Algorithms/Techniques:
- Dynamic Programming
- Modular Arithmetic
- Preprocessing for fast query responses
"""

import sys

input = sys.stdin.readline
MOD = 10**9 + 7


def debug_print(*args, **kwargs):
    """Helper function for debug printing in red color."""
    print("\033[91m" + " ".join(map(str, args)) + "\033[0m", file=sys.stderr, **kwargs)


# Precompute values to optimize calculations
values = [1, 1]
product_sums = [1, 1]
operation_counts = [0, 1]
prefix_operation_sums = [0, 1]
current_size = 2
while operation_counts[-1] <= 10**9:
    next_value = current_size * product_sums[-1] % MOD  # Compute next value based on previous product sum
    values.append(next_value)
    next_product = product_sums[-1] * next_value % MOD   # Compute cumulative product
    product_sums.append(next_product)
    next_ops = prefix_operation_sums[-1] + 1             # Increment operation count
    operation_counts.append(next_ops)
    next_prefix = prefix_operation_sums[-1] + next_ops   # Update prefix operation sums
    prefix_operation_sums.append(next_prefix)
    current_size += 1


def solve_test_case():
    """
    Solves a single test case for the Wafu problem.
    Returns:
        int: The computed result for the test case, modulo MOD
    """
    n, max_operations = map(int, input().split())           # Read n (size of set) and k (max operations)
    elements = sorted(map(int, input().split()))            # Read and sort initial elements
    result = 1                                              # Initialize result to 1
    for element in elements:                                # Iterate through each element
        if element < current_size and operation_counts[element] <= max_operations:
            result = result * values[element] % MOD         # Multiply result by precomputed value
            max_operations -= operation_counts[element]     # Decrease remaining operations
            if max_operations == 0:
                break                                       # No more operations allowed
        else:                                               # Handle elements beyond precomputed range
            while max_operations > 0:
                max_operations -= 1                         # Use one operation
                result = result * element % MOD             # Update the score
                x = min(current_size - 1, element - 1)      # Determine index to check (bound to current size)
                while x > 0 and prefix_operation_sums[x] > max_operations:
                    x -= 1                                  # Reduce x until sufficient operations remain
                if x > 0 and prefix_operation_sums[x] <= max_operations:
                    max_operations -= prefix_operation_sums[x]  # Use accumulated operations
                    result = result * product_sums[x] % MOD     # Apply precomputed product
                    element = x + 1                             # Update element to next value
                else:
                    break                                       # Break if no more valid reductions
            if max_operations == 0:
                break                                           # Early exit if no operations left
    return result


def main():
    """
    Main function to handle multiple test cases.
    Reads the number of test cases and processes each one.
    """
    num_test_cases = int(input())                           # Read number of test cases
    for _ in range(num_test_cases):
        print(solve_test_case())                            # Solve and print result for each case


if __name__ == "__main__":
    main()                                                  # Start the program


# https://github.com/VaHiX/codeForces/