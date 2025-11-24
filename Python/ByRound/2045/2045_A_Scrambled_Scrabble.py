# Problem: CF 2045 A - Scrambled Scrabble
# https://codeforces.com/contest/2045/problem/A

"""
A. Scrambled Scrabble

Purpose:
This code solves the problem of finding the maximum number of syllables that can be formed from a given string S,
where each syllable follows the pattern consonant-vowel-consonant (CVC). 

The algorithm:
1. Count occurrences of specific letters:
   - N, G: These form a special consonant "NG".
   - Y: Can be treated as either vowel or consonant.
   - Vowels (A, E, I, O, U): Treated as vowels.
   - Other letters: Treated as consonants.
2. Process Y's greedily by assigning them to maximize syllable count.
3. Use a greedy approach to compute the maximum number of valid syllables:
   - Each syllable requires one vowel and two consonants (or at most one NG).
4. The final output is the total length of valid syllables.

Time Complexity: O(n), where n is the length of the string S.
Space Complexity: O(1), constant space used for counters and variables.
"""

def solve():
    s = input()
    n, g, y, f = 0, 0, 0, [0, 0]  # n: count of 'N', g: count of 'G', y: count of 'Y', f[0]: consonants, f[1]: vowels
    for i in s:
        if i == "N":
            n += 1
        if i == "G":
            g += 1
        if i == "Y":
            y += 1
        elif i in ["A", "E", "I", "O", "U"]:
            f[1] += 1
        else:
            f[0] += 1
    for _ in range(y):  # Greedily assign Ys to maximize syllables
        if f[0] >= 2 * f[1] + 2:  # If we can add it as a vowel without over-consuming consonants
            f[1] += 1
        else:
            f[0] += 1  # Otherwise, treat Y as consonant
    
    t = min(f[0] // 2, f[1])  # Number of complete syllables we can make
    out = t * 3 + max(0, min(n, g, f[0] - t * 2, t * 2))  # Final length calculation:
    # t * 3: contributes 3 letters per syllable
    # max(0, ...): extra consonants not consumed in syllables but could form new ones with N and G
    print(out)

solve()


# https://github.com/VaHiX/codeForces/