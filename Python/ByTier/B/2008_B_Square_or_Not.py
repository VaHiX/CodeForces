# Contest 2008, Problem B: Square or Not
# URL: https://codeforces.com/contest/2008/problem/B

for s in[*open(0)][2::2]:print('YNeos'[(s.find('0')-1)**2!=len(s)-1::2])