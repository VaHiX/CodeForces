# Problem: CF 2132 B - The Secret Number
# https://codeforces.com/contest/2132/problem/B

"""
B. The Secret Number
time limit per test2 seconds
memory limit per test256 megabytes

This program solves a problem where we need to find all positive integers x
such that n can be expressed as x + x * 10^d = x * (10^d + 1) for some d >= 1.
The approach is to iterate over possible values of d from 20 down to 1 and check
if n is divisible by (10^d + 1). If so, compute x = n / (10^d + 1).

Algorithms/Techniques:
- Brute-force iteration over possible exponents (up to 20)
- Modular arithmetic to check divisibility
- Mathematical transformation: n = x * (10^d + 1)

Time Complexity: O(T * 20) where T is the number of test cases
Space Complexity: O(1) - constant space for each test case

"""

def find_secret_numbers(n):
    """
    Find all positive integers x such that n = x * (10^d + 1) for some d >= 1.
    Args:
        n: The input number to be analyzed
    Returns:
        list: A list of valid x values in ascending order of d
    """
    result = []
    # Iterate from d=20 down to 1 (since 10^20 is much larger than 10^18)
    for exponent in range(20, 0, -1):
        divisor = 10**exponent + 1
        if n % divisor == 0:  # Check if n is divisible by (10^d + 1)
            x = n // divisor  # Compute x = n / (10^d + 1)
            if x > 0:         # Ensure x is positive
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
        print(len(numbers))
        if numbers:
            # Output the results in ascending order (since we process d from 20 to 1,
            # the result list is already sorted accordingly due to reversed iteration)
            print(" ".join(map(str, numbers)))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/