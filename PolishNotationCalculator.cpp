#include <iostream>
#include <string>

using namespace std;

int char_to_int(char c)
{
    switch (c)
    {
    case '0':
        return 0;
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    }
}

int operation(int a, int b, char c)
{
    switch (c)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    }
}

string int_to_char(int num)
{
    string reverse_result, result;
    bool minus_flag = 0;

    if (num < 0)
    {
        minus_flag = 1;
        num *= -1;
    }

    if (num == 0)
        reverse_result += '0';

    while (num > 0)
    {
        if (num % 10 == 1)
            reverse_result += '1';
        else if (num % 10 == 2)
            reverse_result += '2';
        else if (num % 10 == 3)
            reverse_result += '3';
        else if (num % 10 == 4)
            reverse_result += '4';
        else if (num % 10 == 5)
            reverse_result += '5';
        else if (num % 10 == 6)
            reverse_result += '6';
        else if (num % 10 == 7)
            reverse_result += '7';
        else if (num % 10 == 8)
            reverse_result += '8';
        else if (num % 10 == 9)
            reverse_result += '9';
        num /= 10;
    }

    if (minus_flag == 1)
        reverse_result += '-';

    for (int i = size(reverse_result) - 1; i >= 0; i--)
        result += reverse_result[i];

    return result;
}

int main()
{
    string expression;
    cout << "Put your expression:\n";
    getline(cin, expression);
    expression += ' ';

    int space_counter = 0, a = 0, b = 0, item_index = size(expression), operations_amt = 0;

    for (int index = 0; index < size(expression); index++)
    {
        if ((expression[index] == '+' ||
            expression[index] == '-' ||
            expression[index] == '*' ||
            expression[index] == '/') &&
            expression[index + 1] == ' ')
            operations_amt++;
    }

    string inter_result;

    while (item_index >= 0)
    {
        if ((expression[item_index] == '+' ||
            expression[item_index] == '-' ||
            expression[item_index] == '*' ||
            expression[item_index] == '/') &&
            expression[item_index + 1] == ' ')
        {
            for (int inter_index = item_index + 2; space_counter < 2; inter_index++)
            {
                if (expression[inter_index] == ' ')
                {
                    space_counter++;
                    if (space_counter == 1)
                    {
                        int exp = 0;
                        for (int num_index = inter_index - 1; expression[num_index] != ' '; num_index--)
                        {
                            if (expression[num_index] == '-')
                            {
                                a *= -1;
                                break;
                            }
                            a += char_to_int(expression[num_index]) * pow(10, exp);
                            exp++;
                        }
                    }
                    else if (space_counter == 2)
                    {
                        int exp = 0;
                        for (int num_index = inter_index - 1; expression[num_index] != ' '; num_index--)
                        {
                            if (expression[num_index] == '-')
                            {
                                b *= -1;
                                break;
                            }
                            b += char_to_int(expression[num_index]) * pow(10, exp);
                            exp++;
                        }
                    }
                }
            }
            inter_result = int_to_char(operation(a, b, expression[item_index]));
            operations_amt--;

            if (operations_amt == 0)
                expression = inter_result;
            else
                expression.replace(item_index, 5, inter_result);

            space_counter = 0;
            a = 0;
            b = 0;
        }

        else if ((expression[item_index] == '+' ||
            expression[item_index] == '-' ||
            expression[item_index] == '*' ||
            expression[item_index] == '/') &&
            expression[item_index + 1] != ' ')
            item_index--;

        item_index--;
    }
    cout << expression;
}