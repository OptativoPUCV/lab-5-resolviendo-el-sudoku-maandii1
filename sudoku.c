#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    for (int i=0 ; i<9 ; i++){ //validar filas
        int fila[10]={0};
        for (int j=0 ; j<9 ; j++){
            int num = n->sudo[i][j];
            if(num !=0) {
                if(fila[num]==1)
                    return 0;
                fila[num]=1;
            }
        }
    }
  
    //validar columnas
    for (int i=0 ; i<9 ; i++) {
      int col[10]={0};
        for (int j=0 ; j<9 ; j++){
            int num = n->sudo[j][i];
          if (num !=0){
            if(col[num]) return 0;
            col[num]= 1;
          }
        }
    }
    
    for (int i=0 ; i<9 ; i++){
        int box[10]={0};
        for (int j=0 ; j<9 ; j++){
            int k = (i/3)*3 + j/3;
            int l = (i%3)*3 + j%3;
            int num = n->sudo[k][l];
            if(num !=0) {
                if(box[num]== 1)
                    return 0;
                box[num]= 1;
            }
            
        }
    }
    return 1;

}


List* get_adj_nodes(Node* n){
    List* list=createList();

    for (int i=0 ; i<9 ; i++){
        for (int j=0 ; j<9 ; j++) {
            if(n->sudo[i][j] == 0) {
                for (int k=1 ; k<=9 ; k++) {
                    Node* new = copy(n);
                    new->sudo[i][j] = k;
                    if(is_valid(new)){
                        pushBack(list, new);
                    } else {
                        free(new);
                    }
                }
                return list;
            }
        }
    }
    return list;
}


int is_final(Node* n){
    for (int i=0 ; i<9 ; i++){
        for (int j=0 ; j<9 ; j++) {
            if(n->sudo[i][j] == 0)
                return 0;
        }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
    Stack* stack = createStack();
    push(stack, initial);
    Node* current;
    while(!is_empty(stack)){
        current = top(stack);
        pop(stack);
        (*cont)++;
        if(is_final(current)){
            return current;
        }
        List* adj = get_adj_nodes(current);
        for (Node* n = first(adj); n != NULL; n = next(adj)) {
            push(stack, n);
        }
        clean(adj);
    }
    clean(stack);

  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/