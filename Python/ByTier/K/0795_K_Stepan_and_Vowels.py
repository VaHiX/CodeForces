# Contest 795, Problem K: Stepan and Vowels
# URL: https://codeforces.com/contest/795/problem/K

n = int(input())
s = input().strip()

vowels = {"a", "e", "i", "o", "u", "y"}

result = []
current_vowel = None
current_count = 0

for c in s:
    if c in vowels:
        if c == current_vowel:
            current_count += 1
        else:
            if current_vowel is not None:
                if current_vowel in {"e", "o"}:
                    if current_count == 2:
                        result.append(current_vowel * 2)
                    else:
                        result.append(current_vowel)
                else:
                    result.append(current_vowel)
            current_vowel = c
            current_count = 1
    else:
        if current_vowel is not None:
            if current_vowel in {"e", "o"}:
                if current_count == 2:
                    result.append(current_vowel * 2)
                else:
                    result.append(current_vowel)
            else:
                result.append(current_vowel)
            current_vowel = None
            current_count = 0
        result.append(c)

if current_vowel is not None:
    if current_vowel in {"e", "o"}:
        if current_count == 2:
            result.append(current_vowel * 2)
        else:
            result.append(current_vowel)
    else:
        result.append(current_vowel)

print("".join(result))
