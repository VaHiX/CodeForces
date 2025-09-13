# Contest 2035, Problem C: Alya and Permutation
# URL: https://codeforces.com/contest/2035/problem/C

t = int(input())


def get_max(n):
    if n % 2 == 0:
        return 2 ** (len(bin(n)) - 2) - 1
    else:
        return n


def gen_perm(n):
    if n == 5:
        return [2, 1, 3, 4, 5]
    if n % 2 == 0:
        if n.bit_count() == 1:
            ans = gen_perm(n - 1)
            ans.append(n)
        else:
            last = (2 ** (len(bin(n)) - 3)) - 1
            ans = [i for i in range(1, n + 1) if i != last]
            ans.append(last)
    else:
        ans = gen_perm(n - 1)
        ans.append(n)
    return ans


for _ in range(t):
    n = int(input())
    print(get_max(n))
    print(" ".join(map(str, gen_perm(n))))
