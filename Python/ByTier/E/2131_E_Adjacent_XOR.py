# Problem: CF 2131 E - Adjacent XOR
# https://codeforces.com/contest/2131/problem/E

"""
E. Adjacent XOR
time limit per test2 seconds
memory limit per test256 megabytes

Problem: CF2131E - Adjacent XOR
This program determines if array A can be transformed into array B using the following operation:
- Choose an index i (0 ≤ i < n-1) and set A[i] = A[i] XOR A[i+1]
The operation can be performed any number of times (including zero).

Approach:
1. The last element of A must match the last element of B since it can't be modified.
2. For each element from second last to first, check if it can be transformed into the target value
   using the XOR operation with either the original or modified next element.
3. The transformation is possible if all elements can be matched through this process.

Algorithms/Techniques:
- Greedy approach with backward iteration
- XOR properties: a ^ b = c => a ^ c = b

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
    
    # Last element must match since it cannot be modified
    if arr_a[-1] != arr_b[-1]:
        return "NO"
    
    # Iterate from second last to first element (backwards)
    for i in range(n - 2, -1, -1):
        # If current element doesn't match target value
        if arr_a[i] != arr_b[i]:
            # Check if either original or modified next element can produce target
            # arr_a[i] ^ arr_a[i+1] -> what happens when we apply operation on index i
            # arr_a[i] ^ arr_b[i+1] -> what would be needed to get target from current value
            
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


# https://github.com/VaHiX/codeForces/