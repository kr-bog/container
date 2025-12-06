#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
#include <exception>
#include <string>
#include <cstddef>

//исключение
class ContainerException : public std::exception {
private:
    std::string msg;
public:
    explicit ContainerException(const std::string& message) : msg(message) {}

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

//Узел списка
template <typename T>
struct Node {
    T data;         //значение
    Node* next;     //указатель

    Node(const T& val) : data(val), next(nullptr) {}        //копирование
    Node(T&& val) : data(std::move(val)), next(nullptr) {}  //перемещение
};

//Абстрактный контейнер
template <typename T>
class Container {
protected:
    virtual void Print(std::ostream& os) const = 0;

public:
    virtual ~Container() = default;         // деструктор

    virtual void Push(const T& value) = 0;  //добавляет элемент по значению в контейнер
    virtual void Push(T&& value) = 0;       //перемещает элемент
    virtual void Pop() = 0;                 //удаляет
    virtual T& GetFront() = 0;              //ссылка на 1 эл контейнера
    virtual bool IsEmpty() const = 0;       //пустой контейнер
    virtual std::size_t Size() const = 0;   //кол-во эл в контейнере
    virtual Container<T>& operator=(const Container<T>& other) = 0;     // копирующее присваивание

    // operator<< через Print
    friend std::ostream& operator<<(std::ostream& os, const Container<T>& cont) {
        cont.Print(os);
        return os;
    }

    // operator>> через Push
    friend std::istream& operator>>(std::istream& is, Container<T>& cont) {
        T val;                  //вводим буфер
        if (is >> val) {
            cont.Push(val);
        }
        return is;
    }
};

#endif // CONTAINER_H
