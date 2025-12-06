    #ifndef QUEUE_H
    #define QUEUE_H

    #include "Container.h"

    template <typename T>
    class Queue : public Container<T> {
    private:
        Node<T>* front;     //указатель на 1
        Node<T>* back;      //последний
        std::size_t count;  // количество элементов

        void Clear();       // очищает очередь
        void CopyFrom(const Queue<T>& other);   // копирует элементы из другой очереди

    protected:
        void Print(std::ostream& os) const override;    // вывод элементов в поток

    public:
        Queue();
        Queue(const Queue<T>& other);       // конструктор копирования
        Queue(Queue<T>&& other) noexcept;   // конструктор перемещения
        ~Queue();

        Queue<T>& operator=(const Queue<T>& other);     // копирующее присваивание
        Queue<T>& operator=(Queue<T>&& other) noexcept; // перемещающее присваивание
        Container<T>& operator=(const Container<T>& other) override;    // присваивание от базового контейнера

        void Push(const T& value) override;  //добавление элемента копированием
        void Push(T&& value) override;       //добавление элемента перемещением
        void Pop() override;                 //удаление первого элемента
        T& GetFront() override;              //доступ к первому элементу
        bool IsEmpty() const override;       //проверка на пустоту
        std::size_t Size() const override;   //количество элементов
    };

    #include "Queue_impl.h"

    #endif // QUEUE_H
