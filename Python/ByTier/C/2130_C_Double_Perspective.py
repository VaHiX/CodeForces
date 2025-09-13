"""
Problem: 2130C - Double Perspective

This script solves a problem where we need to find the maximum number of non-overlapping intervals
that can be selected from a set of intervals, where each interval is represented by a start and end point.
The intervals are first sorted by their start time, and then we use a greedy algorithm to select
non-overlapping intervals with the earliest end times.

Approach:
1. Read the number of test cases
2. For each test case:
   a. Read the number of intervals
   b. Read each interval and store it with its original index
   c. Sort intervals by start time (and end time in descending order for tie-breaking)
   d. Use a greedy algorithm to select non-overlapping intervals
   e. Output the count of selected intervals and their original indices

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) to store the intervals and result
"""


def solve():
    # Read number of test cases
    test_cases = int(input())

    for _ in range(test_cases):
        # Read number of intervals
        num_intervals = int(input())
        intervals = []

        # Read each interval and store with its original index (1-based)
        for idx in range(num_intervals):
            start, end = map(int, input().split())
            intervals.append((start, end, idx + 1))  # (start, end, original_index)

        # Sort intervals by start time, and by end time in descending order for tie-breaking
        # This ensures we pick the interval that ends first when start times are equal
        intervals.sort(key=lambda x: (x[0], -x[1]))

        selected_intervals = []
        last_end = 0  # Tracks the end of the last selected interval

        for interval in intervals:
            start, end, original_idx = interval

            # If this interval starts after the last selected interval ends, select it
            if last_end < end:
                last_end = end
                selected_intervals.append(original_idx)

        # Output the results
        print(len(selected_intervals))
        if selected_intervals:  # Only print if there are selected intervals
            print(" ".join(map(str, selected_intervals)))


if __name__ == "__main__":
    solve()
