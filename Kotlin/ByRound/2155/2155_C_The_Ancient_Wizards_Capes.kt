// Problem: CF 2155 C - The Ancient Wizards' Capes
// https://codeforces.com/contest/2155/problem/C

/*
 * C. The Ancient Wizards' Capes
 *
 * Problem Description:
 * There are n wizards in a row, each wearing an invisibility cape that can be worn on either
 * their left or right side. Harry walks from wizard 1 to wizard n and counts how many wizards
 * he sees from each position based on visibility rules:
 * - Wizard j is visible from position i if:
 *   - Wizard j wears cape on left and i >= j, OR
 *   - Wizard j wears cape on right and i <= j.
 * Given Harry's list 'a' of counts, return the number of valid cape arrangements modulo 676767677.
 *
 * Algorithm:
 * For each test case:
 * - If n == 1, answer is always 2 (either left or right).
 * - Otherwise, for each consecutive pair (i, i+1), we compute s[i] = a[i+1] - a[i] + 1
 *   which represents the effective "difference" in visibility.
 * - Then use dynamic programming to try all combinations of capes for positions 1...n:
 *   Each position has either a left (0) or right (1) cape; check consistency against s array.
 *   Count valid configurations modulo M.
 *
 * Time Complexity: O(n^2) in worst case due to nested loops
 * Space Complexity: O(n)
 */
import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter
fun main() = with(BufferedReader(InputStreamReader(System.`in`))) {
    val writer = PrintWriter(System.out, false)
    val M = 676767677L
    readLine()!!.toInt().also { t ->
        var testIdx = t
        while (testIdx-- > 0) {
            readLine()!!.toInt().also { n ->
                readLine()!!.split(" ").map { it.toInt() }.toIntArray().also { a ->
                    when {
                        n == 1 -> {
                            writer.println(2L.rem(M)) // Only two options: left or right for single wizard
                        }
                        else -> {
                            IntArray(n.dec()).also { s ->
                                var ok = true
                                var i = 0
                                while (i < n.dec() && ok) {
                                    s[i] = a[i.inc()].minus(a[i]).inc() // Compute effective visibility difference
                                    when {
                                        s[i] < 0 || s[i] > 2 -> { // Check bounds
                                            ok = false
                                        }
                                    }
                                    i++
                                }
                                when {
                                    !ok -> writer.println(0) // Invalid difference => no solution
                                    else -> {
                                        var w = 0
                                        var st = 0
                                        while (st <= 1) { // Try both cape assignments for first wizard
                                            IntArray(n).apply {
                                                this[0] = st // Assign first wizard's cape type
                                            }.also { x ->
                                                var v = true
                                                var j = 0
                                                while (j < n.dec() && v) {
                                                    x[j.inc()] = s[j].minus(x[j]) // Compute next wizard's cape based on difference
                                                    when {
                                                        x[j.inc()] != 0 && x[j.inc()] != 1 -> { // Invalid cape type
                                                            v = false
                                                        }
                                                    }
                                                    j++
                                                }
                                                when {
                                                    !v -> Unit // Skip invalid assignment
                                                    else -> {
                                                        var S = 0
                                                        var k = 0
                                                        while (k < n) {
                                                            S = S.plus(x[k]) // Compute total count of right-facing capes
                                                            k++
                                                        }
                                                        when {
                                                            S == n.plus(x[0]).minus(a[0]) -> w++ // Check consistency with first element
                                                        }
                                                    }
                                                }
                                            }
                                            st++
                                        }
                                        writer.println(w.toLong().rem(M)) // Output number of valid assignments
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    writer.flush()
    writer.close()
}


// https://github.com/VaHiX/CodeForces/