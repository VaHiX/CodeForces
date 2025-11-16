# Problem: CF 1884 B - Haunted House
# https://codeforces.com/contest/1884/problem/B

"""
Code Purpose:
This code solves the problem of determining the minimum number of adjacent swaps required to make a binary number divisible by 2^i for each i from 1 to n. The approach uses a reverse traversal to count the number of 1s to the right of each position, and then builds a prefix sum array to efficiently compute the number of swaps needed for each power of 2.

Algorithms/Techniques:
- Reverse iteration to count 1s to the right of each bit
- Prefix sum technique for efficient range queries
- Greedy approach to determine minimum swaps for divisibility by 2^i

Time Complexity: O(n) per test case, where n is the length of the binary string. Each operation like traversal and prefix sum computation is linear.
Space Complexity: O(n) for storing the reversed counts and prefix sums.

"""

import sys

input = sys.stdin.read


def main():
    data = input().strip().split()
    index = 0
    t = int(data[index])  # Read number of test cases
    index += 1
    results = []
    for _ in range(t):
        n = int(data[index])  # Read length of binary string
        index += 1
        s = data[index]  # Read binary string
        index += 1
        v = []  # List to store count of 1s to the right of each position (reversed)
        cur = 0  # Counter for 1s seen so far from right
        # Traverse from right to left to count 1s to the right of each position
        for p in range(n - 1, -1, -1):
            if s[p] == "1":
                cur += 1  # Increment counter if current bit is 1
            else:
                v.append(cur)  # Append count of 1s to the right when bit is 0
        # Convert list to prefix sum from right to left (in correct order)
        for p in range(1, len(v)):
            v[p] += v[p - 1]
        result = []  # List to store results for current test case
        # For each position, we output either the number of operations or -1 if impossible
        for p in range(n):
            if p < len(v):
                result.append(str(v[p]))  # If within bounds, output the count
            else:
                result.append("-1")  # If out of bounds, it's impossible to achieve
        results.append(" ".join(result))  # Join results for current test case
    for result in results:
        print(result)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/