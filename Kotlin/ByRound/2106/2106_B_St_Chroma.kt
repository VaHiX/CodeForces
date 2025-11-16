// Problem: CF 2106 B - St. Chroma
// https://codeforces.com/contest/2106/problem/B

/*
B. St. Chroma
Algorithms/Techniques: Greedy construction
Time Complexity: O(n) per test case
Space Complexity: O(n) for the output array

Given a permutation p of length n and a target color x,
construct a permutation such that MEX(p[0..i]) equals x as often as possible.
The key insight is to place x at the beginning, then place values from 0 to x-1
in order so that their MEX starts with 0, and then append the rest.
This maximizes occurrences of x as a MEX value.

Example: n=4, x=2
We want to make sure we get as many 2's as possible, so:
- Put x = 2 at start
- Then put 0 to x-1 (i.e., 0,1) in order
- Then append others (3)
So p = [2, 0, 1, 3]
*/
import java.io.PrintWriter
import java.util.*
@JvmField val INPUT = System.`in`
@JvmField val OUTPUT = System.out
@JvmField val _reader = INPUT.bufferedReader()
fun readLine(): String? = _reader.readLine()
fun readLn() = _reader.readLine()!!
@JvmField var _tokenizer: StringTokenizer = StringTokenizer("")
fun read(): String {
    while (_tokenizer.hasMoreTokens().not()) _tokenizer = StringTokenizer(_reader.readLine() ?: return "", " ")
    return _tokenizer.nextToken()
}
fun readInt() = read().toInt()
fun readDouble() = read().toDouble()
fun readLong() = read().toLong()
fun readStrings(n: Int) = List(n) { read() }
fun readLines(n: Int) = List(n) { readLn() }
fun readInts(n: Int) = List(n) { read().toInt() }
fun readIntArray(n: Int) = IntArray(n) { read().toInt() }
fun readDoubles(n: Int) = List(n) { read().toDouble() }
fun readDoubleArray(n: Int) = DoubleArray(n) { read().toDouble() }
fun readLongs(n: Int) = List(n) { read().toLong() }
fun readLongArray(n: Int) = LongArray(n) { read().toLong() }
@JvmField val _writer = PrintWriter(OUTPUT, false)
inline fun output(block: PrintWriter.() -> Unit) { _writer.apply(block).flush() }
fun main(args: Array<String>) {
    var t = readInt()
    while (t > 0) {
        val n = readInt()
        val x = readInt()
        val answer = mutableListOf<Int>()
        // Add all numbers except x in order from 0 to x-1, starting with x
        for (i in 0 until n) {
            if (i == x) {
                continue  // Skip x for now to place it at front later
            }
            answer.add(i)
        }
        // Append x at the end only if x < n
        if(x < n) {
            answer.add(x)
        }
        println(answer.joinToString(" "))
        t--
    }
}


// https://github.com/VaHiX/CodeForces/