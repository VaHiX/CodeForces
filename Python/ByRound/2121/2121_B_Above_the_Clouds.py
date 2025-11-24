# Problem: CF 2121 B - Above the Clouds
# https://codeforces.com/contest/2121/problem/B

# B. Above the Clouds
# Time complexity: O(n), where n is the length of the string s
# Space complexity: O(1), only using a constant amount of extra space

# For each test case, read input and process the string
for s in [*open(0)][2::2]:
    # Get all unique characters from the string (excluding first and last)
    # Count occurrences of each character in the string
    # If max count is less than 2, it means at most one character appears more than once
    # This implies we can split s into a, b, c such that b is substring of a+c
    print("YNeos"[max(map(s.count, {*s[1:-2]})) < 2 :: 2])


# https://github.com/VaHiX/codeForces/