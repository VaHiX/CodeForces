# Problem: CF 2130 E1 - Interactive RBS (Easy Version)
# https://codeforces.com/contest/2130/problem/E1

"""
Interactive Problem: Regular Bracket Sequence (RBS) - Easy Version

This script solves an interactive problem where we need to determine a valid Regular Bracket Sequence (RBS)
of length n, where each character is either '(' or ')' and the sequence is properly nested.

Approach:
1. Find the first position where the sequence becomes unbalanced using binary search
2. Use this position to determine a pivot point
3. Determine the bracket types for pairs of positions using a clever encoding scheme
4. Handle the last position separately if n is odd

Algorithms/Techniques:
- Binary Search to locate first unbalanced position
- Query-based pattern recognition to deduce bracket types
- Clever encoding scheme to map query results to bracket types

Time Complexity: O(n) queries with O(1) per query
Space Complexity: O(n) for storing the result

E1. Interactive RBS (Easy Version)
"""

import sys


def main():
    test_cases = int(input())
    for _ in range(test_cases):
        sequence_length = int(input())
        left, right = 2, sequence_length
        found_unbalanced = False
        first_unbalanced_pos = -1
        # Binary search to find the first position where the prefix becomes unbalanced
        while left <= right:
            mid = (left + right) // 2
            print("?", mid, *range(1, mid + 1))
            sys.stdout.flush()
            balanced_substrings = int(input())
            if balanced_substrings > 0:  # If there exists a regular substring in this prefix
                first_unbalanced_pos = mid
                right = mid - 1
                found_unbalanced = True
            else:
                left = mid + 1
        # Determine pivot points based on binary search result
        if found_unbalanced:
            right_bracket_pos = first_unbalanced_pos  # Position of a ')' that causes imbalance
            left_bracket_pos = first_unbalanced_pos - 1  # Position of '(' just before it
        else:
            # No unbalance found, implies all brackets are correctly nested (not used in this context)
            left_bracket_pos, right_bracket_pos = sequence_length, 1
        # Map query response codes to bracket pattern strings
        bracket_patterns = {
            1: [")", ")"],
            2: [")", "("],
            3: ["(", ")"],
            4: ["(", "("],
        }
        bracket_sequence = []
        # Process pairs of indices for bracket deduction
        for i in range(1, sequence_length, 2):
            print(
                "?",
                7,  # Number of queries to perform
                i,  # First index
                right_bracket_pos,  # Second index (pivot)
                left_bracket_pos,   # Third index (pivot)
                right_bracket_pos,  # Fourth index (pivot)
                right_bracket_pos,  # Fifth index (pivot)
                i + 1,  # Sixth index
                right_bracket_pos,  # Seventh index (pivot)
            )
            sys.stdout.flush()
            pattern_code = int(input())
            bracket_sequence.extend(bracket_patterns[pattern_code])
        # Handle odd-length sequences - process the last single character
        if sequence_length % 2 == 1:
            print("?", 2, left_bracket_pos, sequence_length)  # Query for the last pair
            sys.stdout.flush()
            last_bracket_type = int(input())
            bracket_sequence.append(")" if last_bracket_type == 1 else "(")
        # Output the final bracket sequence
        print("!", *bracket_sequence, sep="")
        sys.stdout.flush()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/