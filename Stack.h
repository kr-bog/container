#ifndef STACK_H
#define STACK_H

#include "Container.h"

template <typename T>
class Stack : public Container<T> {
private:
    Node<T>* head;         //указатель на верхний элемент стека
    std::size_t count;     //количество элементов

    void Clear();          //очищает стек
    void CopyFrom(const Stack<T>& other);  //копирует элементы из другого стека

protected:
    void Print(std::ostream& os) const override;  //вывод элементов в поток

public:
    Stack();                        //конструктор по умолчанию
    Stack(const Stack<T>& other);   //конструктор копирования
    Stack(Stack<T>&& other) noexcept; //конструктор перемещения
    ~Stack();                        //деструктор

    Stack<T>& operator=(const Stack<T>& other);       //копирующее присваивание
    Stack<T>& operator=(Stack<T>&& other) noexcept;   //перемещающее присваивание
    Container<T>& operator=(const Container<T>& other) override; //присваивание от базового контейнера

    void Push(const T& value) override;  //добавление элемента копированием на вершину
    void Push(T&& value) override;       //добавление элемента перемещением на вершину
    void Pop() override;                 //удаление верхнего элемента
    T& GetFront() override;              //доступ к верхнему элементу
    bool IsEmpty() const override;       //проверка на пустоту стека
    std::size_t Size() const override;   //количество элементов в стеке
};

#include "Stack_impl.h"

#endif // STACK_H
