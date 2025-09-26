# Contest 2010, Problem C1: Message Transmission Error (easy version)
# URL: https://codeforces.com/contest/2010/problem/C1

s=input()
for i in range(len(s)//2+1,len(s)):
    if s[len(s)-i:]==s[:i]:
        print("YES")
        print(s[:i])
        break
else:
    print("NO")