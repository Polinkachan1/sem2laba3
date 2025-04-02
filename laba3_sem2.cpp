#include <iostream>
#include <string>
using namespace std;

struct Stack
{
    char number;
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
    cout << "6. Выход!" << endl;
}
void push(Stack*& top, char num) {
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
int priority_of_operations(char elem) {
    switch (elem) {
    case '-':case '+': return 1;
    case '*':case '/': return 2;
    default: return 0;
    }
}
char top(Stack* top_elem) {
    if (top_elem == nullptr) {
        throw std::runtime_error("Стек пуст!");
    }
    return top_elem->number;
}
void for_calc(Stack*& stack,char elem) {
    int first = pop(stack);
    int second = pop(stack);
    int res = 0;
    switch (elem) {
    case '-':
        res = first - second;
        cout << first << '-' << second;
        break;
    case '+':  
        res = first + second;
        cout << first << '+' << second;
        break;
    case '*': 
        res = first * second;
        cout << first << '*' << second << ' = ' << res << endl;
        break;
    case '/': 
        res = first / second;
        cout << first << '/' << second << ' = ' << res << endl;
        break;
    }
    push(stack, res);
}
string make_reverse_polish_notation(string expression) {
    string result = "", make_num = "";
    Stack* stack = 0;
    for (int i = 0; i < expression.length(); i++) {
        char elem = expression[i];
        if (isdigit(elem)) {
            make_num += elem;
        }
        else {
            if (!make_num.empty()) {
                result += make_num;
                result += ' ';
                make_num.clear();
            }
            if (elem == '(') {
                push(stack, elem);
            }
            else if (elem == ')') {
                while (stack != nullptr and stack->number != '(') {
                    result += pop(stack);
                    result += ' ';
                }
                pop(stack);
            }
            else {
                while (stack != nullptr and priority_of_operations(stack->number) >= priority_of_operations(elem)) {
                    result += pop(stack);
                    result += ' ';
                }
                push(stack, elem);
            }
        }

    }
    if (!make_num.empty()) {
        result += make_num;
        result += ' '; 
    }
    while (stack != nullptr) {
        result += pop(stack);
        result += ' ';
    }
    return result;
}
string make_direct_polish_notation(string expression) {
    Stack* stack = nullptr;
    string result = "", make_num = "";
    for (int i = expression.length()-1; i >= 0; i--) {
        char elem = expression[i];
        if (isdigit(elem)) {
            make_num += elem;
        }
        else {
            if (!make_num.empty()) {
                result += make_num;
                result += ' ';
                make_num.clear();
            }
            if (elem == ')') {
                push(stack, elem);
            }
            else if (elem == '(') {
                while (stack != nullptr && top(stack) != ')') {
                    result += pop(stack);
                    result += ' ';
                }
                pop(stack);
            }
            else {
                while (stack != nullptr && priority_of_operations(top(stack)) > priority_of_operations(elem)) {
                    result += pop(stack);
                    result += ' ';
                }
                push(stack, elem);
            }
        }
    }
    if (!make_num.empty()) {
        result += make_num;
        result += ' ';
    }
    while (stack != nullptr) {
        result += pop(stack);
        result += ' ';
    }
    reverse(result.begin(), result.end());
    return result;
}
void checking_simple_expression(string expression) {}
void checking_reverse_polish_notation(string expression) {}
void checking_direct_polish_notation(string expression) {}
void calculate_simple_expression(string expression) {}
int calculate_expression_in_reverse_polish_notation(string expression) {
    string result = "", make_num = "";
    Stack* stack = 0;
    for (int i = 0; i < expression.length(); i++) {
        char elem = expression[i];
        if (isdigit(elem)) {
            make_num += elem;
        }
        else {
            if (!make_num.empty()) {
                push(stack, stoi(make_num));
                make_num.clear();
            }
            else {
                for_calc(stack, elem);
            }
        }

    }
    int answ = pop(stack);
    return answ;

}
void calculate_expression_in_direct_polish_notation(string expression) {}
void idz() {}
int main() {
    setlocale(0, "");
    int identificator, i;
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
            break;
        case 2:
            cout << "Выберите действие:" << endl;
            cout << "1. Преобразовать выражение в обратную польскую нотацию." << endl;
            cout << "2. Преобразовать выражение в прямую польскую нотацию. " << endl;
            //expression = "1+2*5";
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
            expression = "(3-1)+4";
            cout<<calculate_expression_in_reverse_polish_notation(expression)<<endl;
            break;
        case 5:
            idz();
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