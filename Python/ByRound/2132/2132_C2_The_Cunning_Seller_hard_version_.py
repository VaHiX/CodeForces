"""
Problem: CF2132C2 - The Cunning Seller (Hard Version)

This program solves a problem where we need to determine the minimum total cost for a customer
to buy exactly k items from a seller who uses a cunning pricing strategy. The seller's prices
are based on base-3 representation of numbers.

Approach:
1. Calculate the base-3 digit sum of n
2. Determine the maximum possible r such that r has the same parity as n
3. Calculate the surcharge based on the difference between n and r
4. Compute the total cost using the formula 3n + surcharge

Time Complexity: O(log n) per test case
   - Due to digit sum calculation and loop iterations
   
Space Complexity: O(1) additional space
   - Uses constant extra space regardless of input size
"""

import sys


def solve():
    input = sys.stdin.read().strip().split()
    idx = 0
    num_test_cases = int(input[idx])
    idx += 1
    results = []

    for _ in range(num_test_cases):
        n = int(input[idx])
        k = int(input[idx + 1])
        idx += 2

        # Calculate sum of base-3 digits of n
        base3_digit_sum = 0
        temp = n
        while temp > 0:
            base3_digit_sum += temp % 3
            temp //= 3

        # Check if it's possible to satisfy the condition
        if k < base3_digit_sum:
            results.append("-1")
            continue

        # Find maximum r with same parity as n that's ≤ min(k, n)
        max_possible = min(k, n)
        if (max_possible ^ n) & 1:  # Check if different parity
            max_possible -= 1

        # Calculate the difference between n and max_possible
        difference = n - max_possible
        M = difference // 2  # Number of operations needed

        # Calculate surcharge using base-3 representation
        surcharge = 0
        remaining_items = n // 3
        power_of_3 = 1

        while M > 0 and remaining_items > 0:
            # Take as many items as possible at current power of 3
            take = min(M, remaining_items)
            surcharge += take * power_of_3
            M -= take
            remaining_items //= 3
            power_of_3 *= 3

        # Calculate and store the total cost
        total_cost = 3 * n + surcharge
        results.append(str(total_cost))

    # Output all results
    print("\n".join(results))


if __name__ == "__main__":
    solve()
