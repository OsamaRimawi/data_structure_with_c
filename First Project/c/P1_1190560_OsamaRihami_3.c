///Osama saed Rihami ,1190560, Section:3

#include <stdio.h>
#include <stdlib.h>


struct node;
int ReadFile(struct node* l[]);                   ///function to read the file and store the values in array of linked lists and return the size
void Add(struct node* l,struct node* p,struct node* ans);   ///function that takes two linked lists and return addition of them in linked list
void subtr(struct node* l,struct node* p,struct node* ans);  ///function that takes two linked lists and return subtraction of them in linked list
void distr(struct node* l,struct node* p,struct node* ans); ///function that takes two linked lists and return the distribution of first term of on all second list in linked list
void multi(struct node* l,struct node* p,struct node* b[]); ///function that takes two linked lists and return multiplication of them in linked list
void subtt(struct node* l,int x);         ///function that takes  linked list and number and print the substitution of num in linked list
void printfile(struct node* l[],int sz,int num);   ///function that takes array of linked lists and its size and number and print all the previous functions on a file
void Print(struct node* l[],int sz);        ///function that takes array of linked lists and its size and print the list

int IsEmpty(struct node* L);
int IsLast(struct node* P, struct node* L);
void Insert(int X,int Y, struct node* L,int j);  ///i made some changes on insert from slides
void PrintList(struct node* L);
void DeleteList(struct node* L);
int size( struct node* L);
struct node* MakeEmpty(struct node* L);

 struct node{    ///linked list structure
  int coff;
  int exp;
  struct node* Next;
  struct node* Prev;
};

int main() {

    char c;                          /// char for operation
    int sz=0;                        /// size for linked list array
    int num=1;                       /// value for substitution
    struct node *l[6];                ///linked list array
    struct node* b[1];               ///linked list array for multiplication

    struct node* ans=NULL;
    ans=MakeEmpty(NULL);

    struct node* ans1=NULL;
    ans1=MakeEmpty(NULL);



    do{
    printf("To Read the file enter 'r' \n");
    printf("To Print the List enter 'p' \n");
    printf("To perform Addition enter 'a'\n");
    printf("To perform Subtraction enter 's'\n");
    printf("To perform Multiplication enter 'm'\n");
    printf("To Print all outputs on File enter 'o'\n");
    printf("To change Substitution Integer enter 'n' (Default is 1) \n");
    printf("To Exit enter e TWICE ('ee') \n");
    printf("Enter your Operation: \n");

    scanf("%c", &c);

    if (c == 'r'){
        sz=ReadFile(l);
    }

    else if (c == 'p'){
            if(sz==0)
                printf("the list is empty\n");
            else
                Print(l,sz);
    }

    else if (c == 'a'){
            if(sz==0)
                printf("the list is empty\n");
            else if(sz==1)
                PrintList(l[0]);
            else{
              Add(l[0],l[1],ans);
              for(int i=2;i<sz;i++){
                ans1=ans;
                ans=MakeEmpty(NULL);

                Add(ans1,l[i],ans);
            }

            PrintList(ans);
            subtt(ans,num);
            ans=MakeEmpty(NULL);

            }
    }

    else if (c == 's'){
            if(sz==0)
            printf("the list is empty\n");
            else if(sz==1)
                PrintList(l[0]);
            else{
              subtr(l[0],l[1],ans);
              for(int i=2;i<sz;i++){
                ans1=ans;
                ans=MakeEmpty(NULL);

                subtr(ans1,l[i],ans);
            }
            PrintList(ans);
            subtt(ans,num);

            ans=MakeEmpty(NULL);

            }
    }
    else if (c == 'm'){
            if(sz==0)
            printf("the list is empty\n");
            else if(sz==1)
                PrintList(l[0]);
            else{
                multi(l[0],l[1],b);
                for(int i=2;i<sz;i++){
                    ans1=b[0];
                    b[0]=MakeEmpty(NULL);
                    multi(ans1,l[i],b);
            }
            PrintList(b[0]);
            subtt(b[0],num);
            b[0]=MakeEmpty(NULL);
            }
        }

    else if (c == 'n'){
        printf("enter the integer: \n");
        scanf("%d", &num);
    }

    else if (c == 'o'){
        if(sz==0)
            printf("the list is empty\n");
        else
            printfile(l,sz,num);
    }

    scanf("%c", &c);

    } while(c != 'e');

    return 0;
}

struct node* MakeEmpty(struct node* L){
    if(L != NULL)
        DeleteList( L );
    L = (struct node*)malloc(sizeof(struct node));

    if(L == NULL)
        printf("Out of memory!\n");

    L->Next = NULL;
    L->Prev = NULL;

    return L;
}

int ReadFile(struct node* l[]){

 int x=0;

 FILE *in;
 in = fopen("equations.txt","r");

 char s[100] ;                   ///to store the line


 if (in==NULL) {
    printf("cannot open file \n");}

 else{

    while (fgets(s, 100, in) != NULL){


     char str[100]="" ;                                ///to store the line without spaces
     char *spa = strtok(s, " ");
	 while(spa != NULL)
	 {
		strcat(str,spa);
        spa = strtok(NULL, " ");

	 }


     char str1[100]="" ;
     char *mins = strtok(str, "-");
	 while(mins != NULL)
	 {
	    strcat(str1,"+-");
		strcat(str1,mins);                  ///to deal with '-' ,i put '+' before it so we can split it
        mins = strtok(NULL, "-");
	 }

	 if (str[0]!='-'){                      ///to remove the  '-' from start if there were not any
        str1[1]='+';
	 }

    int i=0;
    char c[10][20];                          /// array to store every x^ inside


	char *ptr = strtok(str1, " +");

     while(ptr != NULL)
	 {
		strcpy(c[i],ptr);
        i++;
        ptr = strtok(NULL, " +");	          ///split every + and " " and store the string in array
	 }

     l[x]=NULL;                                   ///create header for linked lists
     l[x]=MakeEmpty(NULL);

    for(int j=0;j<i;j++){

        int co=0;    ///coefficient variable
        int ex=0;    ///exponent variable

        char *ptr1;

        if(c[j][0]=='-'){
            if(c[j][1]=='x'){
                co=-1;
                if(c[j][2]!='^')
                    ex=1;                      ///to deal if there '-' in the start and no constant was before and after x
                else{
                    ptr1 = strtok(c[j], "-x^");
                    ex= atoi(ptr1);             ///to deal if there '-' in the start and no constant was before  x
                    if(ptr1 == NULL)
                        ex=0;
                }
            }
            else{
                for(int t=0;t<strlen(c[j]);t++){
                    if (c[j][t] =='x')
                        if (c[j][t+1]!='^')            ///to deal if there '-' in the start and there was constant was before  x
                            ex=1;
                }
                ptr1 = strtok(c[j], "x^");
                co = atoi(ptr1);
                ptr1 = strtok(NULL, "x^");
                if(ex != 1){
                    ex= atoi(ptr1);                ///to deal if there '-' in the start and there is constant was before and after  x
                    if(ptr1 == NULL)
                        ex=0;
                }
            }
        }

        else if (c[j][0]=='x') {

            co=1;
            if(c[j][1]!='^')
                ex=1;                      ///to deal if there was no constant was before and after  x
            else{
                ptr1 = strtok(c[j], "-x^");
                ex= atoi(ptr1);             ///to deal if there was no constant was before  x
                if(ptr1 == NULL)
                        ex=0;
            }
        }

        else{
            for(int t=0;t<strlen(c[j]);t++){
              if (c[j][t] =='x')
                if (c[j][t+1]!='^')
                  ex=1;                               ///to deal if there was no constant was after  x
            }
            ptr1 = strtok(c[j], "x^");
            co = atoi(ptr1);
            ptr1 = strtok(NULL, "x^");
            if(ex != 1){
                ex= atoi(ptr1);                 ///to deal if there was constant before and after  x
                if(ptr1 == NULL)
                        ex=0;
            }
        }

        Insert(co,ex,l[x],j);     ///insert inside the list

        }
    x++;  /// to the Next linked list
        }

    }

 fclose(in);
 return x;
 }


void Print(struct node* l[],int sz){
    struct node* P;
    printf("The List :\n");
    for (int i=0;i<sz;i++){
        P = l[i];
    if( IsEmpty(l[i]))
        printf("Empty list\n");
    else
        do{
            P=P->Next;
            printf(" + %dx^%d", P->coff,P->exp);
        }while( !IsLast(P, l[i]) );

    printf("\n");
    }

}

void Add(struct node* l,struct node* p,struct node* ans){

     struct node* term1=l;
     struct node* term2=p;
     int x=0;     ///coefficient
     int y=0;     ///exponent
     int j=0;     ///for insert


    while(! IsEmpty(term1) && ! IsEmpty(term2)){
        if (term1->Next->exp > term2->Next->exp) {     ///term 1 exponent is bigger
            y= term1->Next->exp;
            x = term1->Next->coff;
            term1 = term1->Next;

        }


        else if (term1->Next->exp < term2->Next->exp) {        ///term 2 exponent is bigger
            y = term2->Next->exp;
            x = term2->Next->coff;
            term2 = term2->Next;

        }

        else if (term1->Next->exp == term2->Next->exp){    ///term 1 exponent = term 2 exponent
            y = term1->Next->exp;
            x = term1->Next->coff + term2->Next->coff;
            term1 = term1->Next;
            term2 = term2->Next;

        }
        if(x ==0 && y ==0){}
        else{
            Insert(x,y,ans,j);
            j++;
        }
    }
    while (!IsEmpty(term1) || !IsEmpty(term2)) {
        if (!IsEmpty(term1)) {         ///list 2 is empty while list 1 is not
            y= term1->Next->exp;
            x = term1->Next->coff;
            term1 = term1->Next;

        }
        if (!IsEmpty(term2)) {         ///list 1 is empty while list 2 is not
            y = term2->Next->exp;
            x = term2->Next->coff;
            term2 = term2->Next;
        }
        if(x ==0 && y ==0){}
        else{
            Insert(x,y,ans,j);
            j++;
        }
    }
}

void subtr(struct node* l,struct node* p,struct node* ans){  ///same as Add function but -1*term 2 coefficients

     struct node* term1=l;
     struct node* term2=p;
     int x=0;     ///coefficient
     int y=0;     ///exponent
     int j=0;     ///for insert


    while(! IsEmpty(term1) && ! IsEmpty(term2)){
        if (term1->Next->exp > term2->Next->exp) {
            y= term1->Next->exp;
            x = term1->Next->coff;
            term1 = term1->Next;

        }


        else if (term1->Next->exp < term2->Next->exp) {
            y = term2->Next->exp;
            x = -1*term2->Next->coff;
            term2 = term2->Next;

        }

        else if (term1->Next->exp == term2->Next->exp){
            y = term1->Next->exp;
            x = term1->Next->coff - term2->Next->coff;
            term1 = term1->Next;
            term2 = term2->Next;

        }
        if(x ==0 && y ==0){}
        else{
            Insert(x,y,ans,j);
            j++;
        }
    }
    while (!IsEmpty(term1) || !IsEmpty(term2)) {
        if (!IsEmpty(term1)) {
            y= term1->Next->exp;
            x = term1->Next->coff;
            term1 = term1->Next;

        }
        if (!IsEmpty(term2)) {
            y = term2->Next->exp;
            x =-1*term2->Next->coff;
            term2 = term2->Next;
        }
        if(x ==0 && y ==0){}
        else{
            Insert(x,y,ans,j);
            j++;
        }
    }
}

void distr(struct node* l,struct node* p,struct node* ans){

     struct node* term1=l;
     struct node* term2=p;
     int x=0;     ///coefficient
     int y=0;     ///exponent
     int j=0;     ///for insert
     if(IsEmpty(term1)){}
     else{
        while( ! IsEmpty(term2)){
            y= term1->Next->exp+term2->Next->exp;        /// term 1 exponent + term 2 exponent
            x = term1->Next->coff*term2->Next->coff;    /// term 1 coefficient * term 2 coefficient
            term2 = term2->Next;

            if(x ==0 && y ==0){}
            else{
                Insert(x,y,ans,j);
                j++;
            }
        }
     }

}

void multi(struct node* l,struct node* p,struct node* b[]){

                              /// i passed an array of linked lists (b[]) because when i use MakeEmpty it change the value of
                              ///   it in main unlike single linked list
     struct node* term1=l;
     struct node* term2=p;

     struct node* te=NULL;       ///temp list to use
     te=MakeEmpty(NULL);


     struct node* a[10];          /// array in each node [j] I store the distribution of each term of list 1 on all list 2

     int j=0;

     a[0]=NULL;
     a[0]=MakeEmpty(NULL);

     b[0]=MakeEmpty(NULL);
     distr(term1,term2,b[0]);
     distr(term1,term2,a[0]);

     while(! IsEmpty(term1)){

        term1=term1->Next;
        j++;
        a[j]=NULL;
        a[j]=MakeEmpty(NULL);
        distr(term1,term2,a[j]);
    }

    if(j>=2){
        b[0]=MakeEmpty(NULL);   ///add the first two terms and save the answer in b[0]
        Add(a[0],a[1],b[0]);
    }

    for(int i=2;i<j;i++){
        te=b[0];
        b[0]=MakeEmpty(NULL);
        Add(te,a[i],b[0]);     ///continue adding terms and save the answer in b[0] till the end of a[]
    }
}


void subtt(struct node* l,int x){
    struct node* p=l;
    double sum=0;
    for(int i=0;i<size(l); i++ ){
        sum=sum+(p->Next->coff*(pow(x,p->Next->exp)));
        p=p->Next;
    }
    printf("The substitution of %d in this equation is : %f\n",x,sum);

}

void printfile(struct node* l[],int sz,int num){

    struct node* b[1];
    struct node *ans=NULL;
    ans=MakeEmpty(NULL);

    struct node* ans1=NULL;
    ans1=MakeEmpty(NULL);

    struct node* P;
    struct node* p;

    FILE *out;
    out = fopen("results.txt","w");

    fprintf(out,"The List :\n");

    for (int i=0;i<sz;i++){
        P = l[i];
    if( IsEmpty(l[i]))
        fprintf(out,"Empty list\n");
    else
        do{
            P=P->Next;
            fprintf(out," + %dx^%d", P->coff,P->exp);
        }while( !IsLast(P, l[i]) );

    fprintf(out,"\n");
    }

    fprintf(out,"\n The Addition :\n");

    if(sz==0)
        fprintf(out,"The list is empty\n");
    else if(sz==1)
        ans=l[0];
    else{
        Add(l[0],l[1],ans);
        for(int i=2;i<sz;i++){
            ans1=ans;
            ans=NULL;
            ans=MakeEmpty(NULL);
            Add(ans1,l[i],ans);
        }
    }

    P = ans;
    do{
        P=P->Next;
        fprintf(out," + %dx^%d", P->coff,P->exp);
    }while( !IsLast(P, ans) );

    fprintf(out,"\n");

    p=ans;
    double sum=0;
    for(int i=0;i<size(ans); i++ ){
        sum=sum+(p->Next->coff*(pow(num,p->Next->exp)));
        p=p->Next;
    }
    fprintf(out,"The substitution of %d in this equation is %f\n",num,sum);

    ans=NULL;
    ans=MakeEmpty(NULL);

    fprintf(out,"\nThe subtraction :\n");

    if(sz==0)
        fprintf(out,"The list is empty\n");
    else if(sz==1)
        ans=l[0];
    else{
        subtr(l[0],l[1],ans);
        for(int i=2;i<sz;i++){
            ans1=ans;
            ans=NULL;
            ans=MakeEmpty(NULL);
            subtr(ans1,l[i],ans);
        }
    }

    P = ans;
    do{
        P=P->Next;
        fprintf(out," + %dx^%d", P->coff,P->exp);
    }while( !IsLast(P, ans) );
    fprintf(out,"\n");

    p=ans;
    sum=0;
    for(int i=0;i<size(ans); i++ ){
        sum=sum+(p->Next->coff*(pow(num,p->Next->exp)));
        p=p->Next;
    }
    fprintf(out,"The substitution of %d in this equation is %f\n",num,sum);

    ans=NULL;
    ans=MakeEmpty(NULL);

    fprintf(out,"\n The multiplication :\n");

    if(sz==0)
    fprintf(out,"the list is empty\n");
    else if(sz==1)
            b[0]=l[0];
    else{
            multi(l[0],l[1],b);
            for(int i=2;i<sz;i++){
                ans1=b[0];
                b[0]=MakeEmpty(NULL);
                multi(ans1,l[i],b);
            }
            }
    P = b[0];
    do{
        P=P->Next;
        fprintf(out," + %dx^%d", P->coff,P->exp);
    }while( !IsLast(P, b[0]) );
    fprintf(out,"\n");

     p=b[0];
     sum=0;
    for(int i=0;i<size(b[0]); i++ ){
        sum=sum+(p->Next->coff*(pow(num,p->Next->exp)));
        p=p->Next;
    }
    fprintf(out,"The substitution of %d in this equation is %f\n",num,sum);

    ans=NULL;
    ans=MakeEmpty(NULL);
    b[0]=NULL;
    b[0]=MakeEmpty(NULL);

    fclose(out);
}

int IsEmpty(struct node* L){
return L->Next == NULL;
}

int IsLast(struct node* P, struct node* L){
 return (P->Next== NULL);
}

void Insert(int X,int Y, struct node* L,int j){

struct node *temp;
struct node* p=L;
temp = (struct node*)malloc(sizeof(struct node));
temp->Next=NULL;

for (int i=0;i<j;i++){
    if(p->Next != NULL)
    p=p->Next;
}

temp->coff = X;
temp->exp = Y;
temp->Next = p->Next;
p->Next = temp;
temp->Prev = p;

}

void PrintList(struct node* L){
struct node* P = L;
if( IsEmpty(L))
printf("Empty list\n");
else
do{
P=P->Next;
printf(" + %dx^%d", P->coff,P->exp);
}while( !IsLast(P, L) );

printf("\n");
}

int size( struct node* L){
struct node* p = L->Next;
int count = 0;
while(p != NULL ){
count += 1;
p = p->Next;
}
return count;
}

void DeleteList(struct node* L){
struct node* P;
struct node* temp;
P = L->Next;
L->Next = NULL;
while(P != NULL){
temp = P->Next;
free(P);
P=temp;
}
}
