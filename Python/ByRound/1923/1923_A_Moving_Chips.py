# Problem: CF 1923 A - Moving Chips
# https://codeforces.com/contest/1923/problem/A

"""
Minimum Operations to Group Chips

Algorithm:
- The problem requires grouping all chips into a single contiguous block by moving chips to the left.
- Key insight: Only chips that are not already adjacent to other chips need to be moved.
- We process the array from right to left, counting consecutive free cells (0s) between chips (1s).
- For every chip encountered, we add to the answer the number of free cells that need to be filled to bring it to the leftmost position of its group.

Time Complexity: O(n), where n is the number of cells, since we scan the array once.
Space Complexity: O(1), only using a few variables for computation.
"""

import sys
from os import path


def input():
    return sys.stdin.readline().strip()


def input_int():
    return int(input())


def input_list(delimiter=" "):
    return list(map(int, input().split(delimiter)))


def input_string():
    return input()


def solve():
    n = input_int()  # Read number of cells
    A = input_list()  # Read the state of cells (0 = free, 1 = chip)
    
    # Find the rightmost chip
    j = n - 1
    while j > -1 and A[j] != 1:
        j -= 1
    
    # Initialize counters
    ans = 0  # Total operations needed
    count = 0  # Count of free cells between chips
    
    # Process from right to left
    while j > -1:
        a = A[j]  # Current cell value
        if a == 1:  # If it's a chip
            # Add number of free cells before this chip to total operations
            ans += count
            count = 0  # Reset count after processing
        else:  # If it's a free cell
            count += 1  # Increment free cell counter
        j -= 1  # Move to the previous cell
    
    return ans


def main():
    testcases = input_int()  # Read number of test cases
    for _ in range(testcases):
        print(solve())  # Solve and print result for each test case


if __name__ == "__main__":
    if path.exists("input.txt"):
        sys.stdin = open("input.txt", "r")
        sys.stdout = open("output.txt", "w")
    main()


# https://github.com/VaHiX/CodeForces/