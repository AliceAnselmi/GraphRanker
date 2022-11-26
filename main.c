#include<stdio.h>
#include<limits.h>
#include<string.h>
#include<stdlib.h>

typedef struct node
{
    int index;
    unsigned long int weight;
    struct node *next;
}node_t;

typedef struct tree
{
    int idx;
    unsigned long int key;
    struct tree *father;
    struct tree *left;
    struct tree *right;Inseriscinode
}tree_t;

node_t*Append(node_t*, int, unsigned long int, int);

unsigned long int StringConversion(char*, int);

unsigned long int Dijkstra(node_t *[], int);
int Dequeue(int[], long unsigned int[], int);

tree_t*QueueSum(tree_t*, unsigned long int, int, int);
void PrintRanking(tree_t*, int, int);
tree_t*InsertNode(tree_t*,tree_t*);

int main()
{
    unsigned long int val, sum;
    int d, k, i, j,l,m, graphcounter;
    char v1[11], v2[22]; // v1 is used to parse strings, v2 is used to parse numbers
    node_t **graph; //a graph element is a node_t pointer
    tree_t *top=NULL;

    for(i=0;i<22;i++)
    {
        v2[i]=getchar_unlocked();
        if(v2[i]==' ')
            break;
    }
    v2[i]='\0';
    d=StringConversion(v2,i);
    i++;
    for(j=0;j<i;j++)
        v2[j]='0';
    for(;i<22;i++)
    {
        v2[i]=getchar_unlocked();
        if(v2[i]=='\n')
            break;
        if(v2[i]=='\r')
        {
            getchar_unlocked();
            break;
        }
    }
    v2[i]='\0';
    k= StringConversion(v2,i);

    graph=malloc(d*sizeof(node_t*));
    graphcounter=0;

    while(1)
    {
        for(m=0;m<15;m++)//read "AggiungiGrafo" or "TopK"
        {
            v2[m]=getchar_unlocked();
            if((v2[m]=='\n'))
                break;
        }
        if(strcmp(v2,"TopK")>0)
        {
            if(feof(stdin))
                break;
            if(top!=NULL)
                PrintRanking(top,k, graphcounter);
            printf("\n");
        }
        else
        {
            for (i = 0; i < d; i++)
            {
                for(j=0;j<d;j++)
                {
                    for(l=0;l<11;l++)
                    {
                        v1[l]=getchar_unlocked();
                        if(v1[l]==','||v1[l]=='\n')
                        {
                            v1[l]='\0';
                            break;
                        }
                    }
                    val=StringConversion(v1,l);
                    graph[i]=Append(graph[i], j, val, graphcounter);//j is the index of the node i'm pointing to 
                }

            }
            sum=Dijkstra(graph, d);
            top=QueueSum(top, sum, graphcounter, k);
            graphcounter++;
        }
    }
    return 0;
}

unsigned long int StringConversion(char*s, int dim)
{
    int i;
    unsigned long int num, pot;
    num=0;
    pot=1;

    i=dim-1;
    for(;i>=0;i--)
    {
        num=num+((*(s+i)-'0')*pot);
        pot=pot*10;
    }
    return num;
}

node_t *end;
node_t *Append(node_t *h, int idx, unsigned long int w, int graphcounter) {
    node_t *n, *p;

    if(graphcounter==0)
    {
        n = malloc(sizeof(node_t));
        n->index = idx;
        n->weight = w;
        n->next = NULL;
        if (h != NULL) {
            end->next = n;
            end=end->next;
        } else
        {
            h = n;
            end=h;
        }
    }
    else
    {
        if(idx==0)
        {
            h->index=idx;
            h->weight=w;
            end=h;
        }
        else
        {
            p=end->next;
            p->index=idx;
            p->weight=w;
            end=end->next;
        }
    }


    return h;
}

unsigned long int Dijkstra (node_t *graph[], int d)
{
    node_t*p;
    unsigned long int newd, dist[d];
    int i,curr, q[d-1], dimcoda, sum;

    //queue initialization
    dist[0]=0;
    for(i=1;i<d;i++)
    {
        q[i-1]=i;
        dist[i]=ULONG_MAX;
    }

    curr=0;
    dimcoda=d-1;
    while(dimcoda!=0)
    {
        newd=ULONG_MAX;
        p=graph[curr];
        for(;p!=NULL;p=p->next)
        {
            if((p->weight>0)&&(curr!=p->index)&&(p->index!=0))//exclude self-pointing nodes and paths towards 0
            {
                newd=dist[curr]+p->weight;
                if(newd<dist[p->index])
                    dist[p->index]=newd;

            }

        }
        if(curr==0&&newd==ULONG_MAX)//node 0 is not reachable
            break;
        curr=Dequeue(q,dist, dimcoda);
        if(curr==-1)    //reached the point where the remaining nodes are not reachable
            break;
        dimcoda--;
    }

    sum=0;
    if(curr!=0)
        for(i=0;i<d;i++)
            sum=sum+dist[i];
    return sum;

}

int Dequeue(int q[], long unsigned int dist[], int dimcoda)
{
    //returns the head of the queue
    int i, index, imin;
    unsigned long int min;

    min=ULONG_MAX;
    imin=-1;
    index=0;
    for(i=0;i<dimcoda;i++)
    {
        if(dist[q[i]]<min)
        {
            min=dist[q[i]];
            index=q[i];
            imin=i;
        }
    }
    if(imin!=-1)
        for(i=imin+1;i<dimcoda;i++)
            q[i-1]=q[i];
        // Not reachable nodes: I will reach a point where in the queue I have only nodes whose distance is set to infinity
    if(dimcoda>=0&&min==ULONG_MAX)
    {
        for(i=0;i<dimcoda;i++)
            dist[q[i]]=0;
        index=-1;
    }
    return index;
}

tree_t*small,*big;
int dimtree=0;

tree_t*QueueSum(tree_t *h, unsigned long int val, int index, int k)
{
    tree_t *del, *cur;
    tree_t *x;


    if(dimtree<k) {
        x=malloc(sizeof(tree_t));
        x->left=NULL;
        x->right=NULL;
        x->father=NULL;
        x->key=val;
        x->idx=index;
        h=InsertNode(x,h);
    }

    if(dimtree==k)
    {

        if(val<big->key)
        {
            x=malloc(sizeof(tree_t));
            x->left=NULL;
            x->right=NULL;
            x->father=NULL;
            x->key=val;
            x->idx=index;
            if(big==h)  // degenerate case: the maximum element is the root
            
                {
                h=h->left;

                h->father=NULL;
                cur=h;
                while(cur->right!=NULL)
                    cur=cur->right;
                big=cur;
                h=InsertNode(x,h);
                }

            else
            {
                if(big->left==NULL) {  //normal case: the leftmost element doesn't have children and it's the highest one
                    if(big==big->father->right)  //cur is the right-side child of its father
                        {
                        cur=big->father;
                        big->father->right=NULL; //simply delete the node, no replacement is needed since it doesn't have any children
                        big=cur;
                        h=InsertNode(x,h);
                        }
                }
                else if(big->left!=NULL)
                {
                    del=big->left;
                    del->father=big->father;
                    if(big==big->father->right)
                        del->father->right=del;
                    else if(big==big->father->left)
                        del->father->left=del;
                    cur=del;
                    while(cur->right!=NULL)
                        cur=cur->right;
                    big=cur;
                    h=InsertNode(x,h);
                }
            }
        }
    }
    if(dimtree<k)
        dimtree++;

    return h;
}
tree_t*InsertNode(tree_t*x, tree_t*h) {

    tree_t *cur, *pre;
    if (h == NULL) {
        h = x;
        small=h;
        big=h;
    } else {

        //x is smaller than the lowest element
        if(x->key<small->key)
        {
            cur=small;
            x->father=cur;
            cur->left=x;
            small=x;
        }
        // x is bigger than the highest element
        else if(x->key>big->key)
        {
            cur=big;
            x->father=big;
            cur->right=x;
            big=x;
        }
        // now I act as if x wasn't either the new maximum nor the new minimum
        else if((x->key-small->key)<(big->key-x->key))  // i am closer to the minimum: i start from it and i go up
            {
            cur=small;
            // x does NOT have to be right child of "small": i have to go up ("small" cannot have left children)
            if((small->father!=NULL&&x->key>small->father->key))
                while(cur->father!=NULL&&x->key>cur->father->key)  //going up
                    cur=cur->father;

                //now going down again: algorithm is the usual one
            while (cur != NULL) {
                pre = cur;
                if (x->key < cur->key)
                    cur = cur->left;
                else if (x->key >= cur->key)
                    cur = cur->right;

                }
            x->father = pre;
            if (x->key < pre->key)
                pre->left = x;
            else if (x->key >= pre->key)
                pre->right = x;
            }
        else if ((x->key-small->key)>=(big->key-x->key))//I'm starting from the maximum
            {
            cur=big;
            if(big->father!=NULL&&x->key<big->father->key)
                while(cur->father!=NULL&&x->key<cur->father->key)  //going up
                    cur=cur->father;
            //now going down again: the algorithm is the same as before
            while (cur != NULL) {
                pre = cur;
                if (x->key < cur->key)
                    cur = cur->left;
                else if (x->key >= cur->key)
                    cur = cur->right;
                }
            x->father = pre;
            if (x->key < pre->key)
                pre->left = x;
            else if (x->key >= pre->key)
                pre->right = x;
            }
    }
    return h;
}

void PrintRanking(tree_t *h, int k, int graphcounter)
{
    int i;
    //if the number of parsed graphs is smaller than the dimension of the rank, I simply have to print all indeces up to that point
    if(graphcounter<=k)   
    {
        i=0;
        printf("%d", i);
        for(i=1;i<graphcounter;i++)
            printf(" %d", i);
    }
    else
    {
        if(h->father==NULL)
        {
            printf("%d", h->idx);
            if (h->left != NULL)
                PrintRanking(h->left,k,graphcounter);
            if (h->right != NULL)
                PrintRanking(h->right,k,graphcounter);
        }
        else
        {
            printf(" %d", h->idx);
            if (h->left != NULL)
                PrintRanking(h->left,k,graphcounter);
            if (h->right != NULL)
                PrintRanking(h->right,k,graphcounter);
        }
    }
}
