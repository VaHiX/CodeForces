"""
Interactive Problem: Regular Bracket Sequence (RBS) - Easy Version

This script solves an interactive problem where we need to determine a valid Regular Bracket Sequence (RBS)
of length n, where each character is either '(' or ')' and the sequence is properly nested.

Approach:
1. Find the first position where the sequence becomes unbalanced using binary search
2. Use this position to determine a pivot point
3. Determine the bracket types for pairs of positions using a clever encoding scheme
4. Handle the last position separately if n is odd

Time Complexity: O(n) queries with O(1) per query
Space Complexity: O(n) for storing the result
"""

import sys


def main():
    # Read number of test cases
    test_cases = int(input())

    for _ in range(test_cases):
        # Read the length of the sequence (n)
        sequence_length = int(input())

        # Phase 1: Find the first position where the sequence becomes unbalanced
        left, right = 2, sequence_length
        found_unbalanced = False
        first_unbalanced_pos = -1

        while left <= right:
            mid = (left + right) // 2
            # Query the first 'mid' positions
            print("?", mid, *range(1, mid + 1))
            sys.stdout.flush()

            # Get the number of balanced substrings in the queried range
            balanced_substrings = int(input())

            if balanced_substrings > 0:
                # Found a position where the sequence becomes unbalanced
                first_unbalanced_pos = mid
                right = mid - 1
                found_unbalanced = True
            else:
                left = mid + 1

        # Determine the pivot positions based on whether we found an unbalanced position
        if found_unbalanced:
            # The first unbalanced position and its predecessor form our pivot points
            right_bracket_pos = first_unbalanced_pos
            left_bracket_pos = first_unbalanced_pos - 1
        else:
            # If the entire sequence is balanced, use the first and last positions
            left_bracket_pos, right_bracket_pos = sequence_length, 1

        # Mapping from query results to bracket patterns for pairs of positions
        # The key represents the result of the query, and the value is a list of two brackets
        bracket_patterns = {
            1: [")", ")"],  # Both positions are closing brackets
            2: [")", "("],  # First is closing, second is opening
            3: ["(", ")"],  # First is opening, second is closing
            4: ["(", "("],  # Both positions are opening brackets
        }

        # Initialize the answer list
        bracket_sequence = []

        # Process the sequence in pairs
        for i in range(1, sequence_length, 2):
            # Query to determine the bracket types for positions i and i+1
            # The query is designed to encode the bracket types in the response
            print(
                "?",
                7,
                i,
                right_bracket_pos,
                left_bracket_pos,
                right_bracket_pos,
                right_bracket_pos,
                i + 1,
                right_bracket_pos,
            )
            sys.stdout.flush()

            # Get the encoded bracket pattern
            pattern_code = int(input())

            # Add the corresponding brackets to our sequence
            bracket_sequence.extend(bracket_patterns[pattern_code])

        # Handle the last position if the sequence length is odd
        if sequence_length % 2 == 1:
            # Query to determine the bracket type for the last position
            print("?", 2, left_bracket_pos, sequence_length)
            sys.stdout.flush()

            # The response tells us if it's an opening or closing bracket
            last_bracket_type = int(input())
            bracket_sequence.append(")" if last_bracket_type == 1 else "(")

        # Output the final answer
        print("!", *bracket_sequence, sep="")
        sys.stdout.flush()


if __name__ == "__main__":
    main()
