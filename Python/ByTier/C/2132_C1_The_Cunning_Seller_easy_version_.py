"""
Problem: CF2132C1 - The Cunning Seller (Easy Version)

This program solves a problem where we need to calculate a special sum based on
the ternary (base-3) representation of a number. The sum is calculated as:
sum(digit * 3^(position-1) * (9 + position)) for each digit in the ternary representation.

Approach:
1. For each test case, convert the number to its ternary representation
2. For each digit in the ternary representation, calculate its contribution to the sum
3. The contribution is digit * 3^(position-1) * (9 + position)
4. Sum up all contributions and output the result

Time Complexity: O(T * log₃N) where T is the number of test cases and N is the input number
Space Complexity: O(1) - constant space per test case
"""

def calculate_special_sum(number):
    """
    Calculate the special sum based on the ternary representation of the number.
    
    Args:
        number: The input number to process
        
    Returns:
        int: The calculated special sum
    """
    special_sum = 0
    position = 0
    
    while number > 0:
        # Get the least significant digit in base-3
        digit = number % 3
        number = number // 3
        
        # Calculate the contribution of this digit to the sum
        if position > 0:  # Avoid negative exponent for position=0
            contribution = digit * (3 ** (position - 1)) * (9 + position)
            special_sum += contribution
        
        position += 1
    
    return int(special_sum)

def main():
    """Main function to handle input and output."""
    import sys
    input = sys.stdin.read
    data = input().split()
    
    idx = 0
    test_cases = int(data[idx])
    idx += 1
    results = []
    
    for _ in range(test_cases):
        n = int(data[idx])
        idx += 1
        result = calculate_special_sum(n)
        results.append(result)
    
    # Print all results
    for result in results:
        print(result)

if __name__ == "__main__":
    main()
