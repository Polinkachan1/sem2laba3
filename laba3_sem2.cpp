#include <iostream>
#include <string>
using namespace std;

struct Stack
{
    int number;
    char oper;

    Stack* tail;
};

void display_menu() {
    cout << "Выберите действие:" << endl;
    cout << "1. Введите выражение." << endl;
    cout << "2. Реализует преобразование введенного выражения в прямую или в обратную польскую нотацию" << endl;
    cout << "3. Реализует проверку на корректность простого выражения и выражения, записанного в прямой и обратной польских нотациях" << endl;
    cout << "4. Реализует вычисления простого выражения и выражения, записанного в прямой польской нотациях. " << endl;
    cout << "5. Реализует вычисления простого выражения и выражения, записанного в обратной польских нотациях" << endl;
    cout << "6. ИДЗ" << endl;
    cout << "7. Выход!" << endl;
}
string change_unknown(string expression,int val, char elem) {
    string value = to_string(val);
    string res;
    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == elem) {
            res += value;
        }
        else {
            res += expression[i];
        }
    }
    return res;
}
string replace_unknown(string expression) {
    int value;
    for (int i = 0; i < expression.length(); i++) {
        char elem = expression[i];
        if (isalpha(elem)) {
            cout << "Введите значение для переменной '" << elem << "': ";
            cin >> value;
            expression = change_unknown(expression, value, elem);
        }
    }
    return expression;
}
void push(Stack*& top, int num) {
    Stack* new_elem = new Stack;
    new_elem->number = num;
    new_elem->tail = top;    
    top = new_elem;          
}
char pop(Stack*& top) {
    if (top == nullptr) {
        return '\0';
    }
    Stack* last_elem = top;
    char popped_num = top->number;
    top = top->tail;
    delete last_elem;
    return popped_num;
}
void push_op(Stack*& top, char oper) {
    Stack* new_elem = new Stack;
    new_elem->oper = oper;
    new_elem->tail = top;
    top = new_elem;
}
char pop_op(Stack*& top) {
    if (top == nullptr) {
        cout << "Ошибка: Стек пуст!" << endl;
        return '\0';
    }
    Stack* last_elem = top;
    char popped_op = top->oper;
    top = top->tail;
    delete last_elem;
    return popped_op;
}
int priority_of_operations(char elem) {
    switch (elem) {
    case '-':case '+': return 1;
    case '*':case '/': return 2;
    default: return 0;
    }
}
char top(Stack* top_elem) {
    return top_elem?top_elem->oper:'\n';
}
int for_calc(Stack*& stack,char elem, int right, int left) {
    int result = 0;
    switch (elem) {
    case '+':
        result = left + right;
        cout << right << "  +  " << left << " = " << result << endl;
        break;
    case '-':
        result = left - right;
        cout << left << "  -  " << right << " = " << result << endl;
        break;
    case '*':
        result = left * right;
        cout << left << "  *  " << right << " = " << result << endl;
        break;
    case '/':
        if (right == 0) {
            cout << "Ошибка: Деление на ноль!" << endl;
            return 0;
        }
        result = left / right;
        cout << left << "  /  " << right << " = " << result << endl;
        break;
    default:
        cout << "Ошибка: Неизвестный оператор!" << endl;
        return 0;
    }
    return result;
}
string make_reverse_polish_notation(string& expression) {
    Stack* stack = nullptr;
    string output = "";
    for (int i = 0; i<expression.length(); i++) {
        char elem = expression[i];
        if (elem == ' ') {
            continue;
        }

        if (isdigit(elem)) {
            while (isdigit(expression[i])) {
                output += expression[i++];
            }
            output += ' ';
            i--;
        }
        else if (elem == '(') {
            push_op(stack, elem);
        }
        else if (elem == ')') {
            while (stack != nullptr && stack->oper != '(') {
                output += pop_op(stack);
                output += ' ';
            }
            pop_op(stack);
        }
        else if (elem == '+' || elem == '-' || elem == '*' || elem == '/') {
            while (stack != nullptr && priority_of_operations(stack->oper) >= priority_of_operations(elem)) {
                output += pop_op(stack);
                output += ' ';
            }
            push_op(stack, elem);
        }
    }
    while (stack != nullptr) {
        output += pop_op(stack);
        output += ' ';
    }
    return output;
}
string make_direct_polish_notation(string expression) {
    Stack* stack = nullptr;
    string output = "";
    for (int i = expression.length()-1; i >= 0; i--) {
        char elem = expression[i];
        if (elem == ' ') {
            continue;
        }
        if (isdigit(elem)) {
            string value = "";
            while (i >= 0 && isdigit(expression[i])) {
                value += expression[i];
                i--;
            }
            output += value + ' ';
            i++;
        }
        else if (elem == ')') {
            push_op(stack, elem);
        }
        else if (elem == '(') {
            while (stack != nullptr && top(stack) != ')') {
                output += pop_op(stack);
                output += ' ';
            }
            pop_op(stack);
        }
        else if (elem == '+' || elem == '-' || elem == '*' || elem == '/') {
            while (stack != nullptr && priority_of_operations(top(stack)) >= priority_of_operations(elem)) {
                output += pop_op(stack);
                output += ' ';
            }
            push_op(stack, elem);
        }

    }
    while (stack != nullptr) {
        output += pop_op(stack);
        output += ' ';
    }
    reverse(output.begin(), output.end());
    return output;
}
void checking_simple_expression(string expression) {}
void checking_reverse_polish_notation(string expression) {}
void checking_direct_polish_notation(string expression) {}
void calculate_simple_expression(string expression) {}
int calculate_expression_in_reverse_polish_notation(string expression) {
    Stack* stack = nullptr;
    string value;
    for (int i = 0; i < expression.length(); i++) {
        char elem = expression[i];
        if (elem == ' ') {
            continue;
        }
        if (isdigit(elem)) {
            string value = "";
            while (isdigit(expression[i])) {
                value += expression[i];
                i++;
            }
            int res = stoi(value);
            push(stack, res);
            i--;
        }
        else if (elem == '+' || elem == '-' || elem == '*' || elem == '/') {
            int right = pop(stack);
            int left = pop(stack);
            int result = for_calc(stack, elem, right,left);
            push(stack, result);
        }
    }
    if (!value.empty()) {
        push(stack, stoi(value));
    }
    return pop(stack);
}
int calculate_expression_in_direct_polish_notation(string expression) {
    Stack* stack = nullptr;
    string value;
    for (int i = expression.length()-1; i  >=0; i--) {
        char elem = expression[i];
        if (elem == ' ') {
            continue;
        }
        if (isdigit(elem)) {
            string value = "";
            while (isdigit(expression[i])) {
                value += expression[i];
                i--;
            }
            reverse(value.begin(), value.end());
            int res = stoi(value);
            push(stack, res);
            i++;
        }
        else if (elem == '+' || elem == '-' || elem == '*' || elem == '/') {
            int right = pop(stack);
            int left = pop(stack);
            int result = for_calc(stack, elem, left, right);
            push(stack, result);
        }
    }
    return pop(stack);
}
void calculate_expression_in_simple_expression(string expression) {
}
void idz() {}
int main() {
    setlocale(0, "");
    int identificator, i,res;
    string expression,reverse_pol_not, direct_pol_not;
    while (true) {
        display_menu();
        cout << "ВВЕДИТЕ НОМЕР ЗАДАНИЯ: ";
        cin >> identificator;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("cls");
        switch (identificator) {
        case 1:
            system("cls");
            getline(cin, expression);
            expression = replace_unknown(expression);
            cout << expression << endl;
            break;
        case 2:
            cout << "Выберите действие:" << endl;
            cout << "1. Преобразовать выражение в обратную польскую нотацию." << endl;
            cout << "2. Преобразовать выражение в прямую польскую нотацию. " << endl;
            cin >> i;
            switch (i) {
            case 1:
                cout << "Ваше выражение в обратной польской нотации: ";
                reverse_pol_not =  make_reverse_polish_notation(expression);
                cout << reverse_pol_not<< endl;
                break;
            case 2:
                cout << "Ваше выражение в прямой польской нотации: ";
                direct_pol_not = make_direct_polish_notation(expression);
                cout << direct_pol_not<<endl;
                break;
            }
            break;
        case 3:
            checking_simple_expression(expression);
            checking_reverse_polish_notation(expression);
            checking_direct_polish_notation(expression);
            break;
        case 4:
            cout << "Полученная  обратная польская нотация:  " << reverse_pol_not << endl;
            res = calculate_expression_in_reverse_polish_notation(reverse_pol_not);
            cout << res << endl;
            break;
        case 5:
            cout << "Полученная прямая польская нотация:  " << direct_pol_not << endl;
            res = calculate_expression_in_direct_polish_notation(direct_pol_not);
            cout << res << endl;
            break;
        case 6:
            cout << "Выход!" << endl;
            return 0;

        default:
            cout << "Некорректный номер задания." << endl;
            break;
        }
        cout << "Задание выполнено. Нажмите Enter, чтобы продолжить." << endl;
        cin.ignore();
        cin.get();
    }
    return 0;
}