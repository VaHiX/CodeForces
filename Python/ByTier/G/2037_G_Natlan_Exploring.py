# Contest 2037, Problem G: Natlan Exploring
# URL: https://codeforces.com/contest/2037/problem/G

n = int(input())
a = [int(t) for t in input().split()]

MAX_P = 1_000_000
primes = []
sieve = [0]*(MAX_P+1)
for i in range(2,MAX_P+1):
    if not sieve[i]: primes.append(i)
    for p in primes:
        if i*p > MAX_P: break
        sieve[i*p] = p
        if not i%p: break
def rad(k): #get all divisors of rad(k)
    r = []
    while k > 1:
        if 0 == sieve[k]: r.append(k); break
        p = sieve[k]
        r.append(p)
        while k%p == 0: k //= p

    divs = [1]
    for p in r:
        L = len(divs)
        for _ in range(L):
            divs.append( divs[-L]*(-p) )
    return divs


V = [0]*1_000_001 #sum of v[i] over i such that i%d == 0
for d in rad(a[0]):
    V[abs(d)] = 1

for i in range(1,n):
    divs = rad(a[i])
    ways = 0

    for d in divs:
        if d == 1: continue
        if d > 0: ways -= V[d]
        if d < 0: ways += V[-d]

    ways %= 0x3b800001
    if i == n-1: print(ways)
    for d in divs:
        V[abs(d)] += ways