"""
Problem: CF2131E - Adjacent XOR

This program determines if array A can be transformed into array B using the following operation:
- Choose an index i (0 ≤ i < n-1) and set A[i] = A[i] XOR A[i+1]

The operation can be performed any number of times (including zero).

Approach:
1. The last element of A must match the last element of B since it can't be modified.
2. For each element from second last to first, check if it can be transformed into the target value
   using the XOR operation with either the original or modified next element.
3. The transformation is possible if all elements can be matched through this process.

Time Complexity: O(n) per test case
Space Complexity: O(1) additional space
"""

import sys


def can_transform_to_target():
    """
    Determines if array A can be transformed into array B using adjacent XOR operations.

    Returns:
        str: "YES" if transformation is possible, "NO" otherwise
    """
    n = int(sys.stdin.readline())
    arr_a = list(map(int, sys.stdin.readline().split()))
    arr_b = list(map(int, sys.stdin.readline().split()))

    # The last element must match exactly as it can't be modified
    if arr_a[-1] != arr_b[-1]:
        return "NO"

    # Check each element from the second last to the first
    for i in range(n - 2, -1, -1):
        if arr_a[i] != arr_b[i]:
            # Check if we can get the target value by XORing with either:
            # 1. The original next element (A[i+1])
            # 2. The modified next element (B[i+1] if it was changed)
            if (
                arr_a[i] ^ arr_a[i + 1] != arr_b[i]
                and arr_a[i] ^ arr_b[i + 1] != arr_b[i]
            ):
                return "NO"

    return "YES"


def main():
    """Main function to handle multiple test cases."""
    t = int(sys.stdin.readline())
    for _ in range(t):
        print(can_transform_to_target())


if __name__ == "__main__":
    main()
