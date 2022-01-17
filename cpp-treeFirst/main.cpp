#include <iostream>

using namespace std;

struct node_t
{
    node_t* Left;
    node_t* Right;
    int value;
    int NumOrder;
};

struct Queue_t
{
   node_t *Value;
   Queue_t *Next;
};

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
void FullArray(int **Array_PRN,const node_t* root,int Left_Border,int Right_Border,int Cur_Height, int flag)
{
   int i;
   int Medium = (Right_Border+Left_Border)/2;
   if (root->Left!= NULL)
   {
      for( i = (Left_Border+Medium)/2 ; i < Medium ; i++ )
      {
         Array_PRN[Cur_Height][i] = -1;
      }
      Array_PRN[Cur_Height][(Left_Border+Medium)/2] = -2;

      FullArray(Array_PRN,root->Left, Left_Border, Medium, Cur_Height+1, flag);
   }
   if (root->Right!= NULL)
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
      Array_PRN[i] = new int[tree_Widht*4];
   }
   for(i = 0; i < tree_Height ;i++)
   {
      for(j = 0; j < tree_Widht*4 ;j++)
      {
         Array_PRN[i][j] = 0;
      }
   }
   FullArray(Array_PRN,root,0,tree_Widht*4,0,flag);
   printf("\n");
   for(i = 0; i < tree_Height ;i++)
   {
      printf("\n");
      for(j = 0; j < tree_Widht*4 ;j++)
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

    node_t n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14,n15;
    n1.Left = &n2; n1.Right = &n9; n1.value = 1;
    n2.Left = &n3; n2.Right = &n6; n2.value = 2;
    n3.Left = &n4; n3.Right = &n5; n3.value = 37;
    n4.Left = NULL; n4.Right = NULL; n4.value = 4;
    n5.Left = NULL; n5.Right = &n15; n5.value = 52;
    n6.Left = &n7; n6.Right = &n8; n6.value = 6;
    n7.Left = NULL; n7.Right = NULL; n7.value = 7;
    n8.Left = NULL; n8.Right = NULL; n8.value = 81;
    n9.Left = &n10; n9.Right = &n13; n9.value = 9;
    n10.Left = &n11; n10.Right = &n12; n10.value = 10;
    n11.Left = &n14; n11.Right = NULL; n11.value = 11;
    n12.Left = NULL; n12.Right = NULL; n12.value = 12;
    n13.Left = NULL; n13.Right = NULL; n13.value = 13;
    n14.Left = NULL; n14.Right = NULL; n14.value = 14;
    n15.Left = NULL; n15.Right = NULL; n15.value = 65;

   PrintTree(&n1,1);
   printf("\n");
   getchar();
   return 0;
}