#include "QueueIntValue.h"


ElementIntValue* QueueIntValue::createElement(int Value)
{
    ElementIntValue *Elem = AbstractQueue<ElementIntValue>::createElement();
    this->setValue(Elem, Value);
    return Elem;
}

ElementIntValue* QueueIntValue::findElement(int Value)
{
    if (!this->Head) return NULL;

    ElementIntValue *Current = this->Head;
    while (Current && Current->value != Value) {
        Current = Current->next;
    }

    return Current;
}

int QueueIntValue::getValue(ElementIntValue* El)
{
    return El->value;
}

void QueueIntValue::setValue(ElementIntValue* El, int Value)
{
    El->value = Value;
}

string QueueIntValue::toString()
{
    return AbstractQueue<ElementIntValue>::toString();
}

string QueueIntValue::toString(ElementIntValue *El)
{
    string text;
    text += " Value: ";
    text += to_string(El->value);
    return text;
}

void QueueIntValue::sampleData(int* inputData)
{
    int i = 0;
    while (inputData[i] != '\0') {
        this->addElement(
                    this->createElement(inputData[i]),
                    this->getLastElement()
                    );
        i++;
    }
}
