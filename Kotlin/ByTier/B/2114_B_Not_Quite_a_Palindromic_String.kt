// Problem: CF 2114 B - Not Quite a Palindromic String
// https://codeforces.com/contest/2114/problem/B

/*
 * Problem: B. Not Quite a Palindromic String
 *
 * Purpose:
 *   Given a binary string of even length n, determine whether we can rearrange the characters
 *   such that exactly k pairs (i, n-i+1) have s[i] == s[n-i+1].
 *
 * Algorithm:
 *   1. Count occurrences of '0' and '1'.
 *   2. Try to form exactly k good pairs by consuming 2 characters at a time:
 *      - Prefer using two '0's if possible.
 *      - Else use two '1's.
 *   3. After forming k pairs, check if the remaining count of '0's and '1's are equal.
 *
 * Time Complexity: O(n) per test case due to reading the string and processing counts.
 * Space Complexity: O(1) as only a fixed-size map is used for counting characters.
 */

import java.io.PrintWriter
import java.util.*
import kotlin.collections.ArrayDeque
import kotlin.math.abs
import kotlin.math.ceil
import kotlin.math.min
import kotlin.math.sqrt
const val MOD = 1_000_000_007
val infinityLong = 1_000_000_000_000_0L
private val isLocalEnvironment = java.io.File("input.txt").exists()
@JvmField
val INPUT = if (isLocalEnvironment)
    java.io.FileInputStream("input.txt")
else
    System.`in`
@JvmField
val OUTPUT = if (isLocalEnvironment)
    java.io.FileOutputStream("output.txt")
else
    System.`out`
fun PrintWriter.ans() {
    val (n,k) = readInts(2)
    val s = read().toList()
    val count = s.groupingBy { it }.eachCount().toMutableMap()
    var c = 0L // Count of good pairs formed so far
    while(c < k){
        val cz = count['0'] ?: 0
        val co = count['1'] ?: 0
        if(cz >= 2 && cz >= co){
            // Prefer consuming two '0's to satisfy more potential palindromic segments
            c++
            count['0'] =  count['0']!! - 2
        }else if(co >= 2){
            // If no enough '0's, consume two '1's
            c++
            count['1'] =  count['1']!! - 2
        }else{
            // Cannot form one more pair: not enough characters
            println("NO")
            return
        }
    }
    val cz = count['0'] ?: 0
    val co = count['1'] ?: 0
    if(cz == co){
        // Remaining characters can be arranged to make all pairs equal (symmetric)
        println("YES")
        return
    }
    println("NO")
}
fun PrintWriter.solve() {
    val t = readInt()
    repeat(t) {
        ans()
    }
}
fun main() {
    writer.solve()
    writer.flush()
}
@JvmField
val reader = INPUT.bufferedReader()
fun readLine(): String? = reader.readLine()
fun readLn() = reader.readLine()!! 
@JvmField
var tokenizer: StringTokenizer = StringTokenizer("")
fun read(): String {
    while (tokenizer.hasMoreTokens().not()) tokenizer = StringTokenizer(reader.readLine() ?: return "", " ")
    return tokenizer.nextToken()
}
fun readInt() = read().toInt()
fun readInts(n: Int) = readIntArray(n)
fun readLongs(n: Int) = readLongArray(n)
fun readDouble() = read().toDouble()
fun readLong() = read().toLong()
fun readStrings(n: Int) = Array(n) { read() }
fun readLines(n: Int) = Array(n) { readLn() }
fun readIntArray(n: Int) = IntArray(n) { read().toInt() }
fun readDoubleArray(n: Int) = DoubleArray(n) { read().toDouble() }
fun readLongArray(n: Int) = LongArray(n) { read().toLong() }
@JvmField
val writer = PrintWriter(OUTPUT, false)
fun IntArray.printArray() {
    writer.println(this.joinToString(" "))
}
fun LongArray.printArray() {
    writer.println(this.joinToString(" "))
}
fun CharArray.printArray() = println(this.joinToString(" "))
fun <T> Array<out T>.printArray() {
    writer.println(this.joinToString(" "))
}
fun <T> dbg(value: T, name: String = "test") {
    if (isLocalEnvironment) {
        val formatted = when (value) {
            is List<*> -> value.joinToString(prefix = "[", postfix = "]")
            is Map<*, *> -> value.entries.joinToString(prefix = "{", postfix = "}") { "${it.key}=${it.value}" }
            is Array<*> -> value.joinToString(prefix = "[", postfix = "]")
            is IntArray -> value.joinToString(prefix = "[", postfix = "]")
            is BooleanArray -> value.joinToString(prefix = "[", postfix = "]")
            is DoubleArray -> value.joinToString(prefix = "[", postfix = "]")
            else -> value.toString()
        }
        writer.println("$name=$formatted")
    }
}


// https://github.com/VaHiX/CodeForces/