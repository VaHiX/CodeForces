# Contest 2009, Problem B: osu!mania
# URL: https://codeforces.com/contest/2009/problem/B

exec("n=int(input());print(*[a.index('#')+1for a in[input()for i in range(n)][::-1]]);"*int(input()))