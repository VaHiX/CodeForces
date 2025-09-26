# Contest 2019, Problem A: Max Plus Size
# URL: https://codeforces.com/contest/2019/problem/A

for s in [*open(0)][2::2]:a=s.split();print(max(i//2+(len(a)-i+1)//2+int(x)for
i,x in enumerate(a)))