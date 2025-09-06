# Contest 2037, Problem F: Ardent Flames
# URL: https://codeforces.com/contest/2037/problem/F

for i in range(int(input())):
    n, m ,k = map(int, input().split())
    h = list(map(int, input().split()))
    x = list(map(int, input().split()))
    l = 1
    r = 1000000001
    while l < r:
        attacks = (l+r)//2
        found = 0
        lefts = []
        rights = []
        for i in range(n):
            damage = (h[i]+attacks-1)//attacks
            if damage > m:
                continue
            lefts.append(x[i]-(m-damage))
            rights.append(x[i]+(m-damage)+1)
        lefts.sort()
        rights.sort()
        ptr1 = 0
        ptr2 = 0
        while ptr1 < len(lefts):
            if lefts[ptr1] > rights[ptr2]:
                ptr2 += 1
            elif lefts[ptr1] == rights[ptr2]:
                ptr1 += 1
                ptr2 += 1
            elif lefts[ptr1] < rights[ptr2]:
                ptr1 += 1
                if ptr1 - ptr2 >= k:
                    found = 1
        if found == 0:
            l = attacks+1
        else:
            r = attacks
    if l > 1000000000:
        print(-1)
    else:
        print(l)


