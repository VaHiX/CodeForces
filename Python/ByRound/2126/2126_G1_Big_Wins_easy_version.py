# Contest 2126, Problem G1: Big Wins! (easy version)
# URL: https://codeforces.com/contest/2126/problem/G1



def solve():
    n = int(input())
    a = [int(i) for i in input().split()]
    if n == 1 :
        print(0)
        return
    mn = min(a)
    ans = 0
    s = sorted(set(a), reverse=True)
    for v in s:
        if v <= mn or v - mn <= ans:
            break
        pref = [0] * (n + 1)
        for i in range(n):
            pref[i+1] = pref[i] + (1 if a[i] >= v else -1)
        pref_min = [0] * (n + 1)
        pref_min[0] = pref[0]
        for i in range(1, n + 1):
            pref_min[i] = pref_min[i-1] if pref_min[i-1] < pref[i] else pref[i]
        suff_max = [0] * (n + 1)
        suff_max[n] = pref[n]
        for i in range(n - 1, -1, -1):
            suff_max[i] = pref[i] if pref[i] > suff_max[i + 1] else suff_max[i + 1]

        m_min = float('inf')
        for k in range(1, n + 1):
            if suff_max[k] >= pref_min[k-1]:
                m_min = min(a[k-1], m_min)
            
        ans = max(ans, v - m_min)
    
    print(ans)
        

    
if __name__ == "__main__":
    t = int(input())
    for _ in range(t):
        solve()