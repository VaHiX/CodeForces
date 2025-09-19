// Contest 1910, Problem C: Poisonous Swamp
// URL: https://codeforces.com/contest/1910/problem/C

fun main() {
  repeat(readInt()) {
    readInt()
    val s = readln() + '.' + readln()
    println(s.split(".").sumOf { maxOf(0, it.length - 1) })
  }
}

private fun readInt() = readln().toInt()
