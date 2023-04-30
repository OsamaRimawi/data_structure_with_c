// Osama Rihami , 1190560, Section :3
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct AVLnode *AVLNode; // AVL NODE define
typedef struct HashNode *HashNode; // HASH node define

struct AVLnode  // AVL NODE Structure
{
    char ptName[40];
    char gdr[2];
    int DOA;
    int DOB;
    char ill[40];
    char adrs[40];
    char BT[5];
    AVLNode Left;
    AVLNode Right;
    int Height; //Balance information
};
struct HashNode // HASH NODE Structure
{
    char ptName[40];
    char gdr[2];
    int DOA;
    int DOB;
    char ill[40];
    char adrs[40];
    char BT[5];
};

//define AVL TREE FUNCTIONS:
// NOTE THAT : MOST of these FUNCTIONS is the functions was gives to us by instructor in slides
AVLNode ReadFile( AVLNode tree ); // Read the patients from input file and store them in AVL Tree
void WriteFile(AVLNode T,FILE *out); // Write the AVL TREE on Output file
AVLNode Delete( AVLNode T,char *Name); // Delete one patient from  AVL Tree
AVLNode Find( char *X, AVLNode T ); // Find one patient from  AVL Tree and modify it
void UserInput( AVLNode tree ); // Insert Patient From user input to AVL Tree
void PrintInOrder( AVLNode t); // Print Tree in lexicographic way
void PrintSameIll(char *X, AVLNode T); // List all patients that have the same illness
AVLNode Insert(char *Name,char *G,int DOA1,int DOB1,char *Ill,char *AD,char *BT1, AVLNode T ); // insert to AVL
int Balance(AVLNode N); // return balance of one node in AVL
int Size(AVLNode tree);  // Return the Size of AVL Tree
// the rest is pretty obvious
AVLNode MakeEmpty( AVLNode T );
AVLNode FindMin( AVLNode T );
AVLNode FindMax( AVLNode T );
int Height( AVLNode P );
int Max( int Lhs, int Rhs );
AVLNode SingleRotateWithLeft( AVLNode K2 );
AVLNode SingleRotateWithRight( AVLNode K1 );
AVLNode DoubleRotateWithLeft( AVLNode K3 );
AVLNode DoubleRotateWithRight( AVLNode K1 );

//define Hash Table FUNCTIONS:
void FillHash(AVLNode T, HashNode H[],int SIZE); // Fill the hash table from the AVL tree data
int Hash1(char* key,int SIZE); // First Hash Function
int Hash2(char* key,int SIZE); // second Hash Function
void PrintHash(HashNode H[],int SIZE); // print the Hash Table
void InsertHash(char *Name,char *G,int DOA1,int DOB1,char *Ill,char *AD,char *BT1, HashNode H[],int SIZE); // Insert new data in Hash Table
HashNode SearchHash(char *Name, HashNode H[],int SIZE); // Search for a specific patient in Hash Table
void DeleteHash(char *Name, HashNode H[],int SIZE); //Delete a specific record in Hash Table
void AddHash(HashNode H[],int SIZE); //Insert a new record From user into the hash table.
void SaveHash(HashNode H[],int SIZE); //Save hash table back to file.
int NextPrime(int n); //return the first Next Prime Integer
int prevPrime(int n); //return the first previous Prime Integer

int main()
{
    AVLNode tree=NULL; // OUR AVL TREE
    tree = MakeEmpty( tree );

    char X[40]; //to read from user
    printf("To Call Any Function Enter The Letter After It\n");
    printf("****AVL Tree Functions****\n");
    printf("Read AVL Tree from File - 'r'\n");
    printf("Print AVL Tree - 'p'\n");
    printf("Insert New in AVL Tree - 'i'\n");
    printf("Delete in AVL Tree - 'd'\n");
    printf("Find in AVL Tree - 'f'\n");
    printf("Print all Patients with Same illness - 'c'\n");
    printf("Save AVL Tree on file and Exit to Hash functions - 's'\n");

    int flag =0; //to exit the while loop
    do
    {
        printf("\nChoose function:\n");
        gets(X);

        if (X[0]=='r')
            tree=ReadFile(tree);
        else if (X[0]=='c')
        {
            printf("Enter the illness:\n");
            gets(X);
            PrintSameIll(X,tree);
        }
        else if (X[0]=='i')
            UserInput(tree);
        else if(X[0]== 'p')
            if (tree == NULL)
                printf("Tree is Empty, Make sure to read from File first\n");
            else
                PrintInOrder(tree);
        else if(X[0]=='d')
        {
            printf("Enter the name of patient to delete:\n");
            gets(X);
            tree=Delete(tree,X);
        }
        else if(X[0]=='f')
        {
            printf("Enter the name of patient to Find:\n");
            gets(X);
            AVLNode t2=Find(X,tree);
            if (t2==NULL)
                printf("Not Found \n");
        }
        else if (X[0] == 's')// it will Not exit the loop Unless i have some data in avl tree
        {
            FILE *out;
            out = fopen("patients_hash.data","w");
            if (out==NULL)
                printf("cannot open file \n");
            else if(tree ==NULL)
                printf("Tree is Empty, Make sure to read from File first\n");
            else
            {
                WriteFile(tree,out);
                fclose(out);
                printf("Output Written into file successfully.\n\n");
                flag=1;
            }
        }
    }while (flag != 1);

    int sz=NextPrime(Size(tree)*2); // Size of Hash
    HashNode H[sz]; // OUR Hash Table
    for (int j=0;j<sz;j++) //Make it Empty
        H[j]=NULL;

    FillHash(tree,H,sz);
    printf("****Hash Table Functions****\n");
    printf("Print Hash Table - 'p'\n");
    printf("Insert new in Hash Table - 'i'\n");
    printf("Delete in Hash Table - 'd'\n");
    printf("Find in Hash Table - 'f'\n");
    printf("Print Table Size - 's'\n");
    printf("Print Function Used - 'x'\n");
    printf("Write Hash Table on file - 'o'\n");
    printf("Exit - 'e' \n");

    do
    {
        printf("\nChoose function:\n");
        gets(X);
        if (X[0]=='i')
            AddHash(H,sz);
        else if(X[0]== 'p')
            PrintHash(H,sz);
        else if(X[0]=='d')
        {
            printf("Enter the name of patient to delete:\n");
            gets(X);
            DeleteHash(X,H,sz);
        }
        else if(X[0]=='f' )
        {
            printf("Enter the name of patient to Find:\n");
            gets(X);
            HashNode s=NULL;
            s=SearchHash(X,H,sz);
            if (s==NULL)
                printf("NOT  FOUND\n");
            else
                printf("Founded\n");
        }
        else if(X[0]=='o' )
            SaveHash(H,sz);
        else if(X[0]=='s' )
            printf("Table Size is: %d\n",sz);
        else if(X[0]=='x' )
            printf("Hash Function used here is : Double Hashing\n");

    }while(X[0]!='e');

    return 0;
}

AVLNode ReadFile( AVLNode tree )
{
    FILE *in;
    in = fopen("patients.txt","r");

    char ln[100] ; //to store one line
    char ar [7][40] ; //to store data of one node
    int n=0; // to define the data

    if (in==NULL)
        printf("cannot open file \n");
    else
    {
        while (fgets(ln, 100, in) != NULL)
        {
            n=0;
            char *cut = strtok(ln, "#"); //Split for every # and store it in Array
            while(cut != NULL)
            {
                strcpy(ar[n],cut);
                n++;
                cut = strtok(NULL, "#");
            }
            tree = Insert(ar[0],ar[1],atoi(ar[2]),atoi(ar[3]),ar[4],ar[5],ar[6], tree);
        }
    }
    fclose(in);
    printf("Read from File Successfully\n");
    return tree;
}

void UserInput( AVLNode tree )
{
    char te[7][40]; //to store data of one node
    printf("New Input Enter:\n");
    printf("Name:\n");
    gets(te[0]);
    printf("Gender:\n");
    gets(te[1]);
    printf("Date of admission:\n");
    gets(te[2]);
    printf("Date of birth:\n");
    gets(te[3]);
    printf("Illness:\n");
    gets(te[4]);
    printf("Address:\n");
    gets(te[5]);
    printf("Blood Type:\n");
    gets(te[6]);
    strcat(te[6],"\n"); // i notice that all data that was read from file end with \n so i add it here in order to be the same
    tree = Insert(te[0],te[1],atoi(te[2]),atoi(te[3]),te[4],te[5],te[6], tree);
    printf("Data Inserted Successfully.\n");
}

AVLNode Find( char *X, AVLNode T )
{
    if( T == NULL ) // if Name is not Found return NULL
        return NULL;
    if( strcmp(X,T->ptName) <0 ) // if Name is smaller move to left
        return Find( X, T->Left );
    else if( strcmp(X,T->ptName) >0 ) // if Name is bigger move to right
        return Find( X, T->Right );
    else
    {
        printf("Founded ,Do you want to update its information (y/n)\n");
        char c;
        gets(&c);
        if ( c == 'y')
        {
            char tp[2][20];
            printf("New Input Enter its:\n");
            printf("Name:\n");
            gets(T->ptName);
            printf("Gender:\n");
            gets(T->gdr);
            printf("Date of admission:\n");
            gets(tp[0]);
            T->DOA=atoi(tp[0]);
            printf("Date of birth:\n");
            gets(tp[1]);
            T->DOB=atoi(tp[1]);
            printf("Illness:\n");
            gets(T->ill);
            printf("Address:\n");
            gets(T->adrs);
            printf("Blood Type:\n");
            gets(T->BT);
            return T;
        }
        else
        {
            printf("OK -_-\n");
            return T; // if No RETURN NODE
        }
    }
}

void PrintInOrder( AVLNode T)           //in-order print to see the elements
{
    if( T != NULL)
    {
        PrintInOrder( T->Left );
        printf("%s - %s - %d - %d - %s - %s - %s",T->ptName,T->gdr ,T->DOA ,T->DOB , T->ill ,T->adrs,T->BT);
        PrintInOrder( T->Right );
    }
}

void PrintSameIll(char *X, AVLNode T){
    if( T != NULL)
    {
        PrintSameIll( X,T->Left );
        if (strcmp(X,T->ill)==0)
            printf("%s - %s - %d - %d - %s - %s - %s",T->ptName,T->gdr ,T->DOA ,T->DOB , T->ill ,T->adrs,T->BT);
        PrintSameIll( X,T->Right );
    }
}

void WriteFile(AVLNode T,FILE *out)
{
    if( T != NULL)
    {
        WriteFile( T->Left,out );
        fprintf(out,"%s - %s - %d - %d - %s - %s - %s",T->ptName,T->gdr ,T->DOA ,T->DOB , T->ill ,T->adrs,T->BT);
        WriteFile( T->Right,out );
    }
}

int Size(AVLNode T)
{
    int n=0; //for every node increase n and return it
    if( T != NULL)
    {
        n=n+Size( T->Left );
        n++;
        n=n+Size( T->Right );
    }
    return n;
}

AVLNode MakeEmpty( AVLNode T )
{
    if( T != NULL )
    {
        MakeEmpty( T->Left );
        MakeEmpty( T->Right );
        free( T );
    }
    return NULL;
}

AVLNode FindMin( AVLNode T )
{
    if( T == NULL )
        return NULL;
    else if( T->Left == NULL )
        return T;
    else
        return FindMin( T->Left );
}

AVLNode FindMax( AVLNode T )
{
    if( T != NULL )
        while( T->Right != NULL )
            T = T->Right;
    return T;
}

int Height( AVLNode T )
{
    if( T == NULL )
        return -1;
    else
        return T->Height;
}

int Balance(AVLNode T)
{
    if (T == NULL)
        return 0;
    return Height(T->Left) - Height(T->Right);
}

int Max( int Lhs, int Rhs )
{
    return Lhs > Rhs ? Lhs : Rhs;
}

AVLNode SingleRotateWithLeft( AVLNode K2 ) // Rotate Tree In left left case
{
    AVLNode  K1;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;
    K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;

    return K1;
}

AVLNode SingleRotateWithRight( AVLNode K1 ) // Rotate Tree In Right Right case
{
    AVLNode K2;

    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;

    K1->Height = Max( Height( K1->Left ), Height( K1->Right ) ) + 1;
    K2->Height = Max( Height( K2->Right ), K1->Height ) + 1;

    return K2;  /* New root */
}

AVLNode DoubleRotateWithLeft( AVLNode K3 )  // Rotate Tree In left-right case
{
    /* Rotate between K1 and K2 */
    K3->Left = SingleRotateWithRight( K3->Left );

    /* Rotate between K3 and K2 */
    return SingleRotateWithLeft( K3 );
}

AVLNode DoubleRotateWithRight( AVLNode K1 ) // Rotate Tree In right-left case
{
    /* Rotate between K3 and K2 */
    K1->Right = SingleRotateWithLeft( K1->Right );

    /* Rotate between K1 and K2 */
    return SingleRotateWithRight( K1 );
}

AVLNode Insert(char *Name,char *G,int DOA1,int DOB1,char *Ill,char *AD,char *BT1, AVLNode T )
{
    if( T == NULL )
    {
        T = malloc( sizeof( struct AVLnode ) ); // create new node
        if( T == NULL )
            printf( "Out of space!!!" );
        else
        {
            strcpy(T->ptName,Name);
            strcpy(T->gdr,G);
            T->DOA =DOA1;
            T->DOB =DOB1;
            strcpy(T->ill,Ill);
            strcpy(T->adrs,AD);
            strcpy(T->BT,BT1);
            T->Height = 0;
            T->Left = T->Right = NULL;
        }
    }
    else if( strcmp(Name,T->ptName) <0) // if Name is smaller keep moving to left
    {
        T->Left = Insert(Name,G,DOA1,DOB1,Ill,AD,BT1, T->Left );
        if( Height( T->Left ) - Height( T->Right ) == 2 ) // if balance is broken
        {
            if(strcmp(Name,T->Left->ptName) <0) //if Name is smaller do left left Rotate
                T = SingleRotateWithLeft( T );
            else
                T = DoubleRotateWithLeft( T ); //if Name is Bigger do left Right Rotate
        }
    }
    // same method if Name was Bigger
    else if( strcmp(Name,T->ptName) >0)
    {
        T->Right = Insert(Name,G,DOA1,DOB1,Ill,AD,BT1,T->Right );
        if( Height( T->Right ) - Height( T->Left ) == 2 )
        {
            if(strcmp(Name,T->Right->ptName) >0 )
                T = SingleRotateWithRight( T );
            else
                T = DoubleRotateWithRight( T );
        }
    }
    // if the Name was in Tree already we will do nothing

    T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1; // update the hight information
    return T;
}

AVLNode Delete(AVLNode T, char *Name)
{
    if (T == NULL) // if Name was not found
    {
        printf("Didn't Find Patient\n"  );
        return T;
    }

    if (strcmp(Name,T->ptName) > 0) //if Name is Bigger keep moving right
        T->Right = Delete(T->Right, Name);

    else if ( strcmp(Name,T->ptName) <0) //if Name is smaller keep moving left
        T->Left = Delete(T->Left, Name);

    else //if we find the Name
    {
        if( (T->Left == NULL) || (T->Right == NULL) ) // if it zero or one child
        {
            AVLNode tp; // temporarily node to store the data to delete
            if (T->Left == NULL)
                tp = T->Right;
            else
                tp = T->Left;

            if (tp == NULL) // case it didn't have any child tp node will equal the node
            {
                tp = T;
                T = NULL;
            }

            else // case it have one child the node will point to the child and tp node will equal the parent node
                *T = *tp;

            free(tp); // free node
            printf("Patient Deleted Successfully\n");
        }

        else // case it have two children the node will copy the smallest child in right data then delete the child
        {
            AVLNode tp = FindMin(T->Right);

            strcpy(T->ptName,tp->ptName);
            strcpy(T->gdr,tp->gdr);
            T->DOA=tp->DOA;
            T->DOB=tp->DOB;
            strcpy(T->ill,tp->ill);
            strcpy(T->adrs,tp->adrs);
            strcpy(T->BT,tp->BT);

            T->Right = Delete(T->Right, tp->ptName);
        }
    }
    if (T == NULL)
      return T;

    T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;

    // after we delete the node we will check the balance
    int bal = Balance(T);

    if (bal > 1 && Balance(T->Left) >= 0) // left left case
        T = SingleRotateWithLeft( T );

    if (bal > 1 && Balance(T->Left) < 0) // left Right case
        T = DoubleRotateWithLeft( T );

    if (bal < -1 && Balance(T->Right) <= 0) // Right Right case
        T = SingleRotateWithRight( T );

    if (bal < -1 && Balance(T->Right) > 0) // Right left case
        T = DoubleRotateWithRight( T );

    T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;

    return T;
}

void FillHash(AVLNode T, HashNode H[],int SIZE)
{
    if( T != NULL) // for every node we insert it in the hash table
    {
        FillHash( T->Left,H ,SIZE);
        InsertHash(T->ptName,T->gdr ,T->DOA ,T->DOB , T->ill ,T->adrs,T->BT,H,SIZE);
        FillHash( T->Right,H,SIZE );
    }
}

int Hash1(char* key,int SIZE)
{
    int hashValue= 0;
    while( *key != '\0' ) // I Have used the second String Hashing Way we Studied
    {
        hashValue= ( hashValue << 2 ) + *key++; // but here i put the number 2 because the string is big and will cause an error for big numbers
    }

    return (hashValue% SIZE);
}

int Hash2(char* key,int SIZE)
{
    int x=prevPrime(SIZE); // The second Hash Function for double Hashing way
    return  (x-(*key %x));
}

HashNode SearchHash(char *Name, HashNode H[],int SIZE)
{
    int key1 = Hash1(Name,SIZE);
    int key2 = Hash2(Name,SIZE);
    int i=0;
    int index =(key1+i*key2)%SIZE;
    while(H[index] != NULL) // for every collision case increase i and change the index
    {
    if(strcmp(Name,H[index]->ptName) == 0)
        return H[index];
    i++;
    index =(key1+i*key2)%SIZE;
    }
   return NULL;
}

void InsertHash(char *Name,char *G,int DOA1,int DOB1,char *Ill,char *AD,char *BT1,HashNode H[],int SIZE)
{
    int flag=0; // first we check if the array is full then we insert
    for(int i=0;i<SIZE;i++)
        if(H[i] == NULL)
            flag=1;
    if (flag==0)
    {
        printf( "Array is FULL\n" );
        return;
    }

    HashNode node = (HashNode) malloc(sizeof(struct HashNode));
    if( node == NULL )
            printf( "Out of space!!!" );
    else
    {
        strcpy(node->ptName,Name);
        strcpy(node->gdr,G);
        node->DOA =DOA1;
        node->DOB =DOB1;
        strcpy(node->ill,Ill);
        strcpy(node->adrs,AD);
        strcpy(node->BT,BT1);
    }

    int key1 = Hash1(Name,SIZE);
    int key2 = Hash2(Name,SIZE);
    int i=0;
    int index =(key1+i*key2)%SIZE;

    while(H[index] != NULL ) //keep searching for the empty spot
    {
        i++;
        index =(key1+i*key2)%SIZE;
    }
    H[index] = node;
}

void DeleteHash(char *Name, HashNode H[],int SIZE)
{
    int key1 = Hash1(Name,SIZE);
    int key2 = Hash2(Name,SIZE);
    int i=0;
    int index =(key1+i*key2)%SIZE;

    while(H[index] != NULL)
    {
        if(strcmp(Name,H[index]->ptName) == 0)
        {
            free(H[index]);
            H[index]=NULL;
            printf("Patient Deleted Successfully\n");
            return;
        }
        i++;
        index =(key1+i*key2)%SIZE;
    }
    printf("Didn't Find Patient\n"  );
}

void PrintHash(HashNode H[],int SIZE)
{
    for(int i = 0; i<SIZE; i++)
    {
        if(H[i] != NULL)
            printf("%s - %s - %d - %d - %s - %s - %s",H[i]->ptName,H[i]->gdr ,H[i]->DOA ,H[i]->DOB , H[i]->ill ,H[i]->adrs,H[i]->BT);
        else
            printf("#\n"); // for Empty values print #
   }
}

void AddHash(HashNode H[],int SIZE)
{
    char te[7][40];
    printf("New Input Enter:\n");
    printf("Name:\n");
    gets(te[0]);
    printf("Gender:\n");
    gets(te[1]);
    printf("Date of admission:\n");
    gets(te[2]);
    printf("Date of birth:\n");
    gets(te[3]);
    printf("Illness:\n");
    gets(te[4]);
    printf("Address:\n");
    gets(te[5]);
    printf("Blood Type:\n");
    gets(te[6]);
    strcat(te[6],"\n");
    InsertHash(te[0],te[1],atoi(te[2]),atoi(te[3]),te[4],te[5],te[6],H,SIZE);
    printf("Data Inserted Successfully.\n");
}

void SaveHash(HashNode H[],int SIZE)
{
    FILE *out;
    out = fopen("patients_hash.data","w");
    if (out==NULL)
        printf("cannot open file \n");
    else
    {
        for(int i = 0; i<SIZE; i++)
        {
        if(H[i] != NULL)
            fprintf(out,"%s - %s - %d - %d - %s - %s - %s",H[i]->ptName,H[i]->gdr ,H[i]->DOA ,H[i]->DOB , H[i]->ill ,H[i]->adrs,H[i]->BT);
        else
            fprintf(out,"#\n");
        }
        fclose(out);
        printf("Output Written into file successfully.\n");
    }
}
int NextPrime(int n)
{
    int flag =0;
    while( flag != 1 )
    {
        flag = 1;
        for(int i=2; i <= n/i; i++)
            if( n%i == 0 )
                flag =0;
        if( flag == 1 )
                break;
        n++;
    }
    return n;
}

int prevPrime(int n)
{
    int flag =0;
    n--;
    while( flag != 1 && n>1)
    {
        flag = 1;
        for(int i=2; i <= n/i; i++)
            if( n%i == 0 )
                flag =0;
        if( flag == 1 )
                break;
        n--;
    }
    return n;
}
