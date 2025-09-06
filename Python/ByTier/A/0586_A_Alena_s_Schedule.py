# Contest 586, Problem A: Alena's Schedule
# URL: https://codeforces.com/contest/586/problem/A

n = int(input())
word = input().replace(" ", "").strip("0")
word = word.replace("0"*5, "00")
while "000" in word:
    word = word.replace("000", "00")
word = word.replace("00", "")
print(len(word))