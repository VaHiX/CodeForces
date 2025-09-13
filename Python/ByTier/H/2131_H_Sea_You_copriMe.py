"""
Problem: CF2131H - Sea You copriMe

This program solves a graph theory problem involving finding specific patterns in a graph
where nodes represent numbers and edges connect coprime numbers.

Approach:
1. Precompute smallest prime factors (SPF) for efficient prime factorization
2. For each test case, build a graph where nodes are numbers and edges connect coprime pairs
3. Find specific patterns (4-node cycles or paths) in the graph based on node degrees
4. Return the indices of nodes forming the desired pattern or [-1] if not found

Time Complexity: O(MAX log log MAX) for sieve precomputation + O(T * n^2) for test cases
Space Complexity: O(MAX) for the sieve
"""

import sys
from math import gcd
from typing import List, Set, Generator, Tuple

# Constants
MAX_NUMBER = 1_000_001

# Precompute smallest prime factors (SPF) for efficient factorization
smallest_prime_factor = [0] * MAX_NUMBER
for prime in range(2, MAX_NUMBER):
    if not smallest_prime_factor[prime]:
        for multiple in range(prime, MAX_NUMBER, prime):
            if not smallest_prime_factor[multiple]:
                smallest_prime_factor[multiple] = prime


def get_distinct_prime_factors(n: int) -> Generator[int, None, None]:
    """
    Generator function to yield all distinct prime factors of n.

    Args:
        n: The number to factorize

    Yields:
        int: Distinct prime factors of n
    """
    while n > 1:
        p = smallest_prime_factor[n]
        while n % p == 0:
            n //= p
        yield p


def get_square_free_divisors(n: int) -> List[int]:
    """
    Returns all square-free divisors of n, with sign indicating number of prime factors.

    Args:
        n: The number to find divisors for

    Returns:
        List[int]: List of divisors where sign indicates parity of prime factors
    """
    divisors = [1]

    for prime in get_distinct_prime_factors(n):
        # For each existing divisor, add a new divisor multiplied by -prime
        # This helps in inclusion-exclusion principle calculations
        current_length = len(divisors)
        for i in range(current_length):
            divisors.append(divisors[i] * (-prime))

    return divisors


def find_coprime_pairs(numbers: List[int]) -> List[List[int]]:
    """
    Find all pairs of indices (i,j) where numbers[i] and numbers[j] are coprime.

    Args:
        numbers: List of integers

    Returns:
        List of lists where each inner list contains indices of coprime pairs
    """
    n = len(numbers)
    return [
        [i, j]
        for i in range(n)
        for j in range(i + 1, n)
        if gcd(numbers[i], numbers[j]) == 1
    ]


def solve() -> List[int]:
    """
    Solves a single test case for the Sea You copriMe problem.

    Returns:
        List[int]: Indices of nodes forming the required pattern or [-1] if not found
    """
    # Read input
    n, m = map(int, input().split())
    numbers = list(map(int, input().split()))

    # Initialize count of numbers sharing each square-free divisor
    divisor_count = [0] * (m + 1)

    # Count occurrences of each square-free divisor
    for num in numbers:
        for divisor in get_square_free_divisors(num):
            divisor_count[abs(divisor)] += 1

    # Calculate degree of each node (number of coprime neighbors)
    degrees = [0] * n
    for i in range(n):
        for divisor in get_square_free_divisors(numbers[i]):
            # Use inclusion-exclusion to count coprime pairs
            sign = 1 if divisor > 0 else -1
            degrees[i] += sign * (divisor_count[abs(divisor)] - 1)

    def get_coprime_neighbors(node_idx: int) -> List[int]:
        """Returns indices of nodes that are coprime with the given node."""
        return [
            j
            for j in range(n)
            if j != node_idx and gcd(numbers[node_idx], numbers[j]) == 1
        ]

    # Find node with maximum degree
    max_degree_node = max(range(n), key=lambda x: degrees[x])

    # If all edges are connected to the max degree node, no solution exists
    if sum(degrees) == degrees[max_degree_node] * 2:
        return [-1]

    # Get neighbors of the max degree node
    neighbors = get_coprime_neighbors(max_degree_node)

    # Case 1: Max degree >= 3
    if degrees[max_degree_node] >= 3:
        # If all neighbors have degree 1, find a separate edge
        if all(degrees[t] == 1 for t in neighbors):
            used_nodes = {max_degree_node} | set(neighbors)
            for i in range(n):
                if i in used_nodes:
                    continue
                if degrees[i] > 0:  # Has at least one neighbor
                    j = get_coprime_neighbors(i)[0]
                    return [i, j, max_degree_node, neighbors[0]]

        # Look for a 4-cycle or appropriate pattern
        for y in neighbors:
            if degrees[y] == 1:
                continue
            for z in get_coprime_neighbors(y):
                if z in {y, max_degree_node}:
                    continue
                for t in neighbors:
                    if t not in {y, max_degree_node, z}:
                        return [max_degree_node, t, y, z]

    # Case 2: Max degree is 1
    if degrees[max_degree_node] == 1:
        y = neighbors[0]
        for i in range(n):
            if i in {max_degree_node, y}:
                continue
            if degrees[i] > 0:
                j = get_coprime_neighbors(i)[0]
                return [i, j, max_degree_node, y]

    # Case 3: Max degree is 2
    y, z = neighbors[0], neighbors[1]

    # Subcase 3.1: Both neighbors have degree 1
    if degrees[y] == 1 and degrees[z] == 1:
        for i in range(n):
            if i in {max_degree_node, y, z}:
                continue
            if degrees[i] > 0:
                j = get_coprime_neighbors(i)[0]
                return [i, j, max_degree_node, y]

    # Subcase 3.2: One neighbor has degree 2
    for first, second in [(y, z), (z, y)]:
        if degrees[first] == 2 and degrees[second] == 1:
            for t in get_coprime_neighbors(first):
                if t not in {max_degree_node, second}:
                    return [max_degree_node, second, first, t]

    # Subcase 3.3: Handle special case where neighbors form a triangle
    neighbor_neighbors = get_coprime_neighbors(y)
    for c in neighbor_neighbors:
        if c not in {max_degree_node, z}:
            return [c, y, max_degree_node, z]

    # No valid pattern found
    return [-1]


def main():
    """
    Main function to handle input/output for multiple test cases.
    """
    import sys

    input = sys.stdin.read
    data = input().split()

    idx = 0
    test_cases = int(data[idx])
    idx += 1

    results = []
    for _ in range(test_cases):
        n, m = int(data[idx]), int(data[idx + 1])
        idx += 2
        numbers = list(map(int, data[idx : idx + n]))
        idx += n

        # Save the current input position
        saved_idx = idx

        # Redirect input for the solve function
        import io
        import sys
        from contextlib import redirect_stdin

        # Create input string for this test case
        input_str = f"{n} {m}\n"
        input_str += " ".join(map(str, numbers)) + "\n"

        # Use StringIO to simulate stdin for the solve function
        with io.StringIO(input_str) as f:
            with redirect_stdin(f):
                result = solve()

        # Restore the original input position
        idx = saved_idx

        # Store the result (add 1 to convert to 1-based indexing)
        results.append([x + 1 for x in result])

    # Print all results
    for result in results:
        print(" ".join(map(str, result)))


if __name__ == "__main__":
    main()
