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

Queue::Element *Queue::Element::getNext()
{
    return _next;
}

void Queue::Element::setNext(Element *next)
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

Queue::Iterator::Iterator()
{
    this->curElement = nullptr;
}

Queue::Iterator::Iterator(Element *element)
{
    this->curElement = element;
}

Queue::Iterator::~Iterator() = default;

Queue::Element* Queue::Iterator::getCurElement()
{
    return this->curElement;
}

void Queue::Iterator::setCurElement(Element* element)
{
    this->curElement = element;
}

Queue::DATA_TYPE Queue::Iterator::getElement(size_t &size)
{
    if (curElement == nullptr)
    {
        throw Container::Error("Can't give element the iterator points to an empty element");
    }
    size = curElement->getSize();
    return curElement->getContent();    
}

void Queue::Iterator::goToNext()
{
    if (!hasNext())
    {
        throw Container::Error("no next element");
    }
    curElement->getNext();
} 

bool Queue::Iterator::hasNext()
{
    if (curElement == nullptr)
    {
        return false;
    }  
    else if (curElement->getNext() == nullptr)
    {
        return false;
    }
    return true;    
}

bool Queue::Iterator::equals(Container::Iterator* right)
{
    if ((dynamic_cast<Iterator*>(right)->curElement == this->curElement))
    {
        return true;
    }
    return false;    
}

void *Queue::allocMem(size_t size)
{
    return _memory.allocMem(size);
}

void Queue::freeMem(void *ptr)
{
    _memory.freeMem(ptr);
}

void Queue::sizeChange(int size)
{
    this->_size += size;
}

Queue::Queue(MemoryManager &memory) : AbstractQueue(memory)
{
    allocMem(sizeof(Element));
    Element *newElement = new Element();
    this->_head = newElement;
    this->_tail = this->_head;
    this->_memory = memory;
    this->_size = 0;
}

Queue::~Queue()
{
    Queue::clear();
}

int Queue::push(void *elem, size_t size)
{
    if (_size == 0)
    {
        //add error if size > maxSize
        allocMem(sizeof(Element));
        Element *newElement = new Element(elem, size);
        this->_tail = newElement;
        this->_head = this->_tail;
    }
    else
    {
        //add error if size > maxSize
        allocMem(sizeof(Element));
        Element *newElement = new Element(elem, size);
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

    Element *newHead = _head->getNext();
    freeMem(this->_head);
    delete this->_head;
    this->_head = newHead;
    sizeChange(-1);
    return 0;
}

void *Queue::front(size_t &size)
{
    size = this->_head->getSize();
    return this->_head->getContent();
}

void *Queue::back(size_t &size)
{
    size = this->_tail->getSize();
    return this->_tail->getContent();
}

int Queue::insert(AbstractQueue::Iterator* iter, DATA_TYPE elem, size_t size)
{
    auto iterator = dynamic_cast<Iterator*>(iter);
    if ((iterator->getCurElement() == nullptr))
    {
        return 1;
    }

    Element* catcherElem = iterator->getCurElement();
    allocMem(sizeof(Element));
    auto newElement = new Element(elem, size);
    Element* oldNextElement = catcherElem->getNext();
    catcherElem->setNext(newElement);
    newElement->setNext(oldNextElement);    
    iterator->setCurElement(newElement);
    sizeChange(1);
    return 0;
}

void Queue::clear()
{
    if (this->empty())
    {
        return;
    }

    while (_head != nullptr)
    {
        pop();
    }   
}

bool Queue::empty()
{
    if (_size == 0)
    {
        return true;
    }
    return false;
}
