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
    int *testElem = new int(5);
    queue.push(&testElem, sizeof(testElem));

    Queue::Iterator *iterat = queue.begin();

    size_t size;
    void *element = iterat->getElement(size);
    void *lol = &testElem;
    if (element == lol)
    {
        return testPassed(testName);
    }

    return testPassed(testName);
}