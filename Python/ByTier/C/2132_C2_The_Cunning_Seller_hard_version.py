# Problem: CF 2132 C2 - The Cunning Seller (hard version)
# https://codeforces.com/contest/2132/problem/C2

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

Algorithms/Techniques:
- Base-3 digit sum computation
- Bit manipulation for parity checking
- Greedy strategy with base-3 representation
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
        base3_digit_sum = 0
        temp = n
        while temp > 0:
            base3_digit_sum += temp % 3  # Calculate sum of base-3 digits
            temp //= 3
        if k < base3_digit_sum:  # Impossible case: not enough deals to cover digit sum
            results.append("-1")
            continue
        max_possible = min(k, n)
        if (max_possible ^ n) & 1:  # Adjust max_possible to have same parity as n
            max_possible -= 1
        difference = n - max_possible
        M = difference // 2  # Calculate how many adjustments are needed
        surcharge = 0
        remaining_items = n // 3  # Begin with base-3 representation logic
        power_of_3 = 1
        while M > 0 and remaining_items > 0:  # Greedily use larger powers of 3 first
            take = min(M, remaining_items)
            surcharge += take * power_of_3  # Accumulate surcharge based on base-3 values
            M -= take
            remaining_items //= 3
            power_of_3 *= 3
        total_cost = 3 * n + surcharge  # Final cost computation using formula
        results.append(str(total_cost))
    print("\n".join(results))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/codeForces/