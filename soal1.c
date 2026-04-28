 //   Modul               : 03 – Structure and Dynamic Array
 //   Hari dan Tanggal    : Selasa, 28 April 2026
 //   Nama (NIM)          : Raegrand Archamadeus (13224014)
 //   Nama File           : soal1.c
 //   Deskripsi           : Program mencari penjaga terbaik untuk setiap shift yang ada
 //                         kemudian mencetak penjaga terbaiknya

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Penjaga{
    char nama [30];
    int id;
    int score;
} Penjaga;

typedef struct Node{
    Penjaga data;
    struct Node *next;
    struct Node *prev;
}Node;

typedef struct List{
    Node *head;
    int size;
} List;

void List_init(List *L);
void Insert_before(Node *curr, Node *new);
void Insert_after(Node *curr, Node *new);
void List_insert(List *L, Penjaga *p);
void Print_top(List *P,  List *S, List *M);
void Print_list(List *L);

void List_init(List *L){
    L->head = NULL;
    L->size = 0;
}

void Insert_before(Node *curr, Node *new){
    new->next = curr;
    new->prev = curr->prev;
    if(curr->prev != NULL){
        curr->prev->next = new;// problem
    }
    curr->prev = new;
}

void Insert_after(Node *curr, Node *new){
    // printf("Breakpoint 2\n");
    new->prev = curr;
    new->next = curr->next;
    if(curr->next != NULL){
        curr->next->prev = new;
    }
    curr->next = new;
}


void List_insert(List *L, Penjaga *p){
    int inserted = 0;
    Node *newNode = (Node*) malloc(sizeof(Node));
    if(newNode == NULL){
        printf("Alokasi memori gagal!");
        return;
    }

    newNode->data.id = p->id;
    newNode->data.score = p->score;
    strcpy(newNode->data.nama, p->nama);
    newNode->next = NULL;
    newNode->prev = NULL;
    
    Node *curr = L->head;
    if(L->size == 0){
        L->head = newNode;
        inserted = 1;
    }
    else{
        while(curr != NULL){
            if(p->score > curr->data.score){// insert before curr
                if(curr == L->head){
                        L->head = newNode;
                }
                Insert_before(curr, newNode);
                // printf("breakpoint\n");
                inserted = 1;
                break;
            }
            else if(p->score == curr->data.score){// next check id
                if(p->id < curr->data.id){// p better, insert before curr
                    if(curr == L->head){
                        L->head = newNode;
                    }
                    Insert_before(curr, newNode);
                    inserted = 1;
                }
                else if(p->id > curr->data.id){// curr is better, insert after curr
                    Insert_after(curr, newNode);
                    inserted = 1;
                }
                else{// cheeck name
                    printf("breakpoint 4\n");
                    if(strcmp(p->nama, curr->data.nama) < 0){// p better, insert before curr
                        if(curr == L->head){
                            L->head = newNode;
                        }
                        Insert_before(curr, newNode);
                        inserted = 1;
                    }
                    else{// curr better, insert after curr
                        Insert_after(curr, newNode);
                        inserted = 1;
                    }
                }
                break;
            }
            curr = curr->next;
        }
    }
    // printf("inserted = %d\n", inserted);
    if(inserted == 0){
        curr = L->head;
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next = newNode;
        newNode->prev = curr;
    }
    // Print_list(L);
    L->size++;
}
void Print_top(List *P,  List *S, List *M){
    if(P->head != NULL){
        printf("PAGI %s %d %d\n", P->head->data.nama, P->head->data.id, P->head->data.score);
    }
    else{
        printf("PAGI -\n");
    }
    if(S->head != NULL){
        printf("SIANG %s %d %d\n", S->head->data.nama, S->head->data.id, S->head->data.score);
    }
    else{
        printf("SIANG -\n");
    }
    if(M->head != NULL){
        printf("MALAM %s %d %d\n", M->head->data.nama, M->head->data.id, M->head->data.score);
    }
    else{
        printf("MALAM -\n");
    }
}

void Print_list(List *L){
    Node *curr = L->head;
    printf("\nPRINGTING LIST:\n");
    while(curr != NULL){
        printf("%s, %d, %d\n", curr->data.nama, curr->data.id, curr->data.score);
        curr = curr->next;
    }
}

int main(void) {
    int n;
    Penjaga temp;
    char shift[7];
    List pagi, siang, malam;
    List_init(&pagi); 
    List_init(&siang); 
    List_init(&malam);

    scanf("%d", &n);
    for(int i = 0; i<n; i++){
        scanf("%29s", &temp.nama);
        scanf("%d", &temp.id);
        scanf("%6s", &shift);
        scanf("%d", &temp.score);
        if(strcmp(shift, "PAGI") == 0){
            List_insert(&pagi, &temp);
        }
        else if(strcmp(shift, "SIANG") == 0){
            List_insert(&siang, &temp);
        }
        else if(strcmp(shift, "MALAM") == 0){
            List_insert(&malam, &temp);
        }

    }
    Print_top(&pagi, &siang, &malam);
    return 0;
}
