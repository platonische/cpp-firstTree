#ifndef QUEUEINTVALUE_H
#define QUEUEINTVALUE_H
#include "src/AbstractQueue.h"

using namespace std;

struct ElementIntValue: public Element<ElementIntValue> {
   int value;
};


class QueueIntValue: public AbstractQueue<ElementIntValue>
{
public:
    QueueIntValue(): AbstractQueue<ElementIntValue>() {};

    virtual ElementIntValue* createElement(int);
    virtual ElementIntValue* findElement(int);

    virtual int getValue(ElementIntValue*);
    virtual void setValue(ElementIntValue*, int);



    virtual string toString();
    virtual string toString(ElementIntValue*);

    virtual void sampleData(int*);
};

#endif // QUEUEINTVALUE_H
