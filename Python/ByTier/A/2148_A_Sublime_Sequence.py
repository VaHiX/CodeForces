# Problem: CF 2148 A - Sublime Sequence
# https://codeforces.com/contest/2148/problem/A

"""
A. Sublime Sequence
time limit per test1 second
memory limit per test256 megabytes

Algorithm: 
- Create a sequence of length n alternating between x and -x, starting with x
- Sum all elements in the sequence
- Key insight: if n is even, each pair (x, -x) sums to 0; if n is odd, the last element is x

Time Complexity: O(1) - constant time operations
Space Complexity: O(1) - constant space usage
"""

for _ in range(int(input())):  # Read number of test cases
    x, n = map(int, input().split())  # Read x and n for current test case
    print(0 if n % 2 == 0 else x)  # If n is even, sum is 0; if odd, sum is x


# https://github.com/VaHiX/codeForces/