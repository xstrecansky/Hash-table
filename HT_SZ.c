#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 1000
//Reprezentuje jeden prvok v hashovacej tabulke
typedef struct entryNode{
    int data;
    int key;
    struct entryNode *next;
}entryNode;
//Reprezentuje hashovaciu tabulku
typedef struct{
    entryNode **entries;
}hTable;
//Funkcia na alokovanie pamate 
entryNode *allocateEntry(int data){
    entryNode *temp = malloc(sizeof(temp));
    temp->key = data%SIZE;
    temp->data = data;
    temp->next = NULL;
    return temp;
}
//Funkcia na pridanie prvku do hashovacej tabulky
void insert(hTable *hashTable, int data){
    entryNode *tempEntry = hashTable->entries[data%SIZE];
    if(tempEntry == NULL){
        hashTable->entries[data%SIZE] = allocateEntry(data);
        return;
    }
    entryNode *prevEntry;
    while(tempEntry!=NULL){
        prevEntry = tempEntry;
        tempEntry = prevEntry->next;
    }
    prevEntry->next = allocateEntry(data);
    return;
}
//Funckia na vyhladanie prvku v tabulke
int search(hTable *hashTable, int data){
    entryNode *tempEntry = hashTable->entries[data%SIZE];
    if(tempEntry==NULL)
        return 0;
    while(tempEntry!=NULL){
        if(tempEntry->data==data)
            return 1;
        tempEntry = tempEntry->next;
    }
    return 0;
}
//Funkcia na vymazanie prvku v tabulke
void delete(hTable *hashTable, int data){
    entryNode *deleteEntry = hashTable->entries[data%SIZE];
    entryNode *prevEntry;
    if(deleteEntry!=NULL && deleteEntry->data==data){
        hashTable->entries[data%SIZE] = deleteEntry->next;
        free(deleteEntry);
        return;
    }
    while (deleteEntry != NULL && deleteEntry->data!=data) {
        prevEntry = deleteEntry;
        deleteEntry = deleteEntry->next;
    }
    if (deleteEntry == NULL)
        return;
    prevEntry->next = deleteEntry->next;
    free(deleteEntry);
}
//Funckia na vypisanie hodnot tabulky
void printTable(hTable *hashTable){
    printf("-----------\n");
    for(int i=0;i<SIZE;i++){
        entryNode *tempEntry = hashTable->entries[i];
        if(tempEntry == NULL)
            continue;
        while(tempEntry!=NULL){
            printf("%d, ",tempEntry->data);
            tempEntry = tempEntry->next;
        }
        printf("\n");
    }
    printf("-----------\n");
}
//Funkcia na uvolnenie spajaneho zoznamu
void freeNode(entryNode *temp){
    entryNode *previous;
    while(temp!=NULL){
        previous=temp;
        temp = temp->next;
        free(temp);
    }
}
//Funckia na uvolnenie hash tabulky
void freeHash(hTable *hashTable){
    entryNode *tempEntry;
    for(int i=0;i<SIZE;i++){
        tempEntry = hashTable->entries[i];
        freeNode(tempEntry);
    }
}
int main(){
    //Vytvorime hashovaciu tabulku
    printf("Ak chces testovat O(n) stlac 1\n");
    int test;
    scanf("%d",&test);
    if(test == 1){
        clock_t start;
        double time;
        struct node* root;
        printf("Casova zlozitost HT SZ:\n\n");
        printf("Pocet Prvkov\t\t|Insert\t\t|Search\t\t|Delete\n");
        for(int i=1;i<=10;i++){
            hTable *hashTable = malloc(sizeof(hashTable));
            hashTable->entries = malloc(sizeof(entryNode*)*SIZE);
            for(int k=0;k<SIZE;k++){
                hashTable->entries[k]=NULL;
            }
            printf("------------------------+---------------+---------------+--------\n");
            printf("%d\t\t\t", (1000*i));
            start=clock();
            //Testujeme insert
            for(int j=0;j<(1000*i);j++){
                insert(hashTable, random()%(1000*i));
            }
            time=(clock()-start)/(double)CLOCKS_PER_SEC;
            printf("|%f\t",time);
            //Testujeme search
            start=clock();
            for(int j=0;j<(1000*i);j++){
                search(hashTable, random()%(1000*i));
            }
            time=(clock()-start)/(double)CLOCKS_PER_SEC;
            printf("|%f\t",time);
            //Testujeme delete
            start=clock();
            for(int j=0;j<(1000*i);j++){
                delete(hashTable, random()%(1000*i));
            }
            time=(clock()-start)/(double)CLOCKS_PER_SEC;
            printf("|%f\n",time);
            //Uvolnime pamat
            //freeHash(hashTable);
        }
        printf("-----------------------------------------------------------------\n");
        return 0;
    }
    hTable *hashTable = malloc(sizeof(hashTable));
    hashTable->entries = malloc(sizeof(entryNode*)*SIZE);
    for(int i=0;i<SIZE;i++)
        hashTable->entries[i]=NULL;
    int initValue, inputValue, i=0, j=0;
    printf("Vloz hodnotu do hasovacej tabulky\n");
    scanf("%d",&initValue);
    while(i==0){
        printf("Vloz dalsiu hodnotu do hasovacej tabulky\nAk vlozis %d, vkladanie skonci\n",initValue);
        scanf("%d",&inputValue);
        if(initValue==inputValue){
            while(j==0){
                printf("Vloz 1 ak chces vypisat hodnoty tabulky\nVloz 2 ak chces vymazat hodnotu v tabulky\nVloz 3 ak chces najst hodnotu v tabulke\nVloz 4 ak chces opat vlozit hodnoty tabulky\nVloz ine ak chces ukoncit program\n");
                scanf("%d",&inputValue);
                switch (inputValue){
                    case 1:
                        printTable(hashTable);
                        break;
                    case 2:
                        scanf("%d",&inputValue);
                        delete(hashTable, inputValue);
                        printf("Hodnota bola odstranena\n");
                        break;
                    case 3:
                        scanf("%d",&inputValue);
                        if(search(hashTable, inputValue)==0)
                            printf("Hodnota sa nenachadza v tabulke\n");
                        else
                            printf("Hodnota sa nachadza v tabulke\n");
                        break;
                    case 4:
                        j=1;
                        break;
                    default:
                        j=1;
                        i=1;
                        break;
                }
            }
        }
        insert(hashTable, inputValue);
    }
    freeHash(hashTable);
    return 0;
}