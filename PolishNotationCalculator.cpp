#include <iostream>
#include <string>
#include <math.h>
#include <sstream>

using namespace std;

string alpha = "0123456789";

int string_to_num(char c)
{
    for (int num = 0; num < 10; num++)
    {
        if (c == alpha[num])
            return num;
    }
    
    return 0;
}

float operation(float a, float b, char c)
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
    
    return 0;
}

string num_to_string(float num)
{
    string result;
    stringstream ss;

    ss << num;
    ss >> result;
    
    return result;
}

int main()
{
    string expression;
    int end_inter_expression = 0;
    cout << "Put your expression:\n";
    getline(cin, expression);
    expression += ' ';

    int space_counter = 0, item_index = size(expression), operations_amt = 0;
    float a = 0, b = 0;

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
                        bool float_flag = 0;
                        bool is_float = 0;

                        for (int num_index = inter_index - 1; expression[num_index] != ' '; num_index--)
                        {
                            for (int check_index = num_index; expression[check_index] != ' '; check_index--)
                            {
                                if (expression[check_index] == '.')
                                {
                                    is_float = 1;
                                    break;
                                }
                            }

                            if (is_float == 0 || float_flag == 1)
                            {
                                if (expression[num_index] == '-')
                                {
                                    a *= -1;
                                    break;
                                }
                                a += string_to_num(expression[num_index]) * pow(10, exp);
                                exp++;
                            }

                            if (expression[num_index] == '.')
                            {
                                float_flag = 1;
                                int float_exp = -1;
                                for (int float_index = num_index + 1; float_index < inter_index; float_index++)
                                {
                                    a += string_to_num(expression[float_index]) * pow(10, float_exp);
                                    float_exp--;
                                }
                            }
                        }
                    }
                    else if (space_counter == 2)
                    {
                        end_inter_expression = inter_index - item_index;

                        int exp = 0;
                        bool float_flag = 0;
                        bool is_float = 0;

                        for (int num_index = inter_index - 1; expression[num_index] != ' '; num_index--)
                        {
                            for (int check_index = num_index; expression[check_index] != ' '; check_index--)
                            {
                                if (expression[check_index] == '.')
                                {
                                    is_float = 1;
                                    break;
                                }
                            }

                            if (is_float == 0 || float_flag == 1)
                            {
                                if (expression[num_index] == '-')
                                {
                                    b *= -1;
                                    break;
                                }
                                b += string_to_num(expression[num_index]) * pow(10, exp);
                                exp++;
                            }

                            if (expression[num_index] == '.')
                            {
                                float_flag = 1;
                                int float_exp = -1;
                                for (int i = num_index + 1; i < inter_index; i++)
                                {
                                    b += string_to_num(expression[i]) * pow(10, float_exp);
                                    float_exp--;
                                }
                            }
                        }
                    }
                }
            }
            inter_result = num_to_string(operation(a, b, expression[item_index]));
            operations_amt--;

            if (operations_amt == 0)
                expression = inter_result;
            else
                expression.replace(item_index, end_inter_expression, inter_result);

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
    
    cout << expression << "\n";
}