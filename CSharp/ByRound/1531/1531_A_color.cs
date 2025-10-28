// Problem: CF 1531 A - Зингер | color
// https://codeforces.com/contest/1531/problem/A

﻿/*
 * Код обрабатывает последовательность сообщений для управления цветом подсветки в куполе Дома Зингера.
 * Алгоритмы/Techniques: Симуляция состояния с использованием флага блокировки и переменной последнего цвета.
 * 
 * Временная сложность: O(n), где n — количество сообщений.
 * Пространственная сложность: O(1), так как используются только постоянные переменные.
 */

using System;
namespace ConsoleApp1 {
class Program {
  static void Main(string[] args) {
    bool isLocked = false; // Флаг, indicating если изменение цвета заблокировано
    string lastColor = "blue"; // Последний установленный цвет (начинается с "blue")
    int n = int.Parse(Console.ReadLine()); // Количество сообщений
    
    for (; n > 0; n--) {
      string input = Console.ReadLine(); // Чтение следующего сообщения
      
      if (input == "lock")
        isLocked = true; // Блокировка изменения цвета
      else if (input == "unlock")
        isLocked = false; // Разблокировка изменения цвета
      else if (!isLocked)
        lastColor = input; // Установка нового цвета, если не заблокировано
    }
    
    Console.WriteLine(lastColor); // Вывод конечного цвета
  }
}
}


// https://github.com/VaHiX/codeForces/