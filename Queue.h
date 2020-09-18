#pragma once
#include <QueueAbstract.h>

class Queue : public AbstractQueue
{
private:
    typedef void *DATA_TYPE;
    class Element
    {
    private:
        Element* _next;
        DATA_TYPE _content;
        size_t _size;

    public:
        Element();
        Element(DATA_TYPE content, size_t size);        
        ~Element();
        Element* getNext();
        void setNext(Element* next);
        DATA_TYPE getContent();
        void setContent(DATA_TYPE content);
        size_t getSize();
        void setSize(size_t size);
    };

    Element* _head;
    Element* _tail;
    size_t _size;

    void* allocMem(size_t size);
    void freeMem(void* ptr);
    void sizeChange(int size);
    
public:

    Queue(MemoryManager& mem);

    ~Queue();

    int push(void *elem, size_t size) override;    

    int pop() override;    

    void* front(size_t &size) override;
    
    void* back(size_t &size) override;

    int insert(Iterator* iter, void* elem, size_t size) override;

    bool empty() override;
    {
        if (this->head == nullptr)
            return 0;
        if (this->size == 0)
            return 0;
        return 1;
    }

    class Iterator
    {
        queue<DATA_TYPE> *currQueue;
        Element *currElem;

        Iterator(queue *currQue, Element *elem)
        {
            this->currQueue = currQue;
            this->currElem = elem;
        }

        ~Iterator(){};

        void goToNext()
        {
            this->currElem = currelem->next;
        }

        DATA_TYPE &get()
        {
            return this->currElem->content;
        }

        bool equal(Iterator *iter)
        {
            if (this->currQueue != iter->currQueue)
                return 0;
            if (this->currElem != iter->currElem)
                return 0;
            return 1;
        }
    };
    void insert(Iterator *iter, DATA_TYPE content)
    {
        //iter->currElem->content = content; ���� ������ ��������
        Element *insElem = new Element(iter->currElem, content);
    }
};
