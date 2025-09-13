# Contest 396, Problem A: On Number of Decompositions into Multipliers
# URL: https://codeforces.com/contest/396/problem/A

# Made By Mostafa_Khaled
bot = True
Mod = 1000000007

MAX = 33000

n = int(input())

A = list(map(int, input().split()))


B = [0] * MAX

bePrime = [0] * MAX

primNum = []

C = []


fac = [1]

for j in range(1, MAX):

    fac.append(fac[-1] * j % Mod)


def calc(M, N):

    return fac[M] * pow(fac[N] * fac[M - N] % Mod, Mod - 2, Mod) % Mod


for j in range(2, MAX):

    if bePrime[j] == 0:

        primNum.append(j)

        i = j

        while i < MAX:

            bePrime[i] = 1

            i = i + j


for x in A:

    tmp = x

    for j in primNum:

        while tmp % j == 0:

            tmp /= j

            B[j] += 1

    if tmp > 1:

        C.append(tmp)


ans = 1


for j in range(2, MAX):

    if B[j] > 0:

        ans = ans * calc(n + B[j] - 1, n - 1) % Mod


l = len(C)

for j in range(0, l):

    num = 0

    for k in range(0, l):

        if C[k] == C[j]:

            num = num + 1

            if k > j:

                num = 0

                break

    if num > 0:

        ans = ans * calc(n + num - 1, n - 1) % Mod


print(str(ans % Mod))


# Made By Mostafa_Khaled
