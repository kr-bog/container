#ifndef STACK_IMPL_H
#define STACK_IMPL_H

template <typename T>
//функция очищения стека
void Stack<T>::Clear() {
    while (head != nullptr) {            // ока стек не пуст
        Node<T>* temp = head;            //сохраняем текущий узел
        head = head->next;               // переходим к следующему
        delete temp;                     //удаляем узел
    }
    count = 0;                           //размер = 0
}

template <typename T>
// копирует содержимое другого стека за один проход
void Stack<T>::CopyFrom(const Stack<T>& other) {
    if (other.head == nullptr) {         // если другой стек пуст
        head = nullptr;
        count = 0;
        return;
    }

    Node<T>* curr = other.head;          // текущий узел в другом стеке
    head = new Node<T>(curr->data);      // создаём первый узел копии
    Node<T>* tail = head;                // хвост для быстрого добавления
    curr = curr->next;

    while (curr != nullptr) {            // копируем остальные узлы
        tail->next = new Node<T>(curr->data);
        tail = tail->next;               // сдвигаем хвост
        curr = curr->next;               // идём к следующему узлу
    }

    count = other.count;                 // копируем размер
}

template <typename T>
// функция вывода стека
void Stack<T>::Print(std::ostream& os) const {
    os << "Stack[";
    Node<T>* curr = head;
    bool first = true;
    while (curr != nullptr) {
        if (!first) os << ", ";
        os << curr->data;
        first = false;
        curr = curr->next;
    }
    os << "]";
}

// конструкторы

template <typename T>
// создаём пустой стек
Stack<T>::Stack() : head(nullptr), count(0) {}

template <typename T>
// конструктор копирования
Stack<T>::Stack(const Stack<T>& other) : head(nullptr), count(0) {
    CopyFrom(other);
}

template <typename T>
// конструктор перемещения: переносим данные без копирования
Stack<T>::Stack(Stack<T>&& other) noexcept : head(other.head), count(other.count) {
    other.head = nullptr;
    other.count = 0;
}

template <typename T>
// деструктор
Stack<T>::~Stack() {
    Clear();
}

// операторы присваивания

template <typename T>
// копирующее присваивание
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
    if (this != &other) {
        Clear();
        CopyFrom(other);
    }
    return *this;
}

template <typename T>
// перемещающее присваивание
Stack<T>& Stack<T>::operator=(Stack<T>&& other) noexcept {
    if (this != &other) {
        Clear();
        head = other.head;
        count = other.count;
        other.head = nullptr;
        other.count = 0;
    }
    return *this;
}

template <typename T>
// присваивание от базового контейнера с проверкой типа
Container<T>& Stack<T>::operator=(const Container<T>& other) {
    const Stack<T>* ptr = dynamic_cast<const Stack<T>*>(&other);
    if (ptr != nullptr) {
        *this = *ptr;
    } else {
        throw ContainerException("ошибка, очередь пуста");
    }
    return *this;
}

// основные методы

template <typename T>
// добавляет элемент на вершину стека копированием
void Stack<T>::Push(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    newNode->next = head;
    head = newNode;
    ++count;
}

template <typename T>
// добавляет элемент на вершину стека перемещением
void Stack<T>::Push(T&& value) {
    Node<T>* newNode = new Node<T>(std::move(value));
    newNode->next = head;
    head = newNode;
    ++count;
}

template <typename T>
// удаляет верхний элемент стека
void Stack<T>::Pop() {
    if (IsEmpty()) {
        throw ContainerException("Pop from empty stack");
    }
    Node<T>* temp = head;
    head = head->next;
    delete temp;
    --count;
}

template <typename T>
// возвращает ссылку на верхний элемент стека
T& Stack<T>::GetFront() {
    if (IsEmpty()) {
        throw ContainerException("GetFront from empty stack");
    }
    return head->data;
}

template <typename T>
// проверяет, пуст ли стек
bool Stack<T>::IsEmpty() const {
    return count == 0;
}

template <typename T>
// возвращает количество элементов в стеке
std::size_t Stack<T>::Size() const {
    return count;
}

#endif // STACK_IMPL_H
