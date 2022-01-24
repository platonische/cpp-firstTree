#include <iostream>
#include "src/exted/Any/QueueAnyValue.h"


using namespace std;




struct node_t
{
    node_t* Left;
    node_t* Right;
    int value;
    int NumOrder;
    int level;
};

struct Queue_t
{
   node_t *Value;
   Queue_t *Next;
};

// Оцередь очередей
struct Qoq
{
   Queue_t *Value;
   Qoq *Next;
};



int recursion1(node_t*);
int recursion2(node_t*);
int recursion3(node_t*);
bool recursion4(node_t*, bool);
int recursion5(node_t*);
int recursion6(node_t*, int);
int recursion7(Queue_t*);
int recursion8(node_t*, int, int);
Queue_t* recursion9(node_t*, Queue_t*, int);
int recursion10(node_t*, QueueAnyValue<node_t*>*, QueueAnyValue<QueueAnyValue<node_t*>*>*);
node_t* recursion11(node_t*, node_t*);
bool isOdd(int);
bool isLeaf(node_t*);
Queue_t* updateQueueForGettingLowLeaves(Queue_t*, node_t*);
void printQueue(Queue_t*);
void printQoq(QueueAnyValue<QueueAnyValue<node_t*>*>*);
node_t* setSwapNodes(node_t*, node_t*, node_t*);
QueueAnyValue<node_t*>* setPath(node_t*, QueueAnyValue<node_t*>*, QueueAnyValue<QueueAnyValue<node_t*>*>*);
Queue_t* addToQoq(Qoq*, Queue_t*);
Queue_t* addToQueue(Queue_t*, node_t*);

//----------------------------------------------------
// Нахождение ширины дерева
int Get_Widht(node_t* root)
{
   int Left_Height = 0;
   int Right_Height = 0;

   if (root->Left!= NULL)
   {
      Left_Height = Get_Widht(root->Left);
   }
   if (root->Right!= NULL)
   {
      Right_Height = Get_Widht(root->Right);
   }
   return (Left_Height + Right_Height)  + 1;
}


//------------------------------------------------------
// Нахождение высоты дерева
int Get_Height(node_t* root)
{
   int Left_Height = 0;
   int Right_Height = 0;

   if (root->Left!= NULL)
   {
      Left_Height = Get_Height(root->Left);
   }
   if (root->Right!= NULL)
   {
      Right_Height = Get_Height(root->Right);
   }
   if (Left_Height > Right_Height)
   {
      return Left_Height+1;
   }
   return Right_Height+1;
}

//----------------------------------------------------
// Заполнение матрицы для форматированного вывода дерева
// int **Array_PRN        - заполняемый массив
// const node_t* root     - корень текущего поддерева
// int Left_Border        - левая граница текущего поддерева
// int Right_Border       - правая граница текущего поддерева
// int Cur_Height         - текущая высота (относительно корня
//                          дерева на которой мы находимся)
// int flag               - что мы выводим на экран
//                        flag = 1  - значения вершин
//                        flag = 2  - номер вершины в пути с четными вершинами

//-------------------------------------------------------
void FullArray(
        int **Array_PRN,
        const node_t* root,
        int Left_Border,
        int Right_Border,
        int Cur_Height,
        int flag
) {
   int i;
   int Medium = (Right_Border+Left_Border)/2;
   if (root->Left != NULL)
   {
      for( i = (Left_Border+Medium)/2 ; i < Medium ; i++ )
      {
         Array_PRN[Cur_Height][i] = -1;
      }
      Array_PRN[Cur_Height][(Left_Border+Medium)/2] = -2;

      FullArray(Array_PRN,root->Left, Left_Border, Medium, Cur_Height+1, flag);
   }
   if (root->Right != NULL)
   {
      for( i = Medium ; i < (Right_Border+Medium)/2 ; i++ )
      {
         Array_PRN[Cur_Height][i] = -1;
      }
      Array_PRN[Cur_Height][(Right_Border+Medium)/2] = -3;
      FullArray(Array_PRN,root->Right,Medium,Right_Border,Cur_Height+1,flag);
   }
   if (flag == 2)
   {
      Array_PRN[Cur_Height][(Right_Border+Left_Border)/2] = root->NumOrder;
   }
   else
   {
      Array_PRN[Cur_Height][(Right_Border+Left_Border)/2] = root->value;
   }
   return;
}

// Распечатка дерева
void PrintTree(node_t* root, int flag)
{
   int tree_Widht;
   int tree_Height;
   int **Array_PRN;
   int i,j;
   tree_Height = Get_Height(root);       // получение высоты дерева
   tree_Widht = Get_Widht(root);         // получение ширины дерева
   printf("\n");
   printf("tree_Height = %d\n",  tree_Height);
   printf("tree_Widht = %d\n",  tree_Widht);
   Array_PRN = new int*[tree_Height];

   for( i = 0; i < tree_Height ;i++ )
   {
      Array_PRN[i] = new int[tree_Widht*6];
   }
   for(i = 0; i < tree_Height ;i++)
   {
      for(j = 0; j < tree_Widht*6 ;j++)
      {
         Array_PRN[i][j] = 0;
      }
   }
   FullArray(Array_PRN,root,0,tree_Widht*6,0,flag);
   printf("\n");
   for(i = 0; i < tree_Height ;i++)
   {
      printf("\n");
      for(j = 0; j < tree_Widht*6 ;j++)
      {
         if (Array_PRN[i][j] > 0)
         {
               printf("%d",Array_PRN[i][j]);
         }
         else if (Array_PRN[i][j]  == -1)
         {
            printf("-");
         }
         else if (Array_PRN[i][j]  == -2)
         {
            printf("/");
         }
         else if (Array_PRN[i][j]  == -3)
         {
            printf("\\");
         }
         else printf(" ");
      }
   }
   printf("\n");
   for(i = 0; i < tree_Height ;i++ )
   {
      delete[] Array_PRN[i];
   }
   delete[] Array_PRN;
}

//----------------------------------------------------
int main()
{
//   setlocale(LC_ALL, "Russian");
   int Height;
   int HeightL;
   int LMax;

    node_t n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14,n15, n16,n17,n18,n19, n20;
    n1.Left = &n2; n1.Right = &n9; n1.value = 4;
    n2.Left = &n3; n2.Right = &n6; n2.value = 2;
    n3.Left = &n4; n3.Right = &n5; n3.value = 37;
    n4.Left = NULL; n4.Right = NULL; n4.value = 4;
    n5.Left = NULL; n5.Right = &n15; n5.value = 52;
    n6.Left = &n7; n6.Right = &n8; n6.value = 61;
    n7.Left = &n16; n7.Right = NULL; n7.value = 72;
    n8.Left = NULL; n8.Right = NULL; n8.value = 81;
    n9.Left = &n10; n9.Right = &n13; n9.value = 9;
    n10.Left = &n11; n10.Right = &n12; n10.value = 10;
    n11.Left = &n14; n11.Right = NULL; n11.value = 11;
    n12.Left = NULL; n12.Right = NULL; n12.value = 12;
    n13.Left = NULL; n13.Right = NULL; n13.value = 13;
    n14.Left = NULL; n14.Right = NULL; n14.value = 14;
    n15.Left = NULL; n15.Right = NULL; n15.value = 15;

    n16.Left = NULL; n16.Right = &n17; n16.value = 12;
    n17.Left = NULL; n17.Right = NULL; n17.value = 32;
//    n17.Left = &n18; n17.Right = &n19; n17.value = 32;
//    n18.Left = NULL; n18.Right = NULL; n18.value = 34;
//    n19.Left = &n20; n19.Right = NULL; n19.value = 36;
//    n20.Left = NULL; n20.Right = NULL; n20.value = 35;


   PrintTree(&n1,1);
   printf("\n");
   //getchar();

//   recursion1(&n1);
//   recursion2(&n1);
//   recursion3(&n1);
   cout << endl;

   //   recursion4(&n1,true);
   //recursion5(&n1);
   //recursion6(&n1, Get_Height(&n1));

//   Queue_t* queue = new Queue_t;
//   queue->Value = &n1;
//   queue->Next = NULL;
//   recursion7(queue);

   //recursion8(&n1,1, Get_Height(&n1));

//   Queue_t* queue = new Queue_t;
//   queue->Value = &n1;
//   printQueue( recursion9(&n1, queue, 1) );

   //recursion11(NULL, &n1);
   //PrintTree(recursion11(NULL, &n1),1);
//   printf("\n");




   QueueAnyValue<QueueAnyValue<node_t*>*>* qoq = new QueueAnyValue<QueueAnyValue<node_t*>*>();

   //Qoq* qoq = new Qoq();
   recursion10(&n1, NULL, qoq);
   printQoq(qoq);


   cout << endl;

   return 0;
}

//Прямой обход
int recursion1(node_t* root)
{
    cout << root->value << ", ";
    if (root->Left) recursion1(root->Left);
    if (root->Right) recursion1(root->Right);
    return 0;
}

//Обратный обход
int recursion2(node_t* root)
{
    if (root->Left) recursion2(root->Left);
    if (root->Right) recursion2(root->Right);
    cout << root->value << ", ";

    return 0;
}

//Симметричный обход
int recursion3(node_t* root)
{
    if (root->Left) recursion3(root->Left);
    cout << root->value << ", ";
    if (root->Right) recursion3(root->Right);
    return 0;
}

//Прямой обход вершины через одну
bool recursion4(node_t* root, bool flag)
{
    if (flag) {
        cout << root->value << ", ";
    }
    flag = !flag;

    if (root->Left) flag = recursion4(root->Left, flag);
    if (root->Right) flag = recursion4(root->Right, flag);

    return flag;
}

//Прямой обход нечетных вершины
int recursion5(node_t* root)
{
    if (isOdd(root->value)) {
        cout << root->value << ", ";
    }
    if (root->Left) recursion5(root->Left);
    if (root->Right) recursion5(root->Right);
    return 0;
}

//Прямой обход четные уровни
int recursion6(node_t* root, int height)
{
    if (!isOdd(height)) {
        cout << root->value << ", ";
    }
    height -= 1;
    if (root->Left) recursion6(root->Left, height);
    if (root->Right) recursion6(root->Right, height);
    return 0;
}

//Обход в ширину
int recursion7(Queue_t* queueIn)
{
    if (queueIn != NULL) {
        cout << "\nNew level: ";
    }

    Queue_t* Current = NULL;
    Queue_t* Head = NULL;
    while (queueIn != NULL){

        cout << queueIn->Value->value << ", ";

        if (queueIn->Value->Left) {
            if (Current==NULL) {
                Current = new Queue_t;
                Head = Current;
            }
            else {
                Current->Next = new Queue_t;
                Current = Current->Next;
            }
            Current->Value = queueIn->Value->Left;
        }

        if (queueIn->Value->Right) {
            if (Current==NULL) {
                Current = new Queue_t;
                Head = Current;
            }
            else {
                Current->Next = new Queue_t;
                Current = Current->Next;
            }
            Current->Value = queueIn->Value->Right;
        }

        queueIn = queueIn->Next;

    }
    if (Head != NULL) recursion7(Head);


    return 0;
}

//Самые нижние листья
int recursion8(node_t* root, int level, int height)
{
    if (level == height) {
        cout << root->value << ", ";
    }
    level++;

    if (root->Left) recursion8(root->Left, level, height);
    if (root->Right) recursion8(root->Right, level, height);
    return 0;
}

//Самые верхние листья
Queue_t* recursion9(node_t* root, Queue_t* queue, int level)
{

    if (isLeaf(root)) {
        root->level = level;
        queue = updateQueueForGettingLowLeaves(queue, root);
    }

    level++;
    if (root->Left) queue = recursion9(root->Left, queue, level);
    if (root->Right) queue = recursion9(root->Right, queue, level);



    return queue;
}

//Самые длинные пути с четными вершинами
int recursion10(
        node_t* node,
        QueueAnyValue<node_t*>* queue,
        QueueAnyValue<QueueAnyValue<node_t*>*>* qoq
        )
{
    if (!isOdd(node->value)){
        queue = setPath(node, queue, qoq);
        //node надо поставить вперед в queue, это будет новая голова
        //и записать ее в qoq как новую очередь
        //Для каждого поапания будет создана своя очередь.
        //следующий элемент это попадание в обратном порядке
    } else {
        queue = NULL;
    }

    // queue здесь уже соответсвует текущей node


    if (node->Left) recursion10(node->Left, queue, qoq);
    if (node->Right) recursion10(node->Right, queue, qoq);

    return 0;
}

QueueAnyValue<node_t*>* setPath(node_t* node,
                 QueueAnyValue<node_t*>* queue,
                 QueueAnyValue<QueueAnyValue<node_t*>*>* qoq)
{
    if(queue == NULL) {
        queue = new QueueAnyValue<node_t*>();
    }

    // Добавили ноду в первую позицию
    // хоть в пустую очередь, хоть в полную
    queue->addElement(queue->createElement(node), NULL);

    // Добавили очередь в очередь очередей
    // Причем каждое попадание это новая итерация
    // Таким образом длинный отрезок из попаданий 2-4-14
    // Будет храниться как 3 отдельных очереди 14, 4-14, 2-4-14
    qoq->addElement(qoq->createElement(queue), NULL);
    return queue;
}

//Queue_t* addToQoq(Qoq* qoq, Queue_t* queue)
//{
//    while(qoq->Next) {
//        qoq = qoq->Next;
//    }

//    qoq->Next = new Qoq();
//    qoq = qoq->Next;
//    if (queue == NULL) {
//        queue = new Queue_t();
//    }
//    qoq->Value = queue;

//    return queue;
//}

//Queue_t* addToQueue(Queue_t* queue, node_t* node)
//{
//    Queue_t* newHead = new Queue_t();
//    newHead->Value = node;

//    if (queue) {
//        newHead->Next = queue;
//    }

//    return newHead;
//}


//Поменять нечетного родителя с четным ребенком
node_t* recursion11(node_t* nodeParent, node_t* node)
{
    if (isOdd(node->value)){

        if (node->Left && !isOdd(node->Left->value))
            node = setSwapNodes(nodeParent, node, node->Left);

        if (node->Right && !isOdd(node->Right->value))
            node = setSwapNodes(nodeParent, node, node->Right);

    }

    if (node->Left) recursion11(node, node->Left);
    if (node->Right) recursion11(node, node->Right);

    return node;
}

bool isOdd(int value)
{
    return bool(value%2);
}

bool isLeaf(node_t* node)
{
    return !(node->Left || node->Right);
}

Queue_t* updateQueueForGettingLowLeaves(Queue_t* queue, node_t* node)
{
    if (queue->Value->level == node->level) {
        //Добавить в конец
        Queue_t *current = queue;
        while (current->Next) {
            current = current->Next;
        }
        current->Next = new Queue_t();
        current = current->Next;
        current->Value = node;

    }

    if (!queue->Value->level || queue->Value->level > node->level) {
        // Заменяем очередь на новую
        queue = new Queue_t;
        queue->Value = node;
    }

    return queue;
}

void printQueue(Queue_t* queue)
{
    while(queue) {
        cout << queue->Value->value << ", ";
        queue = queue->Next;
    }
    cout << endl;
}

void printQoq(QueueAnyValue<QueueAnyValue<node_t*>*>* qoq)
{
    cout << "Печать длинных четных отрезков"<<"\n";

    qoq->setStep(qoq->getHead());
    while (qoq->getStep()){
        QueueAnyValue<node_t*>* curQ = qoq->getValue(qoq->getStep());

        curQ->setStep(curQ->getHead());
        while (curQ->getStep()){
            node_t* curN = curQ->getValue(curQ->getStep());
            cout << curN->value << "-";
            curQ->setStepNext();
        }
        cout << "\n";

        qoq->setStepNext();
    }
}

node_t* setSwapNodes(node_t* nodeGarndParent, node_t* nodeParent, node_t* nodeChild)
{
    if (nodeGarndParent && nodeGarndParent->Left == nodeParent) nodeGarndParent->Left = nodeChild;
    if (nodeGarndParent && nodeGarndParent->Right == nodeParent) nodeGarndParent->Right = nodeChild;

    node_t *tmpL = nodeParent->Left;
    node_t *tmpR = nodeParent->Right;

    nodeParent->Left = nodeChild->Left;
    nodeParent->Right = nodeChild->Right;

    if (tmpL == nodeChild) {
        nodeChild->Left = nodeParent;
    }
    else {
        nodeChild->Left = tmpL;
    }

    if (tmpR == nodeChild) {
        nodeChild->Right = nodeParent;
    }
    else {
        nodeChild->Right = tmpR;
    }

    return nodeChild;
}



