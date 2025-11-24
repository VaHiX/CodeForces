# Problem: CF 2118 A - Equal Subsequences
# https://codeforces.com/contest/2118/problem/A

"""
Task: Construct a perfect bitstring of length n with exactly k 1s.
A perfect bitstring has equal number of "101" and "010" subsequences.

Algorithm/Technique:
- The approach uses a greedy construction method.
- Place k 1s followed by (n - k) 0s to form the string.
- This ensures that all 1s are at the start, minimizing transitions between 0 and 1,
  which balances the count of "101" and "010" subsequences.

Time Complexity: O(n) per test case, due to string construction.
Space Complexity: O(n) per test case, for storing the result string.

Input:
- t (number of test cases)
- For each test case: n (length), k (number of 1s)

Output:
- A perfect bitstring of length n with exactly k 1s.
"""

for _ in range(int(input())):  # Process each test case
    n, k = map(int, input().split())  # Read n and k
    s = "1" * k + "0" * (n - k)  # Create string with k 1s followed by (n-k) 0s
    print(s)  # Output the constructed bitstring


# https://github.com/VaHiX/codeForces/