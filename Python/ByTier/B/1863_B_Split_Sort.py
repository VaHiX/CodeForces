# Problem: CF 1863 B - Split Sort
# https://codeforces.com/contest/1863/problem/B

"""
Code Purpose:
This code solves the "Split Sort" problem where we need to determine the minimum number of operations 
to sort a permutation by repeatedly splitting the array based on a pivot x and reordering elements.

Algorithm:
1. We track the positions of each element in the permutation.
2. Starting from the second element (index 2), we check if the current element appears after the previous element in the original array.
3. If so, it means that a swap is required to bring the previous element into its correct position.
4. For every such case, we decrement the number of swaps required.

Time Complexity: O(n), where n is the length of the input array. We traverse the array once to build position mappings and once to count required swaps.
Space Complexity: O(n), for storing the position mapping array.

Techniques:
- Position tracking using an auxiliary array.
- Greedy approach to counting necessary operations.
"""

def main():

    num_test_cases = int(input())

    for _ in range(num_test_cases):

        array_length = int(input())

        array_elements = list(map(int, input().split()))

        # Create an array to store the position of each element (1-indexed)
        element_positions = [0] * (array_length + 1)

        # Fill the position array: element_positions[value] = position
        for position, value in enumerate(array_elements, start=1):
            element_positions[value] = position

        # Initially assume we need to perform n-1 operations
        swaps_required = array_length - 1

        # For each element from 2 to n, check if it's in the correct relative order
        for i in range(2, array_length + 1):
            # If position of i is after position of (i-1), no operation needed for this pair
            if element_positions[i] > element_positions[i - 1]:
                swaps_required -= 1

        print(swaps_required)

        print()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/