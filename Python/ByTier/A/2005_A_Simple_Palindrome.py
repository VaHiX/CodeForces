# Contest 2005, Problem A: Simple Palindrome
# URL: https://codeforces.com/contest/2005/problem/A

for _ in range(int(input())):
    n = int(input())
    print("a" * (n // 5) + "e" * ((n+1) // 5) + "i" * ((n+2) // 5) + "o" * ((n+3) // 5) + "u" * ((n+4) // 5))
