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

Time Complexity:
   - Preprocessing: O(1) for fixed number of powers
   - Per query: O(log k) for binary search
   - Digit sum calculation: O(log n) for a number n

Space Complexity: O(1) - Constant space for precomputed values
"""

import sys

def main():
    # Precompute powers of 10 up to 1e18
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
        position = 1  # Current digit position (1s, 10s, 100s, etc.)
        
        while position <= n:
            # Split number into higher, current, and lower digits
            higher = n // (position * 10)
            current_digit = (n // position) % 10
            lower = n % position
            
            # Calculate contribution from each digit position
            total += (
                higher * 45 * position +  # Full cycles
                (current_digit * (current_digit - 1) // 2) * position +  # Current digit partial cycle
                current_digit * (lower + 1)  # Remaining numbers
            )
            position *= 10
            
        return total

    # Precompute sum of digits for ranges [10^(i-1), 10^i - 1]
    digit_sums = [0]  # digit_sums[0] = 0 (for numbers with 0 digits)
    for i in range(1, 19):
        start = POWERS_OF_10[i-1]
        end = POWERS_OF_10[i] - 1
        digit_sums.append(sum_of_digits_up_to(end) - sum_of_digits_up_to(start - 1))

    # Process queries
    input = sys.stdin.read
    data = input().split()
    idx = 0
    num_queries = int(data[idx])
    idx += 1
    
    for _ in range(num_queries):
        k = int(data[idx])
        idx += 1
        
        total_sum = 0
        num_digits = 1  # Start with 1-digit numbers
        
        while True:
            # Number of numbers with 'num_digits' digits
            count = 9 * POWERS_OF_10[num_digits - 1]
            # Total digits in all numbers with 'num_digits' digits
            total_digits = count * num_digits
            
            if k > total_digits:
                # Add sum for all numbers with 'num_digits' digits
                total_sum += digit_sums[num_digits]
                k -= total_digits
                num_digits += 1
                continue
                
            # Find the exact number containing the k-th digit
            numbers_before, digit_in_number = divmod(k, num_digits)
            if digit_in_number == 0:
                # Last digit of the previous number
                numbers_before -= 1
                digit_in_number = num_digits
            
            current_number = POWERS_OF_10[num_digits - 1] + numbers_before
            
            # Add sum of complete numbers
            if numbers_before > 0:
                total_sum += sum_of_digits_up_to(current_number - 1) - sum_of_digits_up_to(POWERS_OF_10[num_digits - 1] - 1)
            
            # Add sum of digits in the current number up to the k-th digit
            if digit_in_number > 0:
                total_sum += sum(map(int, str(current_number)[:digit_in_number]))
            
            print(total_sum)
            break

if __name__ == "__main__":
    main()
