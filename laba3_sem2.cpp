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
    cout << "4. Реализует вычисления простого выражения." << endl;
    cout << "5. Реализует вычисления выражения, записанного в обратной польской нотации" << endl;
    cout << "6. Реализует вычисления выражения, записанного в прямой польской нотации" << endl;
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
int pop(Stack*& top) {
    if (top == nullptr) {
        return '\0';
    }
    Stack* last_elem = top;
    int popped_num = top->number;
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
int for_calc(char elem, int right, int left) {
    int result = 0;
    switch (elem) {
    case '+':
        result = left + right;
        cout << left << "  +  " << right << " = " << result << endl;
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
            cout << "Строка сейчас: " << output << endl;
            i--;
        }
        else if (elem == '(') {
            push_op(stack, elem);
        }
        else if (elem == ')') {
            while (stack != nullptr && stack->oper != '(') {
                output += pop_op(stack);
                output += ' ';
                cout << "Строка сейчас: " << output << endl;
            }
            pop_op(stack);
        }
        else if (elem == '+' || elem == '-' || elem == '*' || elem == '/') {
            while (stack != nullptr && priority_of_operations(stack->oper) >= priority_of_operations(elem)) {
                output += pop_op(stack);
                output += ' ';
                cout << "Строка сейчас: " << output << endl;
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
            cout <<"Строка сейчас: "<< output << endl;
            i++;
        }
        else if (elem == ')') {
            push_op(stack, elem);
        }
        else if (elem == '(') {
            while (stack != nullptr && stack->oper != ')') {
                output += pop_op(stack);
                output += ' ';
                cout << "Строка сейчас: " << output << endl;
            }
            pop_op(stack);
        }
        else if (elem == '+' || elem == '-' || elem == '*' || elem == '/') {
            while (stack != nullptr && priority_of_operations(stack->oper) > priority_of_operations(elem)) {
                output += pop_op(stack);
                output += ' ';
                cout << "Строка сейчас: " << output << endl;
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
bool checking_reverse_polish_notation(string expression) {
    Stack* stack = nullptr;
    string value;
    int oper_count = 0;
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
            oper_count++;
            i--;
        }
        else if (elem == '+' || elem == '-' || elem == '*' || elem == '/') {
            if (oper_count < 2) {
                return false;
            }
            int right = pop(stack);
            int left = pop(stack);
            int result = for_calc(elem, right, left);
            push(stack, result);
            oper_count--;
        }
        else {
            return false;
        }
    }
    return oper_count == 1 && (stack != nullptr);
}
bool checking_simple_expression(string expression) {
    Stack* stack = nullptr;
    int oper_count = 0;
    bool is_oper = true;
    for (int i = 0; i < expression.length(); i++) {
        char elem = expression[i];
        if (elem == ' ') {
            continue;
        }

        if (isdigit(elem)) {
            while (isdigit(expression[i])) {
                i++;
            }
            oper_count++;
            is_oper = false;
            i--;
        }
        else if (elem == '(') {
            push_op(stack, elem);
            is_oper = true;

        }
        else if (elem == ')') {
            while (stack == nullptr || top(stack) != '(') {
                return false;
            }
            pop_op(stack);
            is_oper = false;
        }
        else if (elem == '+' || elem == '-' || elem == '*' || elem == '/') {
            if (is_oper) {
                return false;
            }
            if (oper_count < 1) {
                return false;
            }
            oper_count--;
            is_oper = true;
        }
        else {
            return false;
        }
    }
    return oper_count == 1 && (stack == nullptr) && !is_oper;
}
bool checking_direct_polish_notation(string expression) { 
    Stack* stack = nullptr;
    string value;
    int oper_count = 0;
    for (int i = expression.length()-1; i >=0 ; i--) {
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
            oper_count++;
            i++;
        }
        else if (elem == '+' || elem == '-' || elem == '*' || elem == '/') {
            if (oper_count < 2) {
                return false;
            }
            int right = pop(stack);
            int left = pop(stack);
            int result = for_calc(elem, left, right);
            push(stack, result);
            oper_count--;
        }
        else {
            return false;
        }
    }
    return oper_count == 1 && (stack != nullptr);
}
int calculate_simple_expression(string expression) {
    Stack* stack_for_nums = nullptr;
    Stack* stack_for_opers = nullptr;
    string value;
    for (int i = 0; i < expression.length(); i++) {
        char elem = expression[i];
        if (elem == ' ') {
            continue;
        }
        if (isdigit(elem)) {
            value = "";
            while (isdigit(expression[i])) {
                value += expression[i];
                i++;
            }
            int res = stoi(value);
            cout <<"Текущее число: "<< res << endl;
            push(stack_for_nums, res);
            i--;
        }
        else if (elem == '(') {
            push_op(stack_for_opers, elem);

        }
        else if (elem == ')') {
            while (stack_for_opers != nullptr && stack_for_opers->oper != '(') {
                char oper = pop_op(stack_for_opers);
                int right = pop(stack_for_nums);
                int left = pop(stack_for_nums);
                int result = for_calc(oper, right, left);
                push(stack_for_nums, result);
            }
            pop_op(stack_for_opers);
        }
        else if (elem == '+' || elem == '-' || elem == '*' || elem == '/') {
            while (stack_for_opers != nullptr && priority_of_operations(stack_for_opers->oper) >= priority_of_operations(elem)) {
                char oper = pop_op(stack_for_opers);
                int right = pop(stack_for_nums);
                int left = pop(stack_for_nums);
                int result = for_calc(oper, right, left);
                push(stack_for_nums, result);
            }
            push_op(stack_for_opers, elem);
        }
    }
    while (stack_for_opers != nullptr) {
        char oper = pop_op(stack_for_opers);
        if (stack_for_nums == nullptr) {
            cout << "Ошибка: Стек чисел пуст!";
            break;
        }
        int right = pop(stack_for_nums);
        if (stack_for_nums == nullptr) {
            cout <<"Ошибка: Стек чисел пуст!";
            break;
        }
        int left = pop(stack_for_nums);
        int result = for_calc(oper, left, right);
        push(stack_for_nums, result);
    }
    return pop(stack_for_nums);
}
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
            int result = for_calc(elem, right,left);
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
            cout <<"Число, которое нашли: "<< res << endl;
            push(stack, res);
            i++;
        }
        else if (elem == '+' || elem == '-' || elem == '*' || elem == '/') {
            int right = pop(stack);
            int left = pop(stack);
            int result = for_calc(elem, left, right);
            push(stack, result);
        }
    }
    return pop(stack);
}
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
                reverse_pol_not =  make_reverse_polish_notation(expression);
                cout << "Ваше выражение в обратной польской нотации: " << reverse_pol_not<< endl;
                break;
            case 2:
                direct_pol_not = make_direct_polish_notation(expression);
                cout << "Ваше выражение в прямой польской нотации: " << direct_pol_not<<endl;
                break;
            }
            break;
        case 3:
            cout << "Выберите действие:" << endl;
            cout << "1. Проверить простое выражение." << endl;
            cout << "2. Проверить обратную польскую нотацию." << endl;
            cout << "3. Проверить прямую польскую нотацию." << endl;
            cin >> i;
            switch (i) {
            case 1:
                cout << "Ваше простое выражение: ";
                if (checking_simple_expression(expression)) {
                    cout << "Correct" << endl;
                }
                else {
                    cout << "Incorrect" << endl;
                }
                break;
            case 2:
                cout << "Ваше выражение в обратной польской нотации: ";
                if (checking_reverse_polish_notation(reverse_pol_not)) {
                    cout << "Correct" << endl;
                }
                else {
                    cout << "Incorrect" << endl;
                }
                break;
            case 3:
                cout << "Ваше выражение в прямой польской нотации: ";
                if (checking_direct_polish_notation(direct_pol_not)) {
                    cout << "Correct" << endl;
                }
                else {
                    cout << "Incorrect" << endl;
                }
                break;
            }
            break;
        case 4:
            cout << "Простое выражение:  " << expression << endl;
            res = calculate_simple_expression(expression);
            cout <<"Его результат: "<< res << endl;
            break;
        case 5:
            cout << "Обратная польская нотация:  " << reverse_pol_not << endl;
            res = calculate_expression_in_reverse_polish_notation(reverse_pol_not);
            cout << "Её результат: " << res << endl;
            break;
        case 6:
            cout << "Полученная прямая польская нотация:  " << direct_pol_not << endl;
            res = calculate_expression_in_direct_polish_notation(direct_pol_not);
            cout << "Её результат: " << res << endl;
            break;
        case 7:
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