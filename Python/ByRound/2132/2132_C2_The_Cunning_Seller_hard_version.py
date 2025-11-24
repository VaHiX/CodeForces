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
- Base-3 representation manipulation
- Greedy strategy for minimizing cost
- Bitwise operations for parity check
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
            base3_digit_sum += temp % 3  # Compute base-3 digit sum
            temp //= 3
        if k < base3_digit_sum:  # Impossible to buy n items with k deals
            results.append("-1")
            continue
        max_possible = min(k, n)
        if (max_possible ^ n) & 1:  # Check if parity differs; adjust max_possible
            max_possible -= 1
        difference = n - max_possible
        M = difference // 2  # Calculate surplus needed to reach optimal allocation
        surcharge = 0
        remaining_items = n // 3  # Number of items that can be bought in bulk (Deal B)
        power_of_3 = 1
        while M > 0 and remaining_items > 0:
            take = min(M, remaining_items)  # Take minimum of required surplus or available items
            surcharge += take * power_of_3  # Add cost for this portion of deal
            M -= take
            remaining_items //= 3  # Move to next power of 3 in representation
            power_of_3 *= 3
        total_cost = 3 * n + surcharge  # Final cost with base price and surcharge
        results.append(str(total_cost))
    print("\n".join(results))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/