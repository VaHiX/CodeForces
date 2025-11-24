# Problem: CF 2130 D - Stay or Mirror
# https://codeforces.com/contest/2130/problem/D

"""
D. Stay or Mirror
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

You are given a permutation p_1, p_2, ..., p_n of length n.
You have to build an array a_1, a_2, ..., a_n in the following way:

for each 1 <= i <= n, set either a_i = p_i or a_i = 2n - p_i. 
Find the minimum possible number of inversions in the array a_1, a_2, ..., a_n.
An inversion in the array a_1, a_2, ..., a_n is a pair of indices (i, j) such that 1 <= i < j <= n and a_i > a_j.

Algorithms/Techniques:
- For each element in the permutation, we decide whether to keep it as is or mirror it
- For each position, calculate the cost of keeping vs mirroring based on inversions
- Time Complexity: O(n^2) per test case
- Space Complexity: O(n)

Code:
"""

def solve():
    test_cases = int(input())
    for _ in range(test_cases):
        n = int(input())
        permutation = list(map(int, input().split()))
        total_operations = 0
        for current_idx in range(n):
            greater_before = 0
            # Count how many elements before current element are greater than it
            for prev_idx in range(current_idx):
                if permutation[prev_idx] > permutation[current_idx]:
                    greater_before += 1
            # Calculate operations needed if we mirror the current element
            mirror_operations = n - permutation[current_idx] - greater_before
            # Choose minimum between keeping and mirroring
            total_operations += min(greater_before, mirror_operations)
        print(total_operations)


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/codeForces/