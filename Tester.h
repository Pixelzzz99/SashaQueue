#pragma once
#include "Queue.h"

class Tester
{
    private:
    int testFailed(string testName);
    int testPassed(string testName);

    public:

    int testSimpleTestFrom1To12Elements();
    int testOn10000FirstElements();
    int testOn10000000RootChild();
    int testGap();
    int testCheckExceptionIteratorBlock();
};
