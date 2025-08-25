# Contest 2120, Problem E: Lanes of Cars
# URL: https://codeforces.com/contest/2120/problem/E

import sys


def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    out_lines = []
    for _ in range(t):
        n = int(data[index])
        index += 1
        k = int(data[index])
        index += 1
        a = list(map(int, data[index : index + n]))
        index += n
        T = sum(a)

        low = -(10**7)
        high = 10**10

        while low < high:
            mid = (low + high) // 2
            total_count = 0
            for a_i in a:
                if mid > a_i:
                    total_count += mid
                else:
                    if mid + k < 0:
                        total_count += 0
                    else:
                        total_count += min(mid + k, a_i)
            if total_count >= T:
                high = mid
            else:
                low = mid + 1

        x_min = low
        x0 = x_min - 1

        F0 = 0
        S0 = 0
        for a_i in a:
            if x0 > a_i:
                F0_i = x0
                S0_i = (x0 * (x0 + 1)) // 2 - k * a_i
            else:
                if x0 + k < 0:
                    F0_i = 0
                    S0_i = 0
                else:
                    if x0 <= a_i - k:
                        num = x0 + k
                        S0_i = num * (num + 1) // 2 - k * num
                        F0_i = num
                    elif x0 <= a_i:
                        S0_i = (a_i * (a_i + 1)) // 2 - k * a_i
                        F0_i = a_i
                    else:
                        F0_i = 0
                        S0_i = 0
            F0 += F0_i
            S0 += S0_i

        sum_marginal = S0 + (T - F0) * x_min
        total_angriness = sum_marginal + k * T
        out_lines.append(str(total_angriness))

    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    main()
