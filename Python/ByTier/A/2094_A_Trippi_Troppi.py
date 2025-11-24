# Problem: CF 2094 A - Trippi Troppi
# https://codeforces.com/contest/2094/problem/A

"""
Task: Generate modern country names by taking the first letter of each of three words in the ancient name.
Algorithm: String processing
Time Complexity: O(t * n) where t is number of test cases and n is average length of input strings
Space Complexity: O(n) for storing the result string

Input Format:
- First line: integer t (number of test cases)
- Next t lines: three space-separated strings representing ancient country name

Output Format:
- For each test case: first letter of each string concatenated together
"""

for _ in range(int(input())):  # Read number of test cases and iterate
    print("".join(w[0] for w in input().split()))  # Split input line into words, take first character of each word, join them


# https://github.com/VaHiX/codeForces/