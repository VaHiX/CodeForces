// Problem: CF 2132 B - The Secret Number
// https://codeforces.com/contest/2132/problem/B

/**
 * B. The Secret Number
 *
 * Problem Description:
 * Vadim thought of a number x. He appended a positive number of zeros to the right of it,
 * forming a new number y = x * 10^k for some k >= 1. Then, he spreads the sum n = x + y.
 * We are given n and must find all valid values of x such that n = x + x*10^k.
 *
 * Algorithm:
 * For each possible number of digits (from 1 to 17):
 *   - Assume k = digit count - 1, so y = x * 10^(k).
 *   - Form a candidate number 'b' = 10^(k) + 1 (e.g., for k=1 => b=11; for k=2 => b=101)
 *   - Check if n % b == 0
 *   - If so, compute x = n / b and add to result list
 *
 * Time Complexity: O(17 * t) where t is number of test cases.
 * Space Complexity: O(1) excluding output storage.
 */
import java.io.BufferedReader
import java.io.BufferedWriter
import java.io.InputStreamReader
import java.io.OutputStreamWriter
import java.util.*
fun BufferedReader.readInt(): Int = readLine().toInt()
fun BufferedReader.readLong(): Long = readLine().toLong()
fun BufferedReader.readIntArray0(): IntArray = readLine().split(" ").map { it.toInt() }.toIntArray()
fun BufferedReader.readIntArray1(): IntArray = ("1 " + readLine()).split(" ").map { it.toInt() }.toIntArray()
fun BufferedReader.readLongArray0(): LongArray = readLine().split(" ").map { it.toLong() }.toLongArray()
fun BufferedReader.readLongArray1(): LongArray = ("1 " + readLine()).split(" ").map { it.toLong() }.toLongArray()
fun BufferedReader.read2Int(): Pair<Int, Int> = readIntArray0().let { it[0] to it[1] }
fun BufferedReader.read2Long(): Pair<Long, Long> = readLongArray0().let { it[0] to it[1] }
fun BufferedReader.read3Int(): Triple<Int, Int, Int> = readIntArray0().let { Triple(it[0], it[1], it[2]) }
fun BufferedWriter.writeln(s: String) {
    write(s)
    newLine()
}
fun BufferedWriter.writeln() = writeln("")
fun BufferedWriter.writeln(a: Int) = writeln("$a")
fun BufferedWriter.writeln(a: Long) = writeln("$a")
fun BufferedWriter.writeln(a: IntArray) {
    a.forEach { write("$it ") }
    newLine()
}
fun BufferedWriter.writeln(a: List<Int>) {
    a.forEach { write("$it ") }
    newLine()
}
private operator fun Pair<Int, Int>.minus(x: Int): Pair<Int, Int> {
    return first - x to second - x
}
const val MOD = 1_000_000_000 + 7
fun gcd(a: Int, b: Int): Int = if (a == 0) b else gcd(b % a, a)
fun main(args: Array<String>) {
    val reader = BufferedReader(InputStreamReader(System.`in`))
    val writer = BufferedWriter(OutputStreamWriter(System.out))
    val t = reader.readLine().toInt()
    for (i in 0 until t) {
        solve(reader, writer)
    }
    reader.close()
    writer.close()
}
private fun solve(reader: BufferedReader, writer: BufferedWriter) {
    val n = reader.readLong()
    val ans = LinkedList<Long>()
    for (i in 1..17) {
        // Construct candidate b such that x + x * 10^(i-1) = n => x * (1 + 10^(i-1)) = n
        val b = ("1" + "0".repeat(i - 1) + "1").toLong()
        if (n % b == 0L) {
            ans.addFirst(n / b)
        }
    }
    writer.writeln(ans.size)
    if (ans.isNotEmpty()) {
        ans.forEach { writer.write("$it ") }
        writer.writeln()
    }
}


// https://github.com/VaHiX/CodeForces/