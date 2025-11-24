# Problem: CF 2130 C - Double Perspective
# https://codeforces.com/contest/2130/problem/C

"""
Problem: 2130C - Double Perspective
Algorithm: Greedy interval selection with sorting
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) to store the intervals and result

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
"""

def solve():
    test_cases = int(input())
    for _ in range(test_cases):
        num_intervals = int(input())
        intervals = []
        for idx in range(num_intervals):
            start, end = map(int, input().split())
            intervals.append((start, end, idx + 1))  # Store original index
        intervals.sort(key=lambda x: (x[0], -x[1]))  # Sort by start time, then by end time descending
        selected_intervals = []
        last_end = 0
        for interval in intervals:
            start, end, original_idx = interval
            if last_end < end:  # If current interval doesn't overlap with the last selected one
                last_end = end  # Update the end time of the last selected interval
                selected_intervals.append(original_idx)  # Select this interval
        print(len(selected_intervals))
        if selected_intervals:
            print(" ".join(map(str, selected_intervals)))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/codeForces/