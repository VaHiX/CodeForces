# Contest 516, Problem A: Drazil and Factorial
# URL: https://codeforces.com/contest/516/problem/A

L = ["", "", "2", "3", "223", "5", "35", "7", "2227", "3327"]
input()
print("".join(sorted("".join([L[int(k)] for k in input()]))[::-1]))
