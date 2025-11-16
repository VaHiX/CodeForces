# Problem: CF 1822 E - Making Anti-Palindromes
# https://codeforces.com/contest/1822/problem/E

"""
Purpose: 
    This code determines the minimum number of operations (swaps) required to make a given string an anti-palindrome.
    An anti-palindrome is a string where no character at position i equals the character at the corresponding symmetric position (n-i+1).
    If it's impossible to make the string anti-palindromic, it returns -1.

Algorithms/Techniques:
    - Greedy approach with character frequency counting
    - Two-pass method:
        1. First check if transformation is possible (based on even length and max character frequency)
        2. Then calculate minimal swaps needed by comparing symmetric pairs

Time Complexity: O(n) where n is the length of the string. 
    - First loop to count characters: O(n)
    - Second loop to compare symmetric pairs: O(n)
    - Overall: O(n)

Space Complexity: O(1) 
    - A fixed-size array of 30 integers is used (for 26 lowercase letters + buffer).
"""

from sys import stdin, stdout

if __name__ == "__main__":
    for _ in range(int(stdin.readline())):
        n = int(stdin.readline())
        line = stdin.readline()

        ans, cnt = 0, [0] * 30  # cnt[0..25] for a..z, initialize all to 0
        for i in range(n):
            cnt[ord(line[i]) - 97] += 1  # count frequency of each character

        # If string length is odd or any character occurs more than n//2 times, 
        # then anti-palindrome is impossible
        if n & 1 or max(cnt) > n >> 1:
            ans = -1  # impossible case
        else:
            # Reset cnt to count characters at symmetric positions that are equal
            cnt = [0] * 30  # reset for second use
            for i in range(n >> 1):  # iterate only half the length
                if line[i] == line[n - i - 1]:  # if symmetric positions are same
                    ans += 1  # count how many pairs need to be fixed
                    cnt[ord(line[i]) - 97] += 1  # count how many times this char is involved
            # Final answer = max of:
            # 1. Max count of any character among symmetric pairs needing change
            # 2. Ceiling of (number of mismatches)/2 (as each swap fixes 2 mismatches)
            ans = max(max(cnt), (ans + 1) >> 1)
        stdout.write(str(ans) + "\n")


# https://github.com/VaHiX/CodeForces/