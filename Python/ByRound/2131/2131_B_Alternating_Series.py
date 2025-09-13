"""
Problem: CF2131B - Alternating Series

This program generates an alternating series of numbers based on the given input n.
The series alternates between -1 and 3, with special handling for the last element
to ensure the sum is 1 when n is odd.

Approach:
1. For each test case, read integer n
2. If n is odd:
   - Generate (n//2) pairs of (-1, 3) and add an extra -1 at the end
3. If n is even:
   - Generate (n//2 - 1) pairs of (-1, 3) and end with (-1, 2)
4. Print the generated sequence

Time Complexity: O(n) per test case
Space Complexity: O(1) - output is generated on the fly
"""


def generate_alternating_series(n):
    """Generate the alternating series based on the given length n."""
    if n % 2 == 1:
        # For odd n: (n//2) pairs of (-1, 3) and one -1 at the end
        return "-1 3 " * (n // 2) + "-1"
    else:
        # For even n: (n//2 - 1) pairs of (-1, 3) and end with (-1, 2)
        return "-1 3 " * (n // 2 - 1) + "-1 2"


def main():
    # Read number of test cases
    num_test_cases = int(input())

    for _ in range(num_test_cases):
        # Read sequence length
        sequence_length = int(input())

        # Generate and print the alternating series
        print(generate_alternating_series(sequence_length))


if __name__ == "__main__":
    main()
