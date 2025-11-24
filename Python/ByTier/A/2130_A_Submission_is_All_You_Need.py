# Problem: CF 2130 A - Submission is All You Need
# https://codeforces.com/contest/2130/problem/A

"""
===========================================================================
2130A - Submission is All You Need (Python Solution)
===========================================================================
Problem: Calculate the sum of array elements, treating zeros as ones.
Input:  Multiple test cases, each containing an array of integers.
        First line: Number of test cases (t).
        For each test case:
        - First line: Size of array (n).
        - Second line: n space-separated integers.
Output: For each test case, output the sum of elements (zeros count as ones).
Algorithms/Techniques: Simple iteration and counting
Time Complexity: O(t * n), where t is number of test cases and n is array size.
Space Complexity: O(1) - only using a few variables for computation.
===========================================================================
"""


def main():
    import sys

    input_lines = sys.stdin.read().split()
    idx = 0
    num_test_cases = int(input_lines[idx])  # Read number of test cases
    idx += 1
    for _ in range(num_test_cases):
        array_size = int(input_lines[idx])  # Read size of current array
        idx += 1
        numbers = list(map(int, input_lines[idx : idx + array_size]))  # Read the array elements
        idx += array_size
        # Sum all elements and add count of zeros (as zero contributes 1 to sum)
        total_sum = sum(numbers) + numbers.count(0)
        print(total_sum)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/