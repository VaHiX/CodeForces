# Contest 782, Problem A: Andryusha and Socks
# URL: https://codeforces.com/contest/782/problem/A

n = int(input())
s = list(map(int,input().split()))
s_t = set()
len_s_t = 0 
for i in range(2*n):
  if s[i] not in s_t:
    s_t.add(s[i])
  else:
    s_t.remove(s[i])
  if len(s_t) > len_s_t:
    len_s_t = len(s_t)
print(len_s_t)