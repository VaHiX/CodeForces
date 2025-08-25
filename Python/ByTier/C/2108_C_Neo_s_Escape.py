# Contest 2108, Problem C: Neo's Escape
# URL: https://codeforces.com/contest/2108/problem/C

for _ in range(int(input())):
    n = int(input())
    l = list(map(int, input().split()))
    nl = [0]
    answer = 0

    for i in range(n):
        if l[i] != nl[-1]:
            nl.append(l[i])

    nl.append(0)
    # print(nl)

    for i in range(len(nl)):
        if nl[i] > nl[i - 1] and nl[i] > nl[i + 1]:
            answer += 1

    print(answer)
