// Problem: CF 2087 G - Esports in Berland
// https://codeforces.com/contest/2087/problem/G

/*
 * Problem: G. Esports in Berland
 * Purpose: Find maximum income and number of optimal training plans for Monocarp.
 *
 * Algorithms:
 * - Dynamic Programming with precomputation of factorials
 * - Greedy optimization with counting combinations via modular arithmetic
 * - Modular exponentiation for inverse calculation
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

fun main() {
    var n = readInt()
    var a = readInts()
    var cnt = Array(200200, { it -> 0 }) // Count of days with specific "delta" value
    var sum = 0L
    for (i in 0..n - 1) {
        sum += a[i]
        if (n - i - 1 >= a[i]) {
            cnt[n - i - 1 - a[i]]++ // Increment count of delta values
        }
    }
    
    var pn = Array(200200, { it -> 1L })
    for (i in 0..n - 1) {
        pn[i + 1] = pn[i] * (i + 1) % 998244353 // Precompute factorials modulo 998244353
    }
    
    var s1 = sum
    var s2 = 1L
    var s3 = 0L
    var s4 = 0L
    for (i in n - 1 downTo 0) {
        for (j in 1..cnt[i]) {
            s3 = s3 + i // Accumulate delta values
            s4 = s4 + 1 // Count number of selected delta indices
            val now = sum + s3 - s4 * (s4 - 1) / 2 // Compute current income with arithmetic sum
            if (s1 < now) {
                s1 = now
                s2 = pn[cnt[i]] * mpow(pn[j].toInt()) % 998244353 * mpow(pn[cnt[i] - j].toInt()) % 998244353
            } else if (s1 == now) {
                s2 =
                    s2 +
                        pn[cnt[i]] * mpow(pn[j].toInt()) % 998244353 * mpow(pn[cnt[i] - j].toInt()) %
                            998244353
                if (s2 >= 998244353) {
                    s2 = s2 - 998244353
                }
            }
        }
    }
    print(s1)
    print(" ")
    println(s2)
}

fun readInt() = readLine()!!.toInt()
fun readInts() = readLine()!!.split(" ").map { it.toInt() }
fun readLong() = readLine()!!.toLong()
fun readLongs() = readLine()!!.split(" ").map { it.toLong() }
fun readString() = readLine()!!.toString()
fun readStrings() = readLine()!!.split(" ").map { it.toString() }

fun mpow(x: Int): Int {
    var ans = 1L
    var a = x.toLong()
    var b = 998244351
    while (b >= 1) {
        if (b % 2 == 1) {
            ans = ans * a
            ans = ans % 998244353
        }
        a = a * a
        a = a % 998244353
        b = b / 2
    }
    return ans.toInt()
}


// https://github.com/VaHiX/codeForces/