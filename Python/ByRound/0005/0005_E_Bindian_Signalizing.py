# Contest 5, Problem E: Bindian Signalizing
# URL: https://codeforces.com/contest/5/problem/E


def calc(arr, begin, n):
    res = 0
    stack = [arr[begin]]
    cnt = [0]
    for i in range(begin - n, begin + 1):  # from mx to mx
        h = arr[i]
        while h > stack[-1]:
            stack.pop()
            res += cnt.pop()  # add previous lower hills
        if h != stack[0]:  # there is a previous higher hill
            res += 1
        if h == stack[-1]:
            res += cnt[-1]  # add previous same height hills
            cnt[-1] += 1
        else:
            stack.append(h)
            cnt.append(1)
    return res


n = int(input())
hs = [int(x) for x in input().split(" ")]
m1, m2, c1, c2 = 0, 0, 0, 0
for i, h in enumerate(hs):
    if h > m1:
        m2, c2 = m1, c1
        m1, c1 = h, 1
        mid = i
    elif h == m1:
        c1 += 1
    elif h > m2:
        m2, c2 = h, 1
    elif h == m2:
        c2 += 1
print(
    calc(hs, mid, n) - c1 - c2 * int(c1 == 1)
)  # some pair (mid, i) is calculated twice
