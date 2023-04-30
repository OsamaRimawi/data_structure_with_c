
/// Osama Saed Rihami , 1190560 , Section=3

#include <stdio.h>
#include <stdlib.h>

typedef struct node* PtrToNode;
typedef PtrToNode Stack;

void PrintStack(Stack S );
void Save(Stack S );

int IsEmpty( Stack S );
Stack CreateStack();     ///i print the stack functions from the course slides with few changes
void MakeEmpty( Stack S );
void Pop( Stack S );
char *Top ( Stack S );
void Push( char *X, Stack S );



struct node{
char *Element;
PtrToNode Next;
};

int main()
{
    Stack a=NULL;
    a=CreateStack();       /// Stack for the text

    Stack rd=NULL;
    rd=CreateStack();      /// Stack for the redo function

    char str[100];         /// string for line
    char all[100][100];     /// array of  strings for each line
    int x=0;
    char q[]="quit";
    char r[]="redo";
    char u[]="undo";
    char p[]="print";
    char s[]="save";

    gets(str);

    while(strcmp(q,str) !=0 ){

        if(strcmp(p,str) ==0){
            PrintStack(a);
        }

        else if(strcmp(u,str) ==0){
            if(! IsEmpty(a)){
                Push(Top(a),rd);
                Pop(a);
                PrintStack(a);
            }
            else
                printf("Nothing to undo\n");
        }

        else if(strcmp(r,str) ==0){
            if(! IsEmpty(rd)){
                Push(Top(rd),a);
                Pop(rd);
                PrintStack(a);
            }
            else
                printf("Nothing to Redo\n");
        }

        else if(strcmp(s,str) ==0){
            Save(a);
            printf("Saved Successfully\n");
        }
        else{
            strcpy(all[x],str);
            Push(all[x],a);
            x++;
            }
        gets(str);
    }
    Save(a);
    printf("Good Bye!");


    return 0;
}

void PrintStack(Stack S ){   ///to print stack in order i store it in another stack and push back the values while printing them
    Stack t=NULL;
    t=CreateStack();

    if(IsEmpty(S)){
        printf("Nothing to Print\n");
    }
    while(! IsEmpty(S)){
        Push(Top(S),t);
        Pop(S);
    }
    while(! IsEmpty(t)){
        printf("%s\n",Top(t));
        Push(Top(t),S);
        Pop(t);
    }
}

void Save(Stack S ){

    FILE *out;
    out = fopen("output.txt","w");
    Stack t=NULL;
    t=CreateStack();

    if(IsEmpty(S)){
        fprintf(out,"EMPTY\n");
    }
    while(! IsEmpty(S)){
        Push(Top(S),t);
        Pop(S);
    }
    while(! IsEmpty(t)){
        fprintf(out,"%s\n",Top(t));
        Push(Top(t),S);
        Pop(t);

    }
    fclose(out);
}

int IsEmpty( Stack S ){
    return S->Next == NULL;
}

Stack CreateStack( ){
    Stack S;
    S =  ( Stack )malloc( sizeof( struct node ) );
    if( S == NULL )
        printf( "Out of space!\n" );
    S->Next = NULL;
    MakeEmpty( S );
    return S;
}

void MakeEmpty( Stack S ){
    if( S == NULL )
        printf( "Out of space!" );
    else
        while( !IsEmpty( S ))
            Pop( S );
}

void Pop( Stack S ){
    PtrToNode firstCell;
    if( IsEmpty( S ) )
        printf( "Empty stack\n" );
    else{
    firstCell = S->Next;
    S->Next = S->Next->Next;
    free( firstCell );
    }
}

char *Top( Stack S ){
    if( !IsEmpty( S ) )
        return S->Next->Element;
    printf( "Empty stack\n" );
    return 0;
}

void Push( char *X, Stack S ){
    PtrToNode temp;
    temp = ( Stack )malloc( sizeof( struct node ) );
    if( temp == NULL)
        printf( "Out of space!" );
    else{
        temp->Element = X;
        temp->Next = S->Next;
        S->Next = temp;
    }
}

void DisposeStack( Stack S ){
    MakeEmpty( S );
    free( S );
}

