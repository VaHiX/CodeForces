# Contest 738, Problem A: Interview with Oleg
# URL: https://codeforces.com/contest/738/problem/A

n = int(input())
s = input()
interview_text = ""
i = 0

while i < n:
    if s[i:i+3] == 'ogo':
        interview_text += "***"
        i += 2
        while i + 1 < n and s[i + 1:i + 3] == 'go':
            i += 2
    else:
        interview_text += s[i]
    i += 1

print(interview_text)
