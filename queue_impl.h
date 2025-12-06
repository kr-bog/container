#ifndef QUEUE_IMPL_H
#define QUEUE_IMPL_H

template <typename T>
//функция очищения очереди
void Queue<T>::Clear() {
    while (front != nullptr) {
        Node<T>* temp = front;
        front = front->next;
        delete temp;
    }
    back = nullptr;
    count = 0;
}

//копирует содержимое другой очереди
template <typename T>
void Queue<T>::CopyFrom(const Queue<T>& other) {
    if (other.front == nullptr) {
        front = back = nullptr;
        count = 0;
        return;
    }

    Node<T>* curr = other.front;            //текущий узел в другой очереди
    front = new Node<T>(curr->data);        //создаём первый узел копии
    back = front;
    curr = curr->next;

    while (curr != nullptr) {                   //копируем остальные узлы
        back->next = new Node<T>(curr->data);   //создаём новый узел и добавляем в конец
        back = back->next;                      //сдвигаем хвост
        curr = curr->next;                      //идём к следующему узлу в другой очереди
    }

    count = other.count;
}

//функция вывода
template <typename T>
void Queue<T>::Print(std::ostream& os) const {
    os << "Queue[";             //начало ввода
    Node<T>* curr = front;      //первый узел
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
//создаем пустую очередь
template <typename T>
Queue<T>::Queue() : front(nullptr), back(nullptr), count(0) {}

//пустая очередь для копирование
template <typename T>
Queue<T>::Queue(const Queue<T>& other) : front(nullptr), back(nullptr), count(0) {
    CopyFrom(other);
}

//переносит данные из другой очереди без копирования
template <typename T>
Queue<T>::Queue(Queue<T>&& other) noexcept
    : front(other.front), back(other.back), count(other.count) {
    other.front = nullptr;
    other.back = nullptr;
    other.count = 0;
}

//диструктор
template <typename T>
Queue<T>::~Queue() {
    Clear();
}

//операторы присваивания
//копирующее присваивание
template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
    if (this != &other) {
        Clear();
        CopyFrom(other);
    }
    return *this;
}

//перемещающее присваивание
template <typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& other) noexcept {
    if (this != &other) {
        Clear();
        front = other.front;
        back = other.back;
        count = other.count;
        other.front = nullptr;
        other.back = nullptr;
        other.count = 0;
    }
    return *this;
}

// присваивание от базового контейнера с проверкой типа
template <typename T>
Container<T>& Queue<T>::operator=(const Container<T>& other) {
    const Queue<T>* ptr = dynamic_cast<const Queue<T>*>(&other);
    if (ptr != nullptr) {
        *this = *ptr;
    } else {
        throw ContainerException("ошибка");
    }
    return *this;
}

// основные методы
//добавляет элемент в конец очереди копированием
template <typename T>
void Queue<T>::Push(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (back == nullptr) {
        front = back = newNode;
    } else {
        back->next = newNode;
        back = newNode;
    }
    ++count;
}

//добавляет элемент в конец очереди перемещением
template <typename T>
void Queue<T>::Push(T&& value) {
    Node<T>* newNode = new Node<T>(std::move(value));
    if (back == nullptr) {
        front = back = newNode;
    } else {
        back->next = newNode;
        back = newNode;
    }
    ++count;
}

//удаляет первый элемент выбрасывает исключение при пустой очереди
template <typename T>
void Queue<T>::Pop() {
    if (IsEmpty()) {
        throw ContainerException("Ощибка, очередь пуста");
    }
    Node<T>* temp = front;
    front = front->next;
    if (front == nullptr) {
        back = nullptr;
    }
    delete temp;
    --count;
}

//возвращает ссылку на первый элемент
template <typename T>
T& Queue<T>::GetFront() {
    if (IsEmpty()) {
        throw ContainerException("ошибка");
    }
    return front->data;
}

//проверяет, пуста ли очередь
template <typename T>
bool Queue<T>::IsEmpty() const {
    return count == 0;
}

//возвращает количество элементов в очереди
template <typename T>
std::size_t Queue<T>::Size() const {
    return count;
}

#endif // QUEUE_IMPL_H
