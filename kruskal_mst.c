

#include <stdio.h>
#include <stdlib.h>


struct Edge {

	int start;		
	int end;		
	int weight;	

};

struct Graph {

	int E;		//number of edges
	int V;		//number of vertices 
	struct Edge* edge;	//pointer to array of edges
	
};


struct subset {
	
	int parent;	
	int rank;	

};


struct Graph* createGraph(int E, int V) {

	struct Graph* graph = (struct Graph*) malloc (sizeof(struct Graph));
	
	//assign no. of edge and no. of vertex
	graph->E = E;
	graph->V = V;

	//pointer to edge
	graph->edge = (struct Edge*) malloc (graph->E * sizeof(struct Edge));

	//return graph pointer
	return graph;

}


  //find the subset in which
  //the vertex i belongs
 
int Find(struct subset subsets[], int i) {
	
	if (subsets[i].parent != i) {

		subsets[i].parent = Find(subsets, subsets[i].parent);

	}
	
	return subsets[i].parent;

}

//union on 2 subsets

void Union(struct subset subsets[], int x, int y) {

	int rootOfX = Find(subsets, x);
    int rootOfY = Find(subsets, y);
 
    if (subsets[rootOfX].rank < subsets[rootOfY].rank) {
     
        subsets[rootOfX].parent = rootOfY;

    }
    else if (subsets[rootOfX].rank > subsets[rootOfY].rank) {

        subsets[rootOfY].parent = rootOfX;

    }
    else {

        subsets[rootOfY].parent = rootOfX;
        subsets[rootOfX].rank++;

    }
}


void printMST(struct Graph* graphMST) {
	int i, noOfEdges = graphMST->E;
	for (i = 0; i < noOfEdges; i++) {
		printf("Edge %d-->%d Weight: %d\n", graphMST->edge[i].start, graphMST->edge[i].end, graphMST->edge[i].weight);
	}
}


int hasCycle(struct Graph* graph) {

	//variable
	int i, j, x, y;

	//total number of vertices in the graph
	int V = graph->V;
	int E = graph->E;

	
    //create subset
	 
	struct subset* subsets = (struct subset*) malloc (V * sizeof(struct subset));

	//initialize subset
	for (i = 0; i < V; i++) {

		subsets[i].parent = i;
		subsets[i].rank = 0;

	}

	//find cycle
	for (j = 0; j < E; j++) {

		x = Find(subsets, graph->edge[j].start);
		y = Find(subsets, graph->edge[j].end);

		if (x == y) {

			return 1;

		}

		Union(subsets, x, y);

	}
	

	return 0;

}

int myComp(const void* a, const void* b) 
{ 
	struct Edge* a1 = (struct Edge*)a; 
	struct Edge* b1 = (struct Edge*)b; 
	return a1->weight > b1->weight; 
} 

void kruskal(struct Graph* graph) {

	int i, j;

	//number of edges and vertices in the graph
	int E = graph->E;
	int V = graph->V;
	
	//sort the edges of the graph in non decreasing order of weight
	 
	qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);
		
	//MST graph
	 
	struct Graph* graphMST = createGraph(V - 1, V);

	
	for (i = 0, j = 0; i < E && j < V - 1; i++) {

		graphMST->edge[j] = graph->edge[i];
		graphMST->E = j + 1;

		if (!hasCycle(graphMST)) {

			j++;

		}

	}
	printMST(graphMST);

}


int main (void) {

	//total number of edges and vertices
	int E = 5;
	int V = 4;

	
	  //create graph
	 
	struct Graph* graph = createGraph(E, V);

	
	 // add edges to the graph
	 
	//edge: A -- B
	graph->edge[0].start = 0;
	graph->edge[0].end = 1;
	graph->edge[0].weight = 2;
	
	//edge: A -- C
	graph->edge[1].start = 0;
	graph->edge[1].end = 2;
	graph->edge[1].weight = 2;
	
	//edge: B -- C
	graph->edge[2].start = 1;
	graph->edge[2].end = 2;
	graph->edge[2].weight = 1;
	
	//edge: B -- D
	graph->edge[3].start = 1;
	graph->edge[3].end = 3;
	graph->edge[3].weight = 5;
	
	//edge: D -- C
	graph->edge[4].start = 2;
	graph->edge[4].end = 3;
	graph->edge[4].weight = 3;
	

	kruskal(graph);

	return 0;
}
