# Contest 2116, Problem A: Gellyfish and Tricolor Pansy
# URL: https://codeforces.com/contest/2116/problem/A

for _ in range(int(input())):
    a, b, c, d = map(int, input().split())
    print(["Gellyfish", "Flower"][min(b, d) > min(a, c)])
