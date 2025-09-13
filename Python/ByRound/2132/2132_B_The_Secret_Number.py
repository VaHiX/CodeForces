"""
Problem: CF2132B - The Secret Number

This program solves a problem where we need to find all positive integers x
such that n can be expressed as x * (10^d + 1) for some d >= 1.

Approach:
1. For each test case, we iterate through possible values of d from 20 down to 1
2. For each d, we check if n is divisible by (10^d + 1)
3. If divisible, we calculate x = n / (10^d + 1) and add it to our results
4. We output the count of such x values followed by the values themselves

Time Complexity: O(T * 20) where T is the number of test cases
Space Complexity: O(1) - constant space for each test case
"""


def find_secret_numbers(n):
    """
    Find all positive integers x such that n = x * (10^d + 1) for some d >= 1.

    Args:
        n: The input number to be analyzed

    Returns:
        list: A list of valid x values in descending order of d
    """
    result = []
    # Iterate from d=20 down to d=1
    for exponent in range(20, 0, -1):
        divisor = 10**exponent + 1
        if n % divisor == 0:
            x = n // divisor
            if x > 0:  # Only consider positive x
                result.append(x)
    return result


def main():
    """Main function to handle input and output."""
    import sys

    input = sys.stdin.read
    data = input().split()

    idx = 0
    test_cases = int(data[idx])
    idx += 1

    for _ in range(test_cases):
        n = int(data[idx])
        idx += 1

        numbers = find_secret_numbers(n)

        # Output the results
        print(len(numbers))
        if numbers:
            print(" ".join(map(str, numbers)))


if __name__ == "__main__":
    main()
