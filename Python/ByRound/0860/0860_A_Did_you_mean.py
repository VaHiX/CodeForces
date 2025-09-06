# Contest 860, Problem A: Did you mean...
# URL: https://codeforces.com/contest/860/problem/A

word = input()
n = len(word)
breaks = [False] * n
vowels = set({'a', 'e', 'i', 'o', 'u'})
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
print(result)# 1690017674.986915