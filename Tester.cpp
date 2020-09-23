#include "Tester.h"
#include <iostream>
#include "Mem.h"
#include <vector>
#include <numeric>
#include <ctime>
#include "Queue.h"
#include <list>

int Tester::testFailed(string testName)
{
    std::cout << testName + " Fail" << std::endl;
    return 0;
}

int Tester::testPassed(string testName)
{
    std::cout << testName + " Passed" << std::endl;
    return 0;
}

int Tester::testSimpleTestFrom1To12Elements()
{
    string testName = "Simple test for 12 elements";
    Mem mem(100);
    Queue queue(mem);
    vector<int> vt = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    for (auto v : vt)
    {
        if (queue.push(0, (13 - v)))
        {
            std::cout << "push " << v << " fail" << std::endl;
            return testFailed(testName);
        }
    }
    std::cout << "added three first child our root: Done" << std::endl;

    Queue::Iterator *iterat = queue.begin();
    int counter = 11;
    while (iterat->hasNext())
    {
        size_t size;
        iterat->getElement(size);
        if (size != vt[counter])
        {
            std::cout << "error in traversing with " << counter << std::endl;
            return testFailed(testName);
        }
        iterat->goToNext();
        counter--;
    }
    std::cout << "checking for the existence of elements: Done" << std::endl;

    //удаление первых 5 элементов
    for (int i = 0; i < 5; i++)
    {
        if (queue.pop() != 0)
        {
            std::cout << "cannot delete" << std::endl;
            return testFailed(testName);
        }
    }
    std::cout << "deleted first five elements: Done" << std::endl;

    //проверка размера очереди
    if (queue.size() != 7)
    {
        std::cout << "wrong queue size" << std::endl;
        return testFailed(testName);
    }

    std::cout << "checking the remaining items 1, 2, 3, 4, 5, 6" << std::endl;
    vt = {1, 2, 3, 4, 5, 6, 7};
    counter = vt.size() - 1;
    iterat = queue.begin();
    while (iterat->hasNext())
    {
        size_t size;
        iterat->getElement(size);
        if (size != vt[counter])
        {
            std::cout << "error in traversing with" << counter << std::endl;
            return testFailed(testName);
        }
        counter--;
        iterat->goToNext();
    }

    for (auto v : vt)
    {
        size_t size;
        iterat = queue.find(0, v);
        iterat->getElement(size);
        if (size != v)
        {
            std::cout << "not found " << v << std::endl;
            return testFailed(testName);
        }
    }
    std::cout << "checking remaining elements : Done" << std::endl;

    std::cout << "checking for deleted items " << std::endl;
    vt = {8, 9, 10, 11, 12};
    for (auto v : vt)
    {
        size_t size;
        iterat = queue.find(0, v);
        iterat->getElement(size);
        if (size == v)
        {
            std::cout << "found " << v << std::endl;
            return testFailed(testName);
        }
    }
    std::cout << "checking for deleted items : Done" << std::endl;

    return testPassed(testName);
}

int Tester::testOn10000FirstElements()
{
    const string testName = "Test on 10 000 first elements";
    Mem mem(10000);
    Queue queue(mem);
    vector<int> vt(10000);
    std::iota(vt.begin(), vt.end(), 0);
    int i = 0;
    std::cout << "add 10 000 push in our queue" << std::endl;
    const unsigned time = clock();
    for (auto &v : vt)
    {
        i++;
        if (queue.push(&v, i) == 1)
        {
            std::cout << "push " << v << " fail" << std::endl;
            return testFailed(testName);
        }
    }
    std::cout << "time to add 10 000 elements = " << (double)(clock() - time) / CLOCKS_PER_SEC << std::endl;
    std::cout << "added 10 000 elements : Done" << std::endl;

    std::cout << "checking for the existence of added elements" << std::endl;
    Queue::Iterator *iterator = queue.begin();
    int counter = 1;
    while (iterator->hasNext())
    {
        size_t size;
        int v = *static_cast<int *>(iterator->getElement(size));
        if (vt[counter++] == v)
        {
            std::cout << "Error in comparing values with " << counter << std::endl;
            return testFailed(testName);
        }
        iterator->goToNext();
    }
    std::cout << "checking elements : Done" << std::endl;

    std::cout << "Comparing the values" << std::endl;
    iterator = queue.begin();
    Queue::Iterator *newIterator = queue.begin();
    while (iterator->hasNext())
    {
        if (!(iterator->equals(newIterator)))
        {
            std::cout << "error with equal" << std::endl;
            return testFailed(testName);
        }
        iterator->goToNext();
        newIterator->goToNext();
    }
    std::cout << "Comparing the values : Done" << std::endl;
    return testPassed(testName);
}

int Tester::testOn10000000Elements()
{
    string testName = "Test 10000000 elements";
    Mem mem(10000000);
    Queue queue(mem);
    int N = 1e7;
    vector<int> vt(N);
    iota(vt.begin(), vt.end(), 0);

    std::cout << "Add 10 mln elements" << std::endl;
    unsigned int time = clock();
    for (auto &v : vt)
    {
        if (queue.push(&v, 1) == 1)
        {
            std::cout << "Element " << v << " failed" << std::endl;
            return testFailed(testName);
        }
    }
    std::cout << "time to add 10 elements = " << (double)(clock() - time) / CLOCKS_PER_SEC << std::endl;
    std::cout << "add 10 mln elements : Done" << std::endl;

    std::cout << "passage through our queue and remove every element from begin" << std::endl;
    Queue::Iterator *iterator = queue.begin();
    int index = 0;
    time = clock();
    while (index != 9999999)
    {
        queue.pop();
        index++;
    }
    std::cout << "time to passage 10 mln items = " << (double)(clock() - time) / CLOCKS_PER_SEC << std::endl;
    return testPassed(testName);
}

int Tester::testGap()
{
    string testName = "Gap from sm to sm";
    Mem mem(10000);
    Queue queue(mem);
    Queue::Iterator *iterator = queue.newIterator();
    vector<int> vt(10000);
    std::iota(vt.begin(), vt.end(), 0);
    int i = 0;
    std::cout << "add 10000 elements in our tree" << std::endl;
    unsigned int time = clock();
    for (auto &v : vt)
    {
        i++;
        if (queue.push(&v, i) == 1)
        {
            std::cout << "insert " << v << " fail" << std::endl;
            return testFailed(testName);
        }
    }

    std::cout << "time to add 10 000 elements = " << (double)(clock() - time) / CLOCKS_PER_SEC << std::endl;
    std::cout << "added 10000 elements : Done" << std::endl;

    iterator = queue.begin();
    const int GAP_START = 57;
    const int GAP_END = 5648;

    cout << "size before removal = " << queue.size() << std::endl;
    time = clock();
    i = 0;
    while (iterator->hasNext())
    {
        if ((i > GAP_START) && (i < GAP_END))
        {
            queue.remove(iterator);
            i++;
            continue;
        }
        i++;
        iterator->goToNext();
    }

    std::cout << "time to remove items from point " << GAP_START << " to " << GAP_END << " = " << (double)(clock() - time) / CLOCKS_PER_SEC << std::endl;
    std::cout << "size after removal = " << queue.size() << std::endl;
    std::cout << "passage through our queue" << std::endl;
    std::cout << "Test Gap : done" << std::endl;
    return testPassed(testName);
}

int Tester::testRemoveOddElements()
{
    string testName = "Remove odd elements";
    Mem mem(1000000);
    Queue queue(mem);
    Queue::Iterator *iterator = queue.begin();
    const int N = 1000;
    vector<int> vt(N);
    iota(vt.begin(), vt.end(), 0);
    std::cout << "add first 1000 elements" << std::endl;
    unsigned int time = clock();
    int i = 0;
    for (auto &v : vt)
    {        
        if (queue.insert(iterator, &v, sizeof(v)) == 1)
        {
            std::cout << "insert " << v << " failed" << std::endl;
            return testFailed(testName);
        }
    }
    std::cout << "time to add " << N << " items  = " << static_cast<double>(clock() - time) / CLOCKS_PER_SEC << std::endl;
    std::cout << "Added 1,000 elements : Done" << std::endl;

    time = clock();
    cout << "remove odd items" << endl;
    i = 1;
    iterator = queue.begin();
    while (iterator->hasNext())
    {
        iterator->goToNext();
        size_t size;
		int v = *static_cast<int*>(iterator->getElement(size));
        if (vt[i] == v)
        {
            queue.remove(iterator);
            i += 2;
        }
    }

    std::cout << "time to remove odd items  = " << static_cast<double>(clock() - time) / CLOCKS_PER_SEC << std::endl;
    std::cout << "size after removal = " << queue.size() << std::endl;
    return testPassed(testName);
}

int Tester::testCheckExceptionIteratorBlock()
{
    string test_name = "Test check empty Iterator";
    Mem mem(100);
    Queue queue(mem);
    try
    {
        std::cout << "check our Iterator throught Error block" << std::endl;
        Queue::Iterator *iterator = queue.newIterator();
        size_t size;
        iterator->getElement(size);
    }
    catch (Container::Error e)
    {
        std::cout << "Our Iterator hit the exception block" << std::endl;
        string s_error = "Can't give element the iterator points to an empty element";
        if (s_error != e.msg)
        {
            std::cout << "other error" << std::endl;
            return testFailed(test_name);
        }
    }
    return testPassed(test_name);
}
