#include <Queue.h>

Queue::Element::Element()
{
    this->_content = nullptr;
    this->_next = nullptr;
    this->_size = 0;
}

Queue::Element::Element(DATA_TYPE content, size_t size)
{
    this->_content = content;
    this->_next = nullptr;
    this->_size = size;
}

Queue::Element::~Element() = default;

Queue::Element* Queue::Element::getNext()
{
    return _next;
}

void Queue::Element::setNext(Element* next)
{
    this->_next = next;
}

Queue::DATA_TYPE Queue::Element::getContent()
{
    return _content;
}

void Queue::Element::setContent(DATA_TYPE content)
{
    this->_content = content;
}

size_t Queue::Element::getSize()
{
    return _size;
}

void Queue::Element::setSize(size_t size)
{
    this->_size = size;
}

void* Queue::alloc_OURMemORY(size_t size)
{      
    return _memory.allocMem(size);
}

void Queue::freeMem(void* ptr)
{
    _memory.freeMem(ptr);
}

void Queue::sizeChange(int size)
{
    this->_size += size;
}

Queue::Queue(MemoryManager& memory) : AbstractQueue(memory)
{
    allocMem(sizeof(Element));
    Element* newElement = new Element();
    this->_head = newElement;
    this->_tail = this->_head;
    this->_memory = memory;
    this->_size = 0;
}

Queue::~Queue()
{
    Queue::Clear();
}

int Queue::push(void* elem, size_t size)
{
    if (_size == 0)
    {   
        //add error if size > maxSize  
        allocMem(sizeof(Element));
        Element* newElement = new Element(elem, size);
        this->_tail = newElement;
        this->_head = this->_tail;        
    }
    else
    {
        //add error if size > maxSize  
        allocMem(sizeof(Element));
        Element* newElement = new Element(elem, size);
        this->_tail->setNext(newElement);
        this->_tail = _tail->getNext();        
    }    
    sizeChange(1);
    return 0;
}

int Queue::pop()
{
    if (this->_head == nullptr)
    {
        return 1;
    }    

    Element* newHead = _head->getNext();
    freeMem((this->_head)->getSize());
    delete this->_head;
    this->_head = newHead;   
    sizeChange(-1);
    return 0;
}

void* Queue::front()
{
    return this->_head->getContent();
}

void* Queue::back()
{
    return this->_tail->getContent();
}