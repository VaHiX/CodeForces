# Contest 2050, Problem B: Transfusion
# URL: https://codeforces.com/contest/2050/problem/B

for s in [*open(0)][2::2]:
    lst = list(map(int, s.split()))
    len_, sum_ = len(lst), sum(lst)
    print(
        "YES"
        if sum_ % len_ == 0 and sum(lst[1::2]) == (len_ // 2) * (sum_ // len_)
        else "NO"
    )
