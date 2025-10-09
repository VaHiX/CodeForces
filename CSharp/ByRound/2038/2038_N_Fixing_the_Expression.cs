using System;

class Program
{
    static void Main()
    {
        int t = int.Parse(Console.ReadLine());
        string[] expressions = new string[t];

        for (int i = 0; i < t; i++)
        {
            expressions[i] = Console.ReadLine();
        }

        foreach (string expr in expressions)
        {
            Console.WriteLine(FixExpression(expr));
        }
    }

    static string FixExpression(string expr)
    {
        char a = expr[0];
        char op = expr[1];
        char b = expr[2];

        if (IsTrueExpression(a, op, b))
        {
            return expr;
        }

        // Try changing the operator
        if (a < b && op != '<') return $"{a}<{b}";
        if (a > b && op != '>') return $"{a}>{b}";
        if (a == b && op != '=') return $"{a}={b}";

        // Try changing the digits
        if (op == '<') return $"{Math.Min(a, b)}<{Math.Max(a, b)}";
        if (op == '>') return $"{Math.Max(a, b)}>{Math.Min(a, b)}";
        if (op == '=') return $"{a}={a}";

        return expr; // This line should never be reached
    }

    static bool IsTrueExpression(char a, char op, char b)
    {
        if (op == '<' && a < b) return true;
        if (op == '>' && a > b) return true;
        if (op == '=' && a == b) return true;
        return false;
    }
}
