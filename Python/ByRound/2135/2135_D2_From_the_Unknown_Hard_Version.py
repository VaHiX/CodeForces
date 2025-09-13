# Contest 2135, Problem D2: From the Unknown (Hard Version)
# URL: https://codeforces.com/contest/2135/problem/D2

K = 125
L = 25000 - K * K
for _ in range(int(input())):
    print(f"? {L}" + f" {K}" * L)
    ans0 = int(input())
    if ans0 == 0:
        print(f"? {K*K}" + " 1" * (K * K))
        ans1 = int(input())
        if ans1 == K * K:
            print("! 1")
        else:
            for i in range(2, K):
                if (K * K + i - 1) // i == ans1:
                    print(f"! {i}")
    else:
        lft = K * ((L + ans0 - 1) // ans0)
        rgt = min(10**5, K * (L // (ans0 - 1)) + K)
        arr = []
        for i in range(rgt - lft, 0, -1):
            arr.append(lft)
            arr.append(i)
        print(f"? {2*(rgt-lft)} " + " ".join(list(map(str, arr))))
        ans1 = int(input())
        print(f"! {2*rgt-lft-ans1}")
