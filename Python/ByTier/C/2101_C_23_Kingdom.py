# Contest 2101, Problem C: 23 Kingdom
# URL: https://codeforces.com/contest/2101/problem/C


def find(x, book):
    if x == book[x]:
        return x
    book[x] = find(book[x], book)
    return book[x]


for _ in range(int(input())):
    n, a = int(input()), list(map(int, input().split()))
    a = [0] + a
    bookl, bookr = list(range(n + 1)), list(range(n + 1))
    ans, l, r = 0, 1, n
    while l < r:
        while l < r and find(a[l], bookl) == 0:
            l += 1
        while l < r and find(a[r], bookr) == 0:
            r -= 1
        if l < r:
            ans += r - l
            bookl[find(a[l], bookl)] = find(a[l], bookl) - 1
            bookr[find(a[r], bookr)] = find(a[r], bookr) - 1
            l += 1
            r -= 1
    print(ans)
