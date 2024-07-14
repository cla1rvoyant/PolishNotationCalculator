#include <iostream>
#include <string>
#include <math.h>
#include <sstream>

using namespace std;

string alpha = "0123456789";

float string_to_num(string num)
{
    float result;
    stringstream ss;

    ss << num;
    ss >> result;

    return result;
}

int char_to_num(char c)
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
    if (num == -0)
        num = 0;

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

    for (int exp_index = 0; exp_index < size(expression); exp_index++)
    {
        if (expression[exp_index] == '^')
        {
            int end_inter_exp_expression = exp_index + 1;
            string num, exponent;

            int num_end = exp_index;
            int num_begin = num_end;

            for (; expression[num_begin] != ' ' && num_begin > 0; num_begin--);
            if (num_begin > 0)
                num_begin++;
            int begin_inter_exp_expression = num_begin;
            for (; num_begin < num_end; num_begin++)
                num += expression[num_begin];

            for (; expression[end_inter_exp_expression] != ' '; end_inter_exp_expression++)
                exponent += expression[end_inter_exp_expression];
            
            float inter_exp_result = pow(string_to_num(num), string_to_num(exponent));

            int length_inter_exp_expression = end_inter_exp_expression - begin_inter_exp_expression;

            expression.replace(begin_inter_exp_expression, length_inter_exp_expression, num_to_string(inter_exp_result));
        }
    }

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
                                a += char_to_num(expression[num_index]) * pow(10, exp);
                                exp++;
                            }

                            if (expression[num_index] == '.')
                            {
                                float_flag = 1;
                                int float_exp = -1;
                                for (int float_index = num_index + 1; float_index < inter_index; float_index++)
                                {
                                    a += char_to_num(expression[float_index]) * pow(10, float_exp);
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
                                b += char_to_num(expression[num_index]) * pow(10, exp);
                                exp++;
                            }

                            if (expression[num_index] == '.')
                            {
                                float_flag = 1;
                                int float_exp = -1;
                                for (int i = num_index + 1; i < inter_index; i++)
                                {
                                    b += char_to_num(expression[i]) * pow(10, float_exp);
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
            expression[item_index] == '-') &&
            expression[item_index + 1] != ' ')
            item_index--;

        item_index--;
    }
    
    cout << expression << "\n";
}