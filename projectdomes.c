#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

int root, lvl, hascycle = FALSE;

typedef struct tf *foit;
struct tf {
    int i,j,level,father, active;
    float gr;
    foit previous;
    foit next;
    foit u;
    foit d;
};
foit  A[30],B[30],head, tail, temp, temp1, aux;

void insert1(foit *h, foit *t, int a);
void insert2(foit *h, foit *t,int b);
void insert0(int a, int b);
void Activate_symmetric(foit *aux, int b);
void Spanning_tree(foit *aux);
void cycles(foit aux);
void findcycles(int x, int y);
void Print1(foit h);

void delete0(int k, int l);
void delete1(foit *h, int l);
void delete2(foit *h, int k);

int main(void) {

    char c1;

    c1 = 'a';
    //initialization of vertical and horizontal array
    int i;
	for ( i = 0; i < 30; ++i) {

        A[i] = (foit) malloc(sizeof(struct tf));
        B[i] = (foit) malloc(sizeof(struct tf));

        A[i]->i=i;
        A[i]->j=0;
        A[i]->level	= 0;
		A[i]->active = FALSE;
        A[i]->previous = NULL;
        A[i]->next = NULL;
        A[i]->u = NULL;
        A[i]->d = NULL;


        B[i]->i=0;
        B[i]->j=i;
        B[i]->level	= 0;
		B[i]->active	= FALSE;
        B[i]->previous = NULL;
        B[i]->next = NULL;
        B[i]->u= NULL;
        B[i]->d = NULL;

}

    while (c1 != 'q') {
        printf("\n\n Previous choice was %c \n", c1);
        printf("\n Your options are (i)nsert, (p)rint, (d)elete, (s)panningtree, (c)ycles, (q)uit");
        if (c1 != 'q') {
            printf("\n Give new choice: ");
            c1 = 'a';
            fflush(stdin);
            c1 = getchar();
            getchar();
            if (c1 == 'q')
                exit(0);
            if (c1 == 'i') {
                printf("\n INSERT \n");
                int a,b;
             do
             {
                printf("\n Give input between 0 and 29 \n");
                scanf("%d", &a);
                getchar();
            }while (a < 0 || a > 29);

            do
            {
                printf("\n Give input between 0 and 29 \n");
                scanf("%d", &b);
                getchar();
            }while (b < 0 || b > 29);
            if (a!=b){//node with the same i,j is not accepted because it creates a self cycle
                insert0(a,b);
            }
            else
            printf("Can not insert edge that creates self cycle");

            }
            if (c1 == 'd') {
                printf("\n DELETE \n");
                int k,l;

                printf("\n Give node you want to delete: ");
                scanf(" %d", &k);
                getchar();
                scanf(" %d", &l);
                getchar();
                delete0(k, l);
            }
            if (c1 == 's'){
			printf("Insert Root Node:\n"); fflush(stdout);
			scanf("%d", &root);//user gives root
			A[root]->level  = 1;//level of root is 1
			B[root]->father = root;//root has father itself
			B[root]->active = TRUE;//its edge is activated
			Spanning_tree(&A[root]);
		}
		    if (c1 == 'c'){
		    	int k;
			for (k=0; k < 30; ++k)
				cycles(A[k]);
			if (hascycle == FALSE)
				printf("Tree has no cycles.\n");
		}
	}
            if (c1 == 'p') {
                printf("\n PRINT \n");

                Print1(head);

            }

        }

    return 0;
}

void insert0(int a, int b)
{
              //memory allocation for temp, temp1. temp is the element we insert and temp1 is its symmetric
                temp = (foit) malloc(sizeof(struct tf));
                temp1 = (foit) malloc(sizeof(struct tf));
              //initialization of temp
                temp->active=FALSE;
				temp->father=0;
				temp->level=0;
                temp->i=a;
                temp->j=b;
                temp->u=NULL;
                temp->d=NULL;
                temp->next = NULL;
                temp->previous = NULL;
              //insert1, insert2 are called for the right connction of their pointers
                insert1(&A[a], &temp,b);
                insert2(&B[b], &temp,a);
              //initialization of temp1
                temp1->active=FALSE;
				temp1->father=0;
				temp1->level=0;
                temp1->i = b;
                temp1->j = a;
                temp1->u = NULL;
                temp1->d = NULL;
                temp1->next = NULL;
                temp1->previous = NULL;
              //insert1, insert2 are called for temp1 this time
                insert1(&A[b], &temp1, a);
                insert2(&B[a], &temp1, b);
}

void insert1(foit *h, foit *temp, int b) {

//if ((*h)!=NULL){
        if ((*temp)->j > (*h)->j) {
        	//if h->next is not NULL it keeps comparing with the other elements by calling insert1 recursively
            if ((*h)->next != NULL) {

                insert1(&((*h)->next), &(*temp),b);

            } else {//if h->next is NULL, then temp will be inserted as last element


                (*temp)->previous = (*h);
                (*temp)->next=(*h)->next;
                (*h)->next = *temp;

            }
        } else //temp is inserted left of h
		{


            (*temp)->previous = (*h)->previous;
            (*temp)->next = *h;
            (*h)->previous = *temp;
            (*h)=*temp;


        }
}
//else
  //  *h=temp;
    //}


void insert2(foit *h, foit *temp,int a) {


  // if ((*h)!=NULL){

        if ((*temp)->i > (*h)->i) {
            if ((*h)->d != NULL) {

                insert2(&((*h)->d), &(*temp),a);

            } else {

                (*temp)->u = *h;
                (*h)->d = *temp;


            }
        } else if ((*temp)->i < (*h)->i) {

            (*temp)->u = (*h)->u;
            (*temp)->d = *h;
            (*h)->u = *temp;
            (*h)=*temp;

        }
   }
  // else
    //*h=temp;
//}
void delete0(int k,int l)
{//delete0 just calls delete1, delete2 for the deletion of the given element and the update of the pointers.
//They are called two times so that the symmetric node is deleted as well
	delete1(&A[k], l);
	delete2(&B[l], k);
	delete1(&A[l], k);
    delete2(&B[k], l);
}

void delete1(foit *h, int l) {

    	//until the node is found, delete1 is called recursively
        if ((*h)->j != l && ((*h)->next)!=NULL) {
            delete1(&((*h)->next), l);
        } else if ((*h)->j == l) {//once it is found the pointers are being updated
            aux = *h;
            if((*h)->next != NULL)
			{
            (*h)->next->previous = (*h)->previous;
			}
            if((*h)->previous != NULL)
			{
            (*h)->previous->next = (*h)->next;
			}
			else
			{
                *h=(*h)->next;
            }
        }
        else //if it does not exist a message is printed
        printf("\nThe node does not exist\n");

}

void delete2(foit *h, int k) {

    if (*h != NULL) {
        if ((*h)->i != k) {
            delete2(&((*h)->d), k);
        } else {
            aux = *h;
            if((*h)->d != NULL)
			{
            (*h)->d->u = (*h)->u;
			}
            if((*h)->u != NULL)
			{
            (*h)->u->d = (*h)->d;
			}
			else
			{
                *h=(*h)->d;
            }
            //the struct is deleted only in delete2, delete1 only updates the pointers
             free(aux);
        }
    }
}
//activation of symmetric edge with recursive calls until the edge is found
void Activate_symmetric(foit *aux, int b){
	if ((((*aux)->j) < b) && (((*aux)->next) != NULL))
		Activate_symmetric((&(*aux)->next), b);
	else
		(*aux)->active = TRUE;
}

void Spanning_tree(foit *aux){
	int k, printlevel;
	printf("Root:%d\n",root);
	for (lvl=1; lvl < 30; ++lvl)
	{
        	printlevel = FALSE;//printlevel is only used for the better display of the spanning tree
		//i am searching the vertical array
		for (k=0; k < 30; ++k)
		{
		   	if (A[k]->level == lvl && A[k]->active == FALSE)
			   {
		    	*aux = A[k];
		        while ((*aux)->next != NULL)
				{
			           	*aux = (*aux)->next;
		//i include or not the node in spanning tree by checking, and i flag him as active, appointing him a father and increasing the level
			        if ((*aux)->active == FALSE && B[(*aux)->j]->active == FALSE)
					{
						(*aux)->active	 = TRUE;
						B[(*aux)->j]->active = TRUE;
						B[(*aux)->j]->father = (*aux)->i;
						A[(*aux)->j]->level	 = lvl + 1;
					//activation of symmetric edge by calling Activate_symmetric
						Activate_symmetric(&A[(*aux)->j], (*aux)->i);
					if (printlevel == FALSE)
					{
						printf("Level %d: ",lvl);
						printlevel = TRUE;
					}
						printf("{%d}", (*aux)->i);
						printf("(%d,%d)", (*aux)->i, (*aux)->j);
						printf("/(%d,%d),\t", (*aux)->j, (*aux)->i);
			            	}
			        }
			        //activation of row so it is not visited again
			        A[k]->active = TRUE;
			}
		}
		if (printlevel == TRUE)
			printf("\n");
	}
	printf("\n");
}
void findcycles(int x, int y){
	int g = 0, m = 0, n = 0, check = FALSE;
	int K[29], L[29];
	//initialization of Ê, L
	for (m=0; m < 29; ++m){
		if (K[m] != 0)
			K[m] = 0;
		if (L[m] != 0)
			L[m] = 0;
	}
	//K is filled with the nodes, using the fathers to traverse all the way up to the root
	m = 0;
	while (B[x]->j != root){//ascending until root is reached
		K[m] = B[x]->j;
		x = B[x]->father;
		m=m+1;
	}
	if (B[x]->j == root)
		K[m] = root;

	//L is filled too
	n = 0;
	while (B[y]->j != root){
		L[n] = B[y]->j;
		y = B[y]->father;
		n=n+1;
	}
	if (B[y]->j == root)
		L[n] = root;


	for (m=0;((m < 29) && (check == FALSE) && (K[m] != 0)); ++m)//check is used so that the for loops stop running when it becomes TRUE
	{
		for (n=0; ((n < 29) && (check == FALSE) && (L[n] != 0)); ++n)
		{
			if (K[m] == L[n])//if the element is the same
			{
				check	= TRUE;
				hascycle	= TRUE;//if hascycle remains false, then there is no cycle
			}
		}
	}


	//printing of edges that create the cycle
	printf(" Cycle{");
	for (g=0; g < n; ++g)
		printf("%d ", L[g]);
	for (m=m-2; m >= 0; --m)
		printf("%d ", K[m]);
	printf("}\n");
}


void cycles(foit aux){
	while ((aux->next) != NULL){
		aux = aux->next;
		//checking for inactive edges
		if (aux->active == FALSE){
			printf("(%d,%d):", aux->i, aux->j);
		//once inactive edge is found, findcycles is called in order to find and print the cycle
			findcycles(aux->i, aux->j);
		}
	}
}

void Print1(foit h)
{
//printing of sparse array. Using an auxiliary it prints the elements of the matrix,
//starting from the vertical array and continuing with the next pointers
    int i;
    foit aux;
    aux=h;
	for (i = 0; i < 30; i++)
	{
		aux= A[i];
		printf("[%d, %d]->", aux->i, aux->j);
		aux = A[i]->next;
		while (aux != NULL)
		{
			printf("[%d, %d", aux->i, aux->j);
			printf("]->");
			aux = aux->next;
		}
		printf("NULL\n");
	}
}

