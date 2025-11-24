# Problem: CF 2132 A - Homework
# https://codeforces.com/contest/2132/problem/A

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

Algorithms/Techniques: String manipulation, simulation
"""

def process_test_case():
    """Process a single test case and return the result string."""
    int(input())
    result = input().strip()
    int(input())
    chars_to_add = input().strip()
    directions = input().strip()
    for i in range(len(chars_to_add)):
        char = chars_to_add[i]
        if directions[i] == "D":
            result += char
        else:
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
        int(data[idx])
        idx += 1
        s = data[idx]
        idx += 1
        int(data[idx])
        idx += 1
        t = data[idx]
        idx += 1
        u = data[idx]
        idx += 1
        result = s
        for i in range(len(t)):
            if u[i] == "D":
                result += t[i]
            else:
                result = t[i] + result
        print(result)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/