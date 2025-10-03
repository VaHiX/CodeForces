// Contest 1910, Problem A: Username
// URL: https://codeforces.com/contest/1910/problem/A

fun main() = repeat(readln().toInt()) { println(readln().dropLastWhile { it == '0' }.dropLast(1)) }
