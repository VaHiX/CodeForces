# Contest 521, Problem A: DNA Alignment
# URL: https://codeforces.com/contest/521/problem/A

n = int(input())
s = input()
w = [0] * 4
w[0] = s.count("A")
w[1] = s.count("C")
w[2] = s.count("G")
w[3] = s.count("T")
print((w.count(max(w)) ** n) % 1000000007)
