# Problem: CF 1979 B - XOR Sequences
# https://codeforces.com/contest/1979/problem/B

"""
Algorithm: XOR Sequences

Purpose:
This code finds the length of the longest common subsegment between two infinite sequences
a_n = n XOR x and b_n = n XOR y, where x and y are distinct non-negative integers.

Approach:
The key insight is that for sequences a_n = n XOR x and b_n = n XOR y, a common subsegment
exists if and only if there's a shift in the XOR operation. The length of the longest
common subsegment is determined by the smallest power of 2 that divides the difference
d = x XOR y. This is given by d & -d, which isolates the lowest set bit in d.

Time Complexity: O(1) per test case
Space Complexity: O(1) for processing, O(t) for storing results where t is number of test cases

Techniques:
- Bit manipulation to find lowest set bit: d & -d
- Preprocessing of input data
"""

def longest_common_subsegment_length(x, y):
    # Calculate difference using XOR
    d = x ^ y

    # Return the lowest set bit of d, which represents the longest common subsegment length
    return d & -d


def process_test_cases(test_cases):
    results = []
    for x, y in test_cases:
        results.append(longest_common_subsegment_length(x, y))
    return results


import sys

input = sys.stdin.read
data = input().split()

t = int(data[0])
index = 1
test_cases = []
for _ in range(t):
    x = int(data[index])
    y = int(data[index + 1])
    test_cases.append((x, y))
    index += 2


results = process_test_cases(test_cases)


for result in results:
    print(result)


# https://github.com/VaHiX/CodeForces/