# Problem: CF 2132 D - From 1 to Infinity
# https://codeforces.com/contest/2132/problem/D

"""
Problem: CF2132D - From 1 to Infinity
This program solves a problem where we need to find the sum of digits of numbers
from 1 to N, where N is determined based on the input k, which represents a position
in an infinite sequence of numbers.

Approach:
1. Precompute powers of 10 for efficient digit manipulation
2. Calculate the sum of digits for numbers up to a given n
3. Use binary search to find the number at position k in the sequence
4. Calculate the required sum based on the position k

Algorithms/Techniques:
- Digit DP (Dynamic Programming) with precomputed sums
- Binary search to locate k-th digit efficiently
- Mathematical calculation of digit sums for ranges of numbers

Time Complexity:
   - Preprocessing: O(1) for fixed number of powers
   - Per query: O(log k) for binary search
   - Digit sum calculation: O(log n) for a number n
Space Complexity: O(1) - Constant space for precomputed values

"""

import sys


def main():
    POWERS_OF_10 = [10**i for i in range(19)]

    def sum_of_digits_up_to(n):
        """
        Calculate the sum of all digits from 1 to n.
        Args:
            n: Upper bound (inclusive)
        Returns:
            int: Sum of all digits from 1 to n
        """
        total = 0
        position = 1
        while position <= n:
            higher = n // (position * 10)  # Count of full cycles in current digit place
            current_digit = (n // position) % 10  # Current digit at this position
            lower = n % position  # Remaining part after the current digit
            total += (
                higher * 45 * position  # Sum from full cycles
                + (current_digit * (current_digit - 1) // 2) * position  # Sum from partial cycle
                + current_digit * (lower + 1)  # Add contribution of last incomplete cycle
            )
            position *= 10
        return total

    digit_sums = [0]
    for i in range(1, 19):
        start = POWERS_OF_10[i - 1]
        end = POWERS_OF_10[i] - 1
        # Precompute sum of digits for ranges like [10^(i-1), 10^i - 1]
        digit_sums.append(sum_of_digits_up_to(end) - sum_of_digits_up_to(start - 1))
    input = sys.stdin.read
    data = input().split()
    idx = 0
    num_queries = int(data[idx])
    idx += 1
    for _ in range(num_queries):
        k = int(data[idx])
        idx += 1
        total_sum = 0
        num_digits = 1
        while True:
            count = 9 * POWERS_OF_10[num_digits - 1]  # How many numbers have exactly num_digits digits
            total_digits = count * num_digits  # Total digit count for this group
            if k > total_digits:  # If k exceeds current range, add sum of that range
                total_sum += digit_sums[num_digits]
                k -= total_digits
                num_digits += 1
                continue
            numbers_before, digit_in_number = divmod(k, num_digits)  # Find the number and position within it
            if digit_in_number == 0:
                numbers_before -= 1
                digit_in_number = num_digits
            current_number = POWERS_OF_10[num_digits - 1] + numbers_before  # Actual number containing k-th digit
            if numbers_before > 0:
                total_sum += sum_of_digits_up_to(
                    current_number - 1
                ) - sum_of_digits_up_to(POWERS_OF_10[num_digits - 1] - 1)
            if digit_in_number > 0:
                total_sum += sum(map(int, str(current_number)[:digit_in_number]))
            print(total_sum)
            break


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/