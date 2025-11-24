# Problem: CF 860 A - Did you mean...
# https://codeforces.com/contest/860/problem/A

"""
Beroffice text editor typo correction algorithm.

Algorithm:
1. Identify blocks of consecutive consonants.
2. Check if a block has at least 3 consonants and at least 2 different letters.
3. If such a block is found, insert a space before the last character of the block.
4. Reconstruct the string with minimum number of spaces to break all problematic blocks.

Time Complexity: O(n) where n is the length of the input word.
Space Complexity: O(n) for storing the breaks array and result string.

Techniques:
- Single pass through the string
- Tracking streak of consonants and number of different letters in streak
- Greedy approach to minimize number of spaces inserted
"""

word = input()
n = len(word)
breaks = [False] * n
vowels = set({"a", "e", "i", "o", "u"})
streak = 1 if word[0] not in vowels else 0
numdiff = streak
for i in range(1, n):
    if word[i] not in vowels:
        streak += 1
        if word[i] != word[i - 1]:
            numdiff += 1
    else:
        streak = 0
        numdiff = 0
    if streak >= 3 and numdiff >= 2:
        breaks[i] = True
        streak = 1
        numdiff = 1
result = ""
for i in range(n):
    if breaks[i]:
        result += " "
    result += word[i]
print(result)


# https://github.com/VaHiX/CodeForces/