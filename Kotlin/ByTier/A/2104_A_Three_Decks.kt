// Problem: CF 2104 A - Three Decks
// https://codeforces.com/contest/2104/problem/A

/*
 * Problem: A. Three Decks
 * Purpose: Determine if it's possible to distribute cards from the third deck between the first two decks
 *          such that all three decks end up with equal numbers of cards.
 *
 * Algorithm:
 * - Let total = a + b + c
 * - If total is not divisible by 3, return "NO"
 * - Otherwise, target = total / 3
 * - We need to check if we can move some cards from deck `c` to decks `a` and `b`, such that:
 *   - After redistribution: a + x = target, b + y = target, where x + y = cards taken from c
 *   - This implies: x = target - a, y = target - b
 *   - Since x + y = c, we get: (target - a) + (target - b) = c => 2 * target = a + b + c
 *   - Which is always true since total = a + b + c and target = total / 3
 *   - But also, both x and y must be non-negative.
 *   - So: target - a >= 0 => target >= a
 *         target - b >= 0 => target >= b
 *         Also, x <= c and y <= c because we can't take more cards than available in deck `c`
 *
 * Time Complexity: O(t), where t is number of test cases. Each operation takes constant time.
 * Space Complexity: O(1) - only using constant extra space.
 */
import java.io.PrintWriter
import java.util.*
fun PrintWriter.solve() {
    val t = readInt()
    for (i in 0 until t) {
        val a = readInt()
        val b = readInt()
        val c = readInt()
        // Total number of cards
        val total = a + b + c
        // If total is not divisible by 3, it's impossible to make all decks equal
        if (total % 3 != 0) println("NO")
        else {
            val target = total / 3
            // Check if current decks are such that we can distribute cards evenly
            // We must have a <= target and b <= target (since we want to increase them)
            // Additionally, the required number of cards from deck `c` should be valid
            // i.e., x = target - a >= 0, y = target - b >= 0, and x + y <= c
            if (b <= target) println("YES")
            else println("NO")
        }
    }
}
fun main() {
    _writer.solve(); _writer.flush()
}
@JvmField
val INPUT = System.`in`
@JvmField
val OUTPUT = System.out
@JvmField
val _reader = INPUT.bufferedReader()
fun readLine(): String? = _reader.readLine()
fun readLn() = _reader.readLine()!!
@JvmField
var _tokenizer: StringTokenizer = StringTokenizer("")
fun read(): String {
    while (_tokenizer.hasMoreTokens().not()) _tokenizer = StringTokenizer(
        _reader.readLine() ?: return "", " ")
    return _tokenizer.nextToken()
}
fun readInt() = read().toInt()
fun readDouble() = read().toDouble()
fun readLong() = read().toLong()
fun readStrings(n: Int) = Array(n) { read() }
fun readLines(n: Int) = Array(n) { readLn() }
fun readIntArray(n: Int) = IntArray(n) { read().toInt() }
fun readDoubleArray(n: Int) = DoubleArray(n) { read().toDouble() }
fun readLongArray(n: Int) = LongArray(n) { read().toLong() }
@JvmField
val _writer = PrintWriter(OUTPUT, false)
fun bigMod(B: Long, P: Long, M: Long): Long {
    var (r, p, b) = listOf(1, P, B)
    while (p > 0) {
        if (p % 2L == 1L) r = (r * b) % M
        p /= 2
        b = (b * b) % M
    }
    return r
}


// https://github.com/VaHiX/CodeForces/