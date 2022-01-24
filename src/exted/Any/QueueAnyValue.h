#ifndef QUEUEANYVALUE_H
#define QUEUEANYVALUE_H

#include "src/AbstractQueue.h"

using namespace std;

template <class ANY>
struct ElementAny: public Element<ElementAny<ANY>> {
   ANY value;
};

template <class ANY>
class QueueAnyValue: public AbstractQueue<ElementAny<ANY>>
{
public:
    QueueAnyValue(){};
    virtual ~QueueAnyValue(){};

    virtual ElementAny<ANY>* createElement(ANY Value){
        ElementAny<ANY>* Elem = AbstractQueue<ElementAny<ANY>>::createElement();
        this->setValue(Elem, Value);
        return Elem;
    };

    virtual ElementAny<ANY>* findElement(ANY Value){
        if (!this->Head) return NULL;

        ElementAny<ANY> *node = this->Head;
        while (node && node->value != Value) {
            node = node->next;
        }

        return node;
    };

    virtual ANY getValue(ElementAny<ANY>* node){
        return node->value;
    };
    virtual void setValue(ElementAny<ANY>* node, ANY Value){
        node->value = Value;
    };

    virtual string toString(){
        return AbstractQueue<ElementAny<ANY>>::toString();
    };

    virtual string toString(ElementAny<ANY>* node){
        string text;
//        text += " Value: ";
//        text += to_string(node->value);
        return text;
    };
};

#endif // QUEUEANYVALUE_H
