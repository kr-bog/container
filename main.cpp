#include <iostream>
#include <string>
#include <windows.h>
#include "Stack.h"
#include "Queue.h"

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "--- Стек ---" << endl;

    //создаем стек S
    Stack<int> s;
    s.Push(10);
    s.Push(20);
    s.Push(30);
    cout << "Добавили 10, 20, 30: \n" << s << endl;
    cout << "Размер: " << s.Size() << endl;
    cout << "Вершина: " << s.GetFront() << endl;

    s.Pop();    //удаляем верхний элемент
    cout << "После Pop: " << s << endl;

    //создаем копию стека через конструктор копирования
    Stack<int> s2 = s;
    cout << "Копия s2: " << s2 << endl;

    //создаем стек через перемещающий конструктор
    Stack<int> s3 = move(s2);
    cout << "s3 после move: " << s3 << endl;
    cout << "s2 после move: " << s2 << endl;

    try {
        Stack<int> empty;
        empty.Pop();
    } catch (ContainerException& e) {
        cout << "Исключение: " << e.what() << endl;
    }

    cout << endl << "--- Очередь ---" << endl;

    // Создаем очередь q
    Queue<int> q;
    q.Push(10);
    q.Push(20);
    q.Push(30);
    cout << "Добавили 10, 20, 30: \n" << q << endl;
    cout << "Размер: " << q.Size() << endl;
    cout << "Первый: " << q.GetFront() << endl;

    q.Pop();    // удаляем первый элемент очереди
    cout << "После Pop: " << q << endl;

    Queue<int> q2 = q;  //копируем очередь через конструктор копирования
    cout << "Копия q2: " << q2 << endl;

    Queue<int> q3 = move(q2);   //// Перемещаем очередь в q3
    cout << "q3 после move: " << q3 << endl;
    cout << "q2 после move: " << q2 << endl;

    try {
        Queue<int> empty;
        empty.Pop();
    } catch (ContainerException& e) {
        cout << "Исключение: " << e.what() << endl;
    }

    cout << endl << "--- Полиморфизм ---" << endl;

    Stack<int> st;
    Queue<int> qu;

    Container<int>* c1 = &st;
    Container<int>* c2 = &qu;

    // Работаем через базовый интерфейс Container
    c1->Push(1);
    c1->Push(2);
    c2->Push(1);
    c2->Push(2);

    cout << "Stack: " << *c1 << ", front = " << c1->GetFront() << endl;
    cout << "Queue: " << *c2 << ", front = " << c2->GetFront() << endl;

    return 0;
}
