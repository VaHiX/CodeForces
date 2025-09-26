# Contest 2085, Problem B: Serval and Final MEX
# URL: https://codeforces.com/contest/2085/problem/B

for tt in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    c1 = 0 in a[:2]
    c2 = 0 in a[2:]
    print(1 + c1 + c2)
    print(c2 * f"3 {n} \n" + c1 * f"1 2 \n" + f"1 {(n-c1)-c2*(n-3)}")
