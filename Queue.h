#pragma once
#include "QueueAbstract.h"

class Queue : public AbstractQueue
{
private:
    typedef void *DATA_TYPE;
    class Element
    {
    private:
        Element *_next;
        DATA_TYPE _content;
        size_t _size;

    public:
        Element();
        Element(DATA_TYPE content, size_t size);
        ~Element();
        Element *getNext();
        void setNext(Element *next);
        DATA_TYPE getContent();
        void setContent(DATA_TYPE content);
        size_t getSize();
        void setSize(size_t size);
    };

    Element *_head;
    Element *_tail;
    size_t _size;

    void *allocMem(size_t size);
    void freeMem(void *ptr);
    void sizeChange(int size);
    bool checkMemory(size_t size);

public:
    class Iterator : public AbstractQueue::Iterator
    {
    private:
        Element *curElement;
        Element *step(Element *cur);

    public:
        Iterator();
        Iterator(Element *element);
        ~Iterator();

        Element* getCurElement();
        void setCurElement(Element *element);

        DATA_TYPE getElement(size_t &size) override;
        void goToNext() override;
        bool hasNext() override;
        bool equals(Container::Iterator *right) override;
    };

    Queue(MemoryManager &mem);

    ~Queue();

    int push(void *elem, size_t size) override;

    int pop() override;

    void *front(size_t &size) override;

    void *back(size_t &size) override;

    int insert(AbstractQueue::Iterator *iter, DATA_TYPE elem, size_t size) override;

    int size() override;

    size_t max_bytes() override;

    Iterator* find(void *elem, size_t size) override;

    Iterator* newIterator() override;

    Iterator* begin() override;

    Iterator* end() override;

    void remove(Container::Iterator *iter) override;

    void clear() override;
    
    bool empty() override;  
};


