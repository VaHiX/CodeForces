# Problem: CF 1965 F - Conference
# https://codeforces.com/contest/1965/problem/F

"""
Algorithm/Techniques: 
- Interval processing using coordinate compression and heap-based sliding window technique
- Two-pass approach to find valid segments where each day has enough lecturers
- Counting valid consecutive day segments of length k using prefix/suffix sums
- Time complexity: O(n * log(n) + MAX_BOUND), Space complexity: O(MAX_BOUND)

The code processes lecturer availability intervals to compute how many ways there are 
to select a segment of k consecutive days for a conference, for each k from 1 to n.
It uses a min-heap to maintain available lecturers and a two-pass sliding window algorithm 
to determine valid segments. The final result counts valid segments of all lengths.
"""

import heapq


def process_intervals(
    number_of_intervals: int, intervals: list[tuple[int, int]]
) -> list[int]:
    """
    Processes lecturer availability intervals and calculates the number of valid conference segments for each k.

    Parameters:
        number_of_intervals (int): The total number of lecturers.
        intervals (list[tuple[int, int]]): A list of tuples where each tuple (l, r) represents the range of days a lecturer is available.

    Returns:
        list[int]: A list where the k-th index represents the number of ways to select a segment of k consecutive days.
    """
    MAX_BOUND = 200_001
    adjacency_list = [[] for _ in range(MAX_BOUND + 1)]
    collected_segments = []

    # Transform intervals using coordinate compression (reverse coordinates)
    for left_bound, right_bound in intervals:
        adjacency_list[MAX_BOUND - right_bound + 1].append(MAX_BOUND - left_bound + 1)

    # Two passes over the data to compute valid intervals
    for _ in range(2):
        collected_segments.clear()
        min_heap = []

        for coordinate in range(1, MAX_BOUND + 1):
            # Add all intervals starting at this coordinate
            for value in adjacency_list[coordinate]:
                heapq.heappush(min_heap, value)

            # Remove intervals that end before this coordinate
            while min_heap and min_heap[0] < coordinate:
                heapq.heappop(min_heap)

            # If a valid interval exists, record it
            if min_heap:
                collected_segments.append((coordinate, heapq.heappop(min_heap)))

        adjacency_list = [[] for _ in range(MAX_BOUND + 1)]

        # Reconstruct adjacency list using reversed coordinates again for next pass
        for left_val, right_val in collected_segments:
            adjacency_list[MAX_BOUND - right_val + 1].append(MAX_BOUND - left_val + 1)

    # Initialize counting arrays for left and right boundaries
    count_left = [0] * (MAX_BOUND + 1)
    count_right = [0] * (MAX_BOUND + 1)
    final_result = [0] * number_of_intervals

    # Count occurrences of left and right boundaries
    for left_val, right_val in collected_segments:
        count_left[left_val] += 1
        count_right[right_val] += 1

    current_right = 0
    running_sum = 0

    # Sliding window technique to count valid segments of different lengths
    for left_index in range(MAX_BOUND + 1):
        # Adjust window from the right if the current window size is valid
        while running_sum >= current_right - left_index + 1:
            current_right += 1
            running_sum += count_left[current_right]

        # If valid segment found, increment result for k = segment_length
        if left_index < current_right:
            final_result[current_right - left_index - 1] += 1

        # Decrement the count of the left value as we move window forward
        running_sum -= count_right[left_index]

    # Accumulate results from right to left to get cumulative counts
    for idx in range(number_of_intervals - 1, 0, -1):
        final_result[idx - 1] += final_result[idx]

    return final_result


def main() -> None:
    """
    Reads input, processes lecturer availability intervals, and prints the result.
    """
    number_of_intervals = int(input())
    intervals = [tuple(map(int, input().split())) for _ in range(number_of_intervals)]

    result = process_intervals(number_of_intervals, intervals)
    print("\n".join(str(value) for value in result))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/