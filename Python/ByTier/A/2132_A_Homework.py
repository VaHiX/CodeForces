"""
Problem: CF2132A - Homework

This program processes a series of test cases where each case involves
constructing a string by appending or prepending characters based on
a direction string.

Approach:
1. For each test case, read the initial string and a series of characters with directions
2. For each character, append it to the end if direction is 'D', otherwise prepend it
3. Print the final constructed string

Time Complexity: O(T * n) where T is the number of test cases and n is the length of operations
Space Complexity: O(n) where n is the length of the final string
"""


def process_test_case():
    """Process a single test case and return the result string."""
    # Read input values
    n = int(input())  # Length of initial string (unused in this implementation)
    result = input().strip()
    num_operations = int(input())  # Number of operations to perform
    chars_to_add = input().strip()
    directions = input().strip()

    # Process each character and its corresponding direction
    for i in range(len(chars_to_add)):
        char = chars_to_add[i]
        if directions[i] == "D":
            # Append to the end
            result += char
        else:
            # Prepend to the beginning
            result = char + result

    return result


def main():
    """Main function to handle multiple test cases."""
    import sys

    input = sys.stdin.read
    data = input().split()

    idx = 0
    test_cases = int(data[idx])
    idx += 1

    for _ in range(test_cases):
        # Read test case data
        n = int(data[idx])
        idx += 1
        s = data[idx]
        idx += 1
        a = int(data[idx])  # Number of operations
        idx += 1
        t = data[idx]  # Characters to add
        idx += 1
        u = data[idx]  # Directions ('D' for append, 'U' for prepend)
        idx += 1

        # Process the test case
        result = s
        for i in range(len(t)):
            if u[i] == "D":
                result += t[i]
            else:
                result = t[i] + result

        print(result)


if __name__ == "__main__":
    main()
