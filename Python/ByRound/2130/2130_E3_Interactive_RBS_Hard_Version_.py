"""
Interactive Problem: Regular Bracket Sequence (RBS) - Hard Version

This script solves the interactive problem where we need to determine a valid Regular Bracket Sequence (RBS)
of length 2n, where each character is either '(' or ')' and the sequence is properly nested.

The solution uses binary search to find matching pairs and processes the sequence in chunks
to minimize the number of queries, which is crucial for the interactive nature of the problem.

Time Complexity: O(n log n) queries, each of size O(n)
Space Complexity: O(n) additional space
"""

import sys


def main():
    # Read number of test cases
    test_cases = int(input())

    for _ in range(test_cases):
        # Read the length of the sequence (2n)
        n = int(input())

        # Phase 1: Find the first mismatched pair using binary search
        # We'll find the smallest prefix that has more closing than opening brackets
        print("?", n, " ".join(str(x) for x in range(1, n + 1)))
        sys.stdout.flush()

        if input() == "0":
            # No mismatch in the entire sequence, which means the first and last form a pair
            open_pos, close_pos = n, 1
        else:
            # Binary search to find the first position where the sequence becomes invalid
            left, right = 1, n
            while left < right:
                mid = (left + right) // 2
                print("?", mid, " ".join(str(x) for x in range(1, mid + 1)))
                sys.stdout.flush()
                if int(input()) > 0:
                    right = mid
                else:
                    left = mid + 1
            # The first invalid position is 'left', so the matching pair is (left-1, left)
            open_pos, close_pos = left - 1, left

        # Initialize the sequence with the found pair
        sequence = bytearray(n + 1)  # 1-based indexing
        sequence[open_pos] = ord("(")
        sequence[close_pos] = ord(")")

        # Phase 2: Process remaining characters in chunks to minimize queries
        current_pos = 1
        while True:
            query_blocks = []  # Stores the positions we're querying in this batch
            current_query = []  # The actual query being built
            block_count = 0  # Number of blocks in current query
            total_balanced = 0  # Expected balanced substrings if all '?' are '('

            while True:
                # Add separator between blocks (if not the first block)
                block_separator = [close_pos] if current_query else []

                # Find next unassigned position
                while current_pos <= n and sequence[current_pos]:
                    current_pos += 1

                if current_pos > n:
                    break  # No more positions to process

                # Create a balanced block pattern around the current position
                left_balance = (1 << (block_count // 2)) - 1
                right_balance = (1 << ((block_count + 1) // 2)) - 1

                # Build the block pattern: [open_pos, close_pos] * left_balance + [current_pos, close_pos] + [open_pos, close_pos] * right_balance
                block_pattern = (
                    [open_pos, close_pos] * left_balance
                    + [current_pos, close_pos]
                    + [open_pos, close_pos] * right_balance
                )

                # Check if we can add this block to the current query
                if len(current_query) + len(block_pattern) > 1000:  # Query size limit
                    break

                # Calculate expected balanced substrings for this block
                block_size = left_balance + right_balance + 1
                total_balanced += block_size * (block_size + 1) // 2

                # Update query information
                query_blocks.append(current_pos)
                current_query += block_pattern
                block_count += 1
                current_pos += 1

            if not current_query:
                break  # No more positions to process

            # Send the query and get the actual number of balanced substrings
            print("?", len(current_query), " ".join(str(pos) for pos in current_query))
            sys.stdout.flush()

            # Calculate the difference to determine the actual bracket types
            actual_balanced = int(input())
            diff = total_balanced - actual_balanced

            # Decode the bracket types from the difference
            for pos in reversed(query_blocks):
                sequence[pos] = ord(")" if (diff & 1) else "(")
                diff >>= 1

        # Output the final sequence (skip the 0th index)
        print("!", sequence[1:].decode())
        sys.stdout.flush()


if __name__ == "__main__":
    main()
