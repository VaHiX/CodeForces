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
"""

import sys
from typing import List, Tuple

# Input/Output optimization
input = sys.stdin.readline
MOD = 10**9 + 7

def debug_print(*args, **kwargs):
    """Helper function for debug printing in red color."""
    print("\033[91m" + " ".join(map(str, args)) + "\033[0m", 
          file=sys.stderr, **kwargs)

# Precompute values for dynamic programming
# values: Stores the base values for calculations
# product_sums: Stores cumulative products of values for quick lookups
# operation_counts: Tracks the number of operations needed for each index
# prefix_operation_sums: Prefix sums of operation counts for range queries
values = [1, 1]
product_sums = [1, 1]
operation_counts = [0, 1]
prefix_operation_sums = [0, 1]

# Current size of our precomputed arrays
current_size = 2

# Precompute values until we exceed the maximum possible k (1e9)
while operation_counts[-1] <= 10**9:
    # Calculate next value in the sequence
    next_value = current_size * product_sums[-1] % MOD
    values.append(next_value)
    
    # Update product sums with the new value
    next_product = product_sums[-1] * next_value % MOD
    product_sums.append(next_product)
    
    # Update operation counts (number of operations needed for this index)
    next_ops = prefix_operation_sums[-1] + 1
    operation_counts.append(next_ops)
    
    # Update prefix sums of operations
    next_prefix = prefix_operation_sums[-1] + next_ops
    prefix_operation_sums.append(next_prefix)
    
    current_size += 1


def solve_test_case():
    """
    Solves a single test case for the Wafu problem.
    
    Returns:
        int: The computed result for the test case, modulo MOD
    """
    # Read input values
    n, max_operations = map(int, input().split())
    elements = sorted(map(int, input().split()))
    
    result = 1
    
    for element in elements:
        # If we can use the precomputed value for this element
        if element < current_size and operation_counts[element] <= max_operations:
            result = result * values[element] % MOD
            max_operations -= operation_counts[element]
            
            # Early exit if we've used all operations
            if max_operations == 0:
                break
        else:
            # Handle the case where we need to compute the value manually
            while max_operations > 0:
                # Use one operation to multiply by the current element
                max_operations -= 1
                result = result * element % MOD
                
                # Try to find the largest x where prefix_operation_sums[x] <= max_operations
                x = min(current_size - 1, element - 1)
                while x > 0 and prefix_operation_sums[x] > max_operations:
                    x -= 1
                
                # If we found a valid x, use the precomputed product
                if x > 0 and prefix_operation_sums[x] <= max_operations:
                    max_operations -= prefix_operation_sums[x]
                    result = result * product_sums[x] % MOD
                    element = x + 1  # Continue from the next position
                else:
                    break
            
            # If we've used all operations, exit the loop
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
