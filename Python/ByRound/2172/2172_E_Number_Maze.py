# Problem: CF 2172 E - Number Maze
# https://codeforces.com/contest/2172/problem/E

"""
Code Purpose:
This code solves the "Number Maze" problem where given a base numeric code (12, 123, or 1234),
it computes all permutations of its digits, sorts them in ascending order, and then compares
two specific permutations to determine the number of matching digits in value and position (A)
and the number of matching digits in value but not position (B).

Approach:
1. Precompute and store all permutations of digits for each valid base code (12, 123, 1234)
   in sorted order in a dictionary.
2. For each test case, retrieve the j-th and k-th permutations (1-indexed).
3. Compare the two strings digit by digit:
   - Count digits that match in both value and position (A).
   - Total digits minus A gives B.
4. Output result in the format xAyB.

Time Complexity: O(1) per test case
Space Complexity: O(1) overall (fixed sized dictionaries and inputs)

Algorithms/Techniques:
- Precomputation of permutations
- String comparison
- Fixed-size lookup table
"""

dic = {
    12: [12, 21],                    # Precomputed permutations for 12
    123: [123, 132, 213, 231, 312, 321], # Precomputed permutations for 123
    1234: [                           # Precomputed permutations for 1234
        1234,
        1243,
        1324,
        1342,
        1423,
        1432,
        2134,
        2143,
        2314,
        2341,
        2413,
        2431,
        3124,
        3142,
        3214,
        3241,
        3412,
        3421,
        4123,
        4132,
        4213,
        4231,
        4312,
        4321,
    ],
}
t = int(input())                      # Read number of test cases
for _ in range(t):                    # Process each test case
    n, j, k = map(int, input().split())  # Read n, j, k
    a, b = dic[n][j - 1], dic[n][k - 1]  # Get j-th and k-th permutations (1-indexed)
    a, b = str(a), str(b)              # Convert integers to strings for easy comparison
    le = len(a)                        # Length of the code
    cnt1 = 0                           # Counter for correct position matches (A)
    for i in range(le):                # Iterate through each digit
        if a[i] == b[i]:               # If digits match at same index
            cnt1 += 1                  # Increment A count
    print(f"{cnt1}A{le - cnt1}B")      # Print result in required format (A B)


# https://github.com/VaHiX/CodeForces/