# Problem: CF 1799 C - Double Lexicographically Minimum
# https://codeforces.com/contest/1799/problem/C

"""
Algorithm: Double Lexicographically Minimum
Techniques: Greedy, String manipulation, Sorting

Time Complexity: O(n * log(n)) due to sorting, where n is the length of the string
Space Complexity: O(n) for storing the characters and result string

Approach:
1. Sort the input string to get the lexicographically smallest arrangement.
2. Identify pairs of identical characters (build a "palindrome core").
3. Handle cases based on remaining characters:
   - If there are 2 or fewer remaining characters, append them to the palindrome core.
   - If the last character is same as the one after the core, form a specific structure.
   - Else, use the first remaining character, reverse the rest, and form the string.
4. Compare the constructed string with its reverse and output the lexicographically smaller one.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()

for _ in range(int(input())):
    word = [i for i in input()]
    N = len(word)
    word.sort()
    palin = []
    i = 0
    # Build the palindrome core by pairing identical characters
    while i + 1 < N and word[i] == word[i + 1]:
        palin.append(word[i])
        i += 2
    # If remaining characters are 2 or less
    if N - i <= 2:
        res = "".join(palin + word[i:] + palin[::-1])
    # If last character matches the next-to-last character, create balanced structure
    elif word[i + 1] == word[-1]:
        res = "".join(
            palin
            + [word[i + 1]] * ((N - i - 1) // 2)
            + [word[i]]
            + [word[i + 1]] * (N - i - 1 - ((N - i - 1) // 2))
            + palin[::-1]
        )
    # Otherwise, form the structure with first remaining char in middle
    else:
        res = "".join(palin + [word[i]] + word[i + 1 :][::-1] + palin[::-1])
    # Output the lexicographically smaller between res and its reverse
    if res > res[::-1]:
        print(res)
    else:
        print(res[::-1])


# https://github.com/VaHiX/CodeForces/