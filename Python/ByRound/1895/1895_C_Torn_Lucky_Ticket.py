# Problem: CF 1895 C - Torn Lucky Ticket
# https://codeforces.com/contest/1895/problem/C

"""
Algorithm: Dynamic Programming with Prefix Sums
Techniques: 
- Prefix sums for efficient subarray sum calculation
- HashMap (defaultdict) for counting occurrences
- Iterative construction of valid combinations

Time Complexity: O(5 * n * max_len) where max_len is at most 5, so effectively O(n)
Space Complexity: O(n) for the dictionary storage

This solution groups ticket pieces by their total digit sum and length,
then for each piece, it calculates how many other pieces can be concatenated
to form a lucky ticket.
"""

from collections import defaultdict

MAX_DIGITS = 9


def solve(N, L):

    # Initialize data structures for tracking whole and partial sums
    whole = [defaultdict(int) for _ in range(1 + MAX_DIGITS)]
    part = [defaultdict(int) for _ in range(1 + MAX_DIGITS)]

    for piece in L:
        s = len(piece)
        prefix = [0]

        # Build prefix sum array for current piece
        for c in piece:
            prefix.append(prefix[-1] + ord(c) - ord("0"))

        total_sum = prefix[s]

        # Store the total sum for the full piece
        whole[s][total_sum] += 1

        # Handle all possible splits (for odd lengths, there's a middle element)
        part[s][total_sum] += 1

        # For each valid split point, update the partial sums
        for k in range(1, (s + 1) // 2):
            # Update the counts for the adjusted difference between halves
            part[s - 2 * k][total_sum - 2 * prefix[k]] += 1
            part[s - 2 * k][2 * prefix[s - k] - total_sum] += 1

    result = 0

    # For each possible length, accumulate valid combinations
    for length in range(1, 1 + MAX_DIGITS):
        for sum_value, count in whole[length].items():
            # Multiply the frequency of current sum with matching sums from part
            result += count * part[length][sum_value]

    return result


if __name__ == "__main__":
    N = int(input())
    L = input().split()
    print(solve(N, L))


# https://github.com/VaHiX/CodeForces/