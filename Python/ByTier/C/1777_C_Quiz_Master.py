# Problem: CF 1777 C - Quiz Master
# https://codeforces.com/contest/1777/problem/C

"""
Quiz Master Problem Solution

Algorithm:
- Use sliding window technique with precomputed divisors to find the minimum difference
  between smartness values in a valid team that covers all topics.
- Precompute divisors for all numbers up to MAX_VAL using a sieve-like approach.
- For each test case, use two pointers to maintain a window of students that covers all topics.
- Track the number of covered topics and update the minimum difference accordingly.

Time Complexity: O(MAX_VAL + n * log(MAX_VAL) + m) where MAX_VAL = 100001,
                 n is the number of students, m is the number of topics.
                 Precomputation takes O(MAX_VAL * log(MAX_VAL)),
                 each test case takes O(n * log(MAX_VAL)) in worst case.
Space Complexity: O(MAX_VAL^2) for storing divisors, but optimized to O(MAX_VAL * average_divisors) 
                  which is acceptable for the constraints.

The solution uses a sliding window to efficiently find the minimal team difference
that covers all required topics, leveraging precomputed divisor information for fast topic lookup.
"""

import sys

MAX_VAL = 100001
divisors = [[] for _ in range(MAX_VAL)]
precomputed = False


def precompute_divisors_once():
    """
    Precomputes divisors for all numbers up to MAX_VAL - 1.
    divisors[s] will store a list of all d such that s % d == 0.
    This function is called only once.
    """
    global precomputed
    if precomputed:
        return
    for i in range(1, MAX_VAL):
        for j in range(i, MAX_VAL, i):
            divisors[j].append(i)
    precomputed = True


def solve():
    """
    Solves a single test case for the Quiz Master problem.
    """
    n, m = map(int, sys.stdin.readline().split())
    a = list(map(int, sys.stdin.readline().split()))
    a.sort()

    min_overall_diff = float("inf")
    left_ptr = 0

    topic_counts = [0] * (m + 1)

    covered_topics_count = 0

    for right_ptr in range(n):
        current_student_smartness = a[right_ptr]

        for topic in divisors[current_student_smartness]:
            if topic <= m:
                if topic_counts[topic] == 0:
                    covered_topics_count += 1
                topic_counts[topic] += 1

        while covered_topics_count == m:
            current_diff = a[right_ptr] - a[left_ptr]
            min_overall_diff = min(min_overall_diff, current_diff)

            if min_overall_diff == 0:
                sys.stdout.write("0\n")
                return

            departing_student_smartness = a[left_ptr]
            for topic in divisors[departing_student_smartness]:
                if topic <= m:
                    topic_counts[topic] -= 1
                    if topic_counts[topic] == 0:
                        covered_topics_count -= 1
            left_ptr += 1

            if left_ptr > right_ptr + 1 and covered_topics_count < m:
                break

    if min_overall_diff == float("inf"):
        sys.stdout.write("-1\n")
    else:
        sys.stdout.write(str(min_overall_diff) + "\n")


precompute_divisors_once()

num_test_cases = int(sys.stdin.readline())
for _ in range(num_test_cases):
    solve()


# https://github.com/VaHiX/CodeForces/