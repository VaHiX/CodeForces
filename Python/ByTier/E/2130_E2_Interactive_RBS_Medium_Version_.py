"""
Interactive Problem: Regular Bracket Sequence (RBS) - Medium Version

This script solves an interactive problem where we need to determine a valid Regular Bracket Sequence (RBS)
of length n, where each character is either '(' or ')' and the sequence is properly nested.

The solution uses binary search to find a pivot point and then processes the sequence in chunks
of 8 characters to minimize the number of queries, which is crucial for the interactive nature of the problem.

Time Complexity: O(n) queries with O(n) total characters
Space Complexity: O(n) additional space
"""


def send_query(positions):
    """Send a query to the judge with the given positions.

    Args:
        positions: List of 1-based indices to query

    Returns:
        int: The number of balanced substrings in the queried sequence
    """
    print("?", len(positions), *positions, flush=True)
    return int(input())


def send_answer(bracket_sequence):
    """Send the final answer to the judge.

    Args:
        bracket_sequence: List of characters representing the bracket sequence
    """
    print("!", "".join(bracket_sequence), flush=True)


def main():
    # Read number of test cases
    test_cases = int(input())

    for _ in range(test_cases):
        # Read the length of the sequence (n)
        n = int(input())

        # Initialize the sequence with placeholders (1-based indexing)
        bracket_sequence = [" "] * (n + 1)

        # Phase 1: Find a pivot point where the sequence becomes unbalanced
        # We'll find the smallest prefix that has more closing than opening brackets
        if send_query(range(1, n + 1)) == 0:
            # If the entire sequence is balanced, the first and last must be a matching pair
            first_unbalanced_pos = 1
            pivot_pos = n
        else:
            # Binary search to find the first position where the sequence becomes unbalanced
            left, right = 2, n
            first_unbalanced_pos = -1

            while left <= right:
                mid = (left + right) // 2
                if send_query(range(1, mid + 1)) > 0:
                    first_unbalanced_pos = mid
                    right = mid - 1
                else:
                    left = mid + 1
            pivot_pos = first_unbalanced_pos - 1

        # Phase 2: Process the sequence in chunks of 8 characters
        for chunk_start in range(1, n + 1, 8):
            # Get up to 8 indices in the current chunk
            chunk_indices = [min(pos, n) for pos in range(chunk_start, chunk_start + 8)]

            # Build a query that will help us determine the bracket type for each position
            # We use a binary encoding scheme to determine multiple brackets in one query
            query = []
            for bit_pos in range(7, -1, -1):
                # For each bit position, create a pattern that helps identify the bracket type
                # The pattern is [current_pos, pivot, pivot] repeated 2^bit_pos times
                if chunk_start + (7 - bit_pos) <= n:  # Check if index is within bounds
                    current_pos = chunk_indices[7 - bit_pos]
                    query.extend([current_pos, pivot_pos, pivot_pos] * (1 << bit_pos))

            # Send the query and get the result
            query_result = send_query(query)

            # Decode the result to determine each bracket type
            for bit_pos in range(7, -1, -1):
                if chunk_start + (7 - bit_pos) <= n:  # Check if index is within bounds
                    current_pos = chunk_indices[7 - bit_pos]
                    # The bit at position j tells us if this is an opening or closing bracket
                    if (query_result >> bit_pos) & 1:
                        bracket_sequence[current_pos] = "("
                    else:
                        bracket_sequence[current_pos] = ")"

        # Send the final answer
        send_answer(bracket_sequence[1:])  # Skip the 0th index (1-based to 0-based)


if __name__ == "__main__":
    main()
