#ifndef ABSTRACTQUEUE_H
#define ABSTRACTQUEUE_H

#include <iostream>

using namespace std;

template<typename CustomElement>
struct Element {
   CustomElement* next;
};

template<class CustomElement>
class AbstractQueue
{
public:
    AbstractQueue(){};
    virtual ~AbstractQueue(){};

    virtual CustomElement* getHead()
    {
        return this->Head;
    };
    virtual CustomElement* getLastElement()
    {
        if (!this->Head) return NULL;

        CustomElement *Current = this->Head;

        while (Current->next) {
            Current = Current->next;
        }

        return Current;
    };
    virtual CustomElement* getPreElement(CustomElement* El)
    {
        if (!this->Head) return NULL;

        CustomElement *Current = this->Head;
        CustomElement *Preview = NULL;
        while (Current && Current != El) {
            Preview = Current;
            Current = Current->next;
        }

        return Preview;
    };
    virtual CustomElement* getNext(CustomElement* Current)
    {
        return Current->next;
    };

    virtual CustomElement* createElement()
    {
        CustomElement* El = new CustomElement();
        return El;
    };

    virtual void addElement(CustomElement* El, CustomElement* Position)
    {
        if(Position) {
            El->next = Position->next;
            Position->next = El;
        }
        //Вставка в начало
        else {
            El->next = this->Head;
            this->Head = El;
        }
    };

    virtual bool deleteElement(CustomElement* A){
        return this->deleteElement(A,true);
    };
    virtual bool deleteElement(CustomElement* A, bool isClean)
    {
        if (A){
            CustomElement *PreA = this->getPreElement(A);

            if (PreA) PreA->next = A->next;
            else this->Head = A->next;

            if (isClean) {
                delete [] A;
                A = NULL;
            }

            return true;
        }
        else {
            return false;
        }
    };
    virtual bool deleteAll()
    {
        CustomElement* Current = this->getHead();
        while (Current) {
            CustomElement* Tmp = Current->next;
            this->deleteElement(Current);
            Current = Tmp;
        }

        return true;
    };

    virtual void changeElements(CustomElement *A, CustomElement *B)
    {
        if (this->isElementsNeighbour(A,B)){
            this->changeNeighbourElements(A,B);
        }
        else {
            this->changeFarElements(A,B);
        }
    };
    virtual bool isElementsNeighbour(CustomElement *A, CustomElement *B)
    {
        return A->next == B || B->next == A;
    };
    virtual void changeNeighbourElements(CustomElement *A, CustomElement *B) {

        CustomElement *First, *Second, *SecondNext, *Pre;

        if (A->next == B) First = A;
        if (B->next == A) First = B;

        Second = First->next;
        SecondNext = Second->next;
        Pre = this->getPreElement(First);

        if (Pre) Pre->next = Second;
        else this->Head = Second;

        Second->next = First;
        First->next = SecondNext;
    };
    virtual void changeFarElements(CustomElement *A, CustomElement *B)
    {
        // Предыдущие элементы
        CustomElement *PreA = this->getPreElement(A);
        CustomElement *PreB = this->getPreElement(B);

        // Меняем ссылки в самих элементах
        CustomElement* ANext = A->next;
        CustomElement* BNext = B->next;

        A->next = BNext;
        B->next = ANext;


        // Меняем ссылки в педшествующих элементах
        if (PreA) PreA->next = B;
        if (PreB) PreB->next = A;


        //Меняем голову
        bool isHead = false;
        if (A == this->Head && !isHead) {
            this->Head = B;
            isHead = true;
        }
        if (B == this->Head && !isHead) {
            this->Head = A;
            isHead = true;
        }
    };

    // Steps are functions for emulate while circle
    virtual CustomElement* getStep()
    {
        return this->Step;
    };
    virtual void setStep(CustomElement* Elem)
    {
        this->Step = Elem;
    };
    virtual void setStepNext()
    {
        if (this->getStep()) {
            this->setStep(this->getStep()->next);
        }
    };

    virtual string toString()
    {
        string text = "To string output:\n";
        this->setStep(this->getHead());
        while(this->getStep()){
            text += this->toString(this->getStep());
            text += "\n";
            this->setStepNext();
        }

        return text;
    };
    virtual string toString(CustomElement* El)
    {
        string text;
        text += "element";
        return text;
    };

    // Сомнительно
    virtual CustomElement* getMarkedElement()
    {
        CustomElement* Marked = this->Marked;
        return Marked;
    };
    virtual void setMarkedElement(CustomElement* Elem)
    {
            this->Marked = Elem;
    };

protected:
    CustomElement *Head = NULL;
    CustomElement *Marked = NULL;
    CustomElement *Step = NULL;
};

#endif // ABSTRACTQUEUE_H
