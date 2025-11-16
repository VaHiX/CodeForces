# Problem: CF 1997 A - Strong Password
# https://codeforces.com/contest/1997/problem/A

"""
Problem: Strong Password
Algorithm/Techniques: Greedy approach, string manipulation
Time Complexity: O(n) per test case, where n is the length of the string
Space Complexity: O(1) additional space (not counting input/output)

The solution aims to insert one character into the string to maximize the typing time.
The typing time is defined as:
- First character: 2 seconds
- Each subsequent character: 1 second if same as previous, 2 seconds otherwise

Strategy:
1. If there's a pair of consecutive same characters, insert a different character
   to break the sequence and increase time.
2. If no such pair exists, the string is alternating or all same.
   - If length is 1, append 'b' (or 'a' if 'b' not possible).
   - If length is 2 or more, try inserting a character that breaks the first
     two characters' pattern, or if both are same, insert a different one in
     the beginning (to increase the time).
"""

test_case = int(input())
for i in range(test_case):
    s = input()
    n = len(s)
    ans = -1
    # Find first consecutive identical characters
    for j in range(n - 1):
        if s[j] == s[j + 1]:
            ans = j
            break
    # If no consecutive same characters
    if ans == -1 and n >= 2:
        # Try to insert a character at the start that breaks the pattern
        for t in "abc":
            if t != s[0] and t != s[1]:
                print(s[0] + t + s[1:])
                break
    # If string is of length 1
    if ans == -1 and n == 1:
        for t in "ab":
            if t != s[0]:
                print(s + t)
                break
    # If consecutive same characters exist
    if ans != -1 and s[ans] == "a":
        # Insert 'b' to break the pattern
        print(s[: ans + 1] + "b" + s[ans + 1 :])
    elif ans != -1 and s[ans] != "a":
        # Insert 'a' to break the pattern
        print(s[: ans + 1] + "a" + s[ans + 1 :])


# https://github.com/VaHiX/CodeForces/