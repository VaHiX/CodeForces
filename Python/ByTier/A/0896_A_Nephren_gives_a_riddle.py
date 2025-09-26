# Contest 896, Problem A: Nephren gives a riddle
# URL: https://codeforces.com/contest/896/problem/A


def func(n, i):
    while True:
        if n == 0:
            if i < N1:
                return f0[i]
            else:
                return "."
        l = lenf[n - 1] if n <= len(lenf) else lenf[-1]
        if i < N2:
            return f10[i]
        elif i < N2 + l:
            # return func(n - 1, i - 34)
            n -= 1
            i -= N2
        elif i < N2 + l + N3:
            return f11[i - (N2 + l)]
        elif i < N2 + l + N3 + l:
            n -= 1
            i -= N2 + l + N3
            # return func(n - 1, i - (34 + l + 32))
        elif i < N2 + l + N3 + l + N4:
            return f12[i - (N2 + l + N3 + l)]
        else:
            return "."


if __name__ == "__main__":
    q = int(input())
    ans = ""
    f0 = "What are you doing at the end of the world? Are you busy? Will you save us?"
    f10 = 'What are you doing while sending "'
    f11 = '"? Are you busy? Will you send "'
    f12 = '"?'
    N1, N2, N3, N4 = len(f0), len(f10), len(f11), len(f12)

    lenf = [N1]
    while lenf[-1] < 1e18:
        lenf.append(N2 + N3 + N4 + 2 * lenf[-1])
    # print(len(lenf))

    for i in range(q):
        n, k = [int(i) for i in input().split(" ")]
        # print(n, k)
        res = func(n, k - 1)
        ans += res
    print(ans)
