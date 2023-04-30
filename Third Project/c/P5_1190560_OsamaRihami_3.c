#include <stdio.h>
#include <stdlib.h>

#define NODES 300 //Number of all nodes
#define INFINTY 99999999


typedef struct Node *Node; // define Graph NODE
typedef struct Graph *Graph; // define Graph
typedef struct QueueNode *QueueNode; // define Queue NODE
typedef struct Queue *Queue; //define Queue

// Graph NODE
struct Node
{
    int ID;     // City ID
    int weight; //Distance (Cost)
    char Name[20] ; // Road Name
    int visited ;   // will be used for Queue Insert
    struct Node* Next;
};

// Graph (Array of Node Headers)
struct Graph
{
    Node head[NODES];
};

// Queue Node
struct QueueNode
{
    int src;
    int dest;
    int weight;
};

// Queue (using MinHeap Structure)
struct Queue
{
    int size;     // number of Nodes in Queue
    struct QueueNode *head[NODES];    // Array of Queue Node Headrs
};

Graph NewGraph(Graph graph) // method to Create Graph and initialize the Headers
{
    graph = (Graph)malloc(sizeof(struct Graph));
    if(graph == NULL)
        printf("Out of memory!\n");

    for (int i = 0; i < NODES; i++)
    {
        graph->head[i] = NULL;
    }
    return graph;
}

Graph addEdge(Graph graph, int src, int dest, char * Name,int weight) // Add Edge to Graph
{
    Node newNode = (Node)malloc(sizeof(struct Node)); //create New node (edge from source to destination)
    newNode->ID = dest;
    newNode->weight = weight;
    strcpy(newNode->Name, Name);
    newNode->visited=0;

    newNode->Next = graph->head[src];
    graph->head[src] = newNode; // add new node as head source and it will point to the previous Node

    //since Roads are two-ways we create edge from destination to source
    newNode = (Node)malloc(sizeof(struct Node));
    newNode->ID = src;
    newNode->weight = weight;
    strcpy(newNode->Name, Name);
    newNode->visited=0;
    newNode->Next = graph->head[dest];
    graph->head[dest] = newNode;

    return graph;
}

// Queue Functions
QueueNode newQueueNode(int src,int dest,int weight) //Create a Queue Node and return Pointer
{
    QueueNode queueNode =(QueueNode)malloc(sizeof(struct QueueNode));
    queueNode->src = src;
    queueNode->dest = dest;
    queueNode->weight = weight;
    return queueNode;
}

Queue createQueue()// Create Queue and initialize the Headers
{
    Queue queue =(Queue)malloc(sizeof(struct Queue));
    if(queue == NULL)
        printf("Out of memory!\n");
    queue->size = 0;
    for (int i = 0; i < NODES; i++)
    {
        queue->head[i] = NULL;
    }
    return queue;
}

void swapQueueNode(QueueNode *a,QueueNode *b) // Swap 2 Queue Nodes
{
    QueueNode temp = *a;
    *a = *b;
    *b = temp;
}

void rearrange(Queue queue,int index) // Rearrange the Queue as Min Heap at specific index aka (heapify) smaller at the top
{
    if (queue->size > 1)
    {
        int smallest, left, right;
        smallest = index;    // smallest at first will equal the index
        left = 2 * index + 1;   //left Child of Index
        right = 2 * index + 2;  //Right Child of Index

        if (left < queue->size && queue->head[left]->weight < queue->head[smallest]->weight )
            smallest = left;

        if (right < queue->size &&queue->head[right]->weight < queue->head[smallest]->weight )
            smallest = right;

        if (smallest != index) //if one of its children is smaller we swap them and rearrange again until we reach the end
        {
            swapQueueNode(&queue->head[smallest],&queue->head[index]);
            rearrange(queue, smallest);
        }
    }
}

int isEmpty(Queue queue)
{
    return queue->size == 0;
}

QueueNode extractMin(Queue queue) // Remove the Top and return it
{
    if (isEmpty(queue))
        return NULL;

    QueueNode root =queue->head[0];

    QueueNode lastNode = queue->head[queue->size - 1];
    queue->head[0] = lastNode;  // replace root node with the last node

    queue->size--;    // reduce heap size so last node will be removed
    rearrange(queue, 0); //rearrange again from the top

    return root;
}

QueueNode insert(Queue queue, int src,int dest,int weight) // insert New Node in queue and rearrange it
{
    if (queue->size == 0) // if Queue was empty ,insert as Root
    {
        queue->head[0] = newQueueNode(src,dest,weight);
        queue->size += 1;
    }
    else
    {
        queue->head[queue->size] = newQueueNode(src,dest,weight);
        queue->size += 1; // create New Queue Node and insert it as Last Node , increase the size

        for (int i = queue->size / 2 - 1; i >= 0; i--) // Rearrange Form the parent of the Node and go up-words toward Root
            rearrange(queue,i);
    }
}

Graph makeVisited(Graph graph,int src, int dest) // We take the source and destination and make the edge as visited
{
    struct Node *ptr = graph->head[src];
    while (ptr != NULL)
    {
        if(ptr->ID == dest)
        {
            ptr->visited=1;

        }
        ptr = ptr->Next;
    }
    struct Node* ptr1=graph->head[dest]; // Also We do the same thing from destination to source
    while (ptr1 != NULL)
    {
        if(ptr1->ID == src)
            ptr1->visited=1;
        ptr1=ptr1->Next;
    }
    return graph;
}

Graph makeUnVisited(Graph graph) // Method to return all Nodes (Edges) as Not visited (we use it after we done from dijkstra)
{
    for (int i = 0; i < NODES; i++)
    {
        struct Node* ptr = graph->head[i];
        while (ptr != NULL)
        {
            ptr->visited = 0;
            ptr = ptr->Next;
        }
    }
    return graph;
}

void dijkstra(Graph graph, int src,int distn[], int prev[] ) //Dijkstra Algorithm that return arrays of distance and  previous node for a specific Node
{
    Queue queue = createQueue();

    for (int i = 0; i < NODES; i++)    // initialize distn array as infinity and prev array
    {
        distn[i] = INFINTY;
        prev[i]=0;
    }

    distn[src] = 0;    // distn value of source is 0

    struct Node* ptr = graph->head[src];
    while (ptr != NULL)
    {
        insert(queue,src,ptr->ID,ptr->weight); //insert all source Node Edges to the Queue Array And mark Them as Visited
        graph=makeVisited(graph,src,ptr->ID);
        ptr = ptr->Next;
    }

    while (!isEmpty(queue)) // while Queue Array is Not Empty
    {
        QueueNode queueNode = extractMin(queue);  // extract the Minimum Cost Edge

        if(distn[queueNode->dest] > queueNode->weight) // if destination Node is not known yet or it cost is Bigger update it
        {
            distn[queueNode->dest]=queueNode->weight+distn[queueNode->src]; // make the distn value equal edge cost with the cost of previous node
            prev[queueNode->dest]= queueNode->src; // make the prev value equal source (the previous node)
        }


        struct Node *ptr = graph->head[queueNode->dest]; //add the New Edges of destination Node to the Queue
        while (ptr != NULL)
        {
            if(ptr->visited == 0) //only if they were not visited before
            {
                insert(queue,queueNode->dest,ptr->ID, ptr->weight);
                graph = makeVisited(graph,queueNode->dest,ptr->ID);
            }
            ptr=ptr->Next;
        }

    }

}

void writeFile (Graph graph,int src,int dest,char *Name,int distn[],int pre[]) //method to write on File
{
    if(src == -1 && dest == -1) // if Nothing was added from Main
        printf("Nothing to print on File\n");
    else
    {

        FILE *out;
        out = fopen("route.txt","w");

        if (out==NULL)
            printf("can not find the file \n");
        else
        {

            if (distn[dest]==INFINTY)
                fprintf(out,"These Cities Are Not Connected\n");
            else if(src == dest)
                fprintf(out,"Same City -_- \n");
            else
                fprintf(out,"Distance between %d and %d is %d KM through %s and the Previous last city is %d \n",src,dest,distn[dest],Name,pre[dest]);

        }
        printf("Last Output written to File Successfully\n ");
        fclose(out);
    }
}

Graph ReadFile(Graph graph) // Read the Graph From the File and return it
{
    FILE *in;
    in = fopen("segments.txt","r");

    char ln[100] ; //to store one line
    char ar [4][40] ; //to store 4 types of data for each line
    int n=0; // to define the data type

    if (in==NULL)
        printf("cannot open file \n");
    else
    {
        while (fgets(ln, 100, in) != NULL)
        {
            n=0;
            char *cut = strtok(ln, " "); //Split for every " " and store it in Array
            while(cut != NULL)
            {
                strcpy(ar[n],cut); //save it to array value
                while (n>2 && !isdigit(cut[0])) //if Road name had spaces keep adding it to same array value until we read an integer
                {
                    strcat(ar[2]," ");
                    strcat(ar[2],cut);
                    cut = strtok(NULL, " ");
                    if (isdigit(cut[0]))
                        strcpy(ar[n],cut); //if you read an integer add it to new node
                }
                n++;
                cut = strtok(NULL, " ");
            }
            graph=addEdge(graph,atoi(ar[0]),atoi(ar[1]),ar[2],atoi(ar[3])); //add edge to Graph
        }
        printf("  Read File Successfully\n");

    }
    fclose(in);
    return graph;
}

int main ()
{
    Graph graph = NewGraph(graph); //Main Graph
    int distn [NODES];  //array to save all Distances for one Node
    int pre [NODES];    //array to save the Previous nodes
    int src=-1; //to save the Source City number
    int dest=-1; //to save the destination City number
    char Name[20]; //to save Road Name

    int flag=0; // to check if we read from file
    char X[40]; //to read from user
    printf("===========\n");
    printf("************Graph Program************\n");
    printf("===========\n");

    do
    {
        printf("Please enter the City Source Number: (0-300)('e' to exit , 'r' to read from file)\n");
        gets(X);
        if(X[0]=='r')
        {
            graph=ReadFile(graph);
            flag =1;
        }

        else if(isdigit(X[0]) && atoi(X)<300) // if user enter integer and its below 300
        {
            if (flag == 0) //check if we read from file
                printf("  Graph is Empty, Make sure to read from File first\n");
            else
            {
                src= atoi(X); // convert X to integer and save it in src
                dijkstra(graph,src,distn,pre);  //call dijkstra for src

                printf("Please enter the City Destination number:(0-300)\n");
                char Y[40];
                gets(Y);
                if(isdigit(Y[0]) && atoi(Y)<300)
                {
                    dest = atoi(Y); // convert Y to integer and save it in dest

                    Node ptr = graph->head[pre[dest]];//Find the Name of Road Based on dest and its previous Node
                    while(ptr != NULL)
                    {
                        if (ptr->ID == dest)
                        {
                            strcpy(Name,ptr->Name);
                            break;
                        }

                        ptr=ptr->Next;
                    }

                    if (distn[dest]==INFINTY) //if the Destination is not known
                        printf("  These Cities Are Not Connected \n\n");
                    else if(src == dest)
                        printf("  Same City -_- \n\n");
                    else
                        printf("   Distance between %d and %d is %d KM through %s and the Previous Last City is %d \n\n",src,dest,distn[dest],Name,pre[dest]);

                }
                else
                    printf("  invalid input\n");
            }
            graph = makeUnVisited(graph); //make all nodes Unvisited so we can call Dijkstra again
        }

        else if (X[0]!='e')
        {
            printf("  invalid input\n");
        }

    }
    while(X[0] != 'e');

    writeFile(graph,src,dest,Name,distn,pre);//write on file the Last Output we had

    return 0;
}

