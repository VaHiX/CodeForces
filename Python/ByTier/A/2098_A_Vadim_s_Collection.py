# Problem: CF 2098 A - Vadim's Collection
# https://codeforces.com/contest/2098/problem/A

"""
Task: Rearrange digits of a beautiful phone number to form the smallest possible beautiful phone number.

A beautiful phone number is defined as a 10-digit string where the i-th digit from the left is at least (10 - i).
For example:
- First digit >= 9
- Second digit >= 8
- ...
- Tenth digit >= 0

Algorithm:
This solution attempts to sort the digits greedily, ensuring that the resulting number still satisfies the beautiful condition.
The approach involves swapping digits to minimize the number while respecting constraints.

Time Complexity: O(1) - Since the input size is fixed at 10 digits, all operations are constant time.
Space Complexity: O(1) - Only using a fixed amount of additional space for the list of digits.

Techniques:
- Greedy approach with digit swapping
- Constraint-based sorting
"""

for _ in range(int(input())):
    s = input()
    l = [int(i) for i in s]  # Convert string to list of integers
    
    # The core logic: for each pair of positions (i, j), try to swap them if it helps form a smaller number
    # while maintaining the beautiful phone number constraint.
    for i in range(10):
        for j in range(i + 1, 10):
            # Check if swapping makes a valid improvement under constraints:
            # l[j] >= (10 - i - 1) ensures the new value at position i satisfies the minimum requirement
            # l[j] < l[i] checks that we are actually decreasing the larger digit to make smaller number
            if l[j] >= 10 - i - 1 and l[j] < l[i]:
                l[j], l[i] = l[i], l[j]  # Swap the digits

    print("".join([str(i) for i in l]))  # Convert back to string and output


# https://github.com/VaHiX/codeForces/