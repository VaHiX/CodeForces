# Problem: CF 1888 A - Chemistry
# https://codeforces.com/contest/1888/problem/A

"""
Problem: Check if we can remove exactly k characters from a string such that the remaining characters can be rearranged into a palindrome.

Algorithm:
- Count frequency of each character in the string.
- A palindrome can have at most one character with odd frequency (for the middle element in odd-length palindromes).
- So, we count how many characters have odd frequencies.
- If we remove exactly k characters, we reduce the number of odd frequencies.
- To form a valid palindrome after removal:
    - We should be able to reduce the number of odd frequencies to at most 1.
    - This means we need to remove at least (odd_count - 1) characters.
    - But since we must remove exactly k characters, and we want to make sure we can have at most 1 odd frequency,
      we check if k >= (odd_count - 1).
    - Also, if k is greater than or equal to the number of characters in string, that's a special case but not applicable here since k < n.

Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(1), since we use fixed-size array of 26 elements for character counting.
"""

import sys

def main():
    input = sys.stdin.readline
    t = int(input())
    for _ in range(t):
        n, k = map(int, input().split())
        a = [0] * 26  # Array to store frequency of each character (a-z)
        for c in input().rstrip():  # Read the string and count frequencies
            a[ord(c) - 97] += 1
        cnt = 0
        for ai in a:  # Count how many characters have odd frequency
            cnt += ai % 2
        # If k is less than (cnt - 1), we cannot remove enough characters to make at most one odd frequency
        if k < cnt - 1:
            print("NO")
        else:
            print("YES")

main()


# https://github.com/VaHiX/codeForces/