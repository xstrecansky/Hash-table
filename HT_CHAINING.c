#include<stdio.h>
#include<stdlib.h>

#define SIZE 2
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
//Funkcia na vratenie hodnoty
int returnKey(int key){
    return key%SIZE;
}
//Funkcia na alokovanie pamate 
entryNode *allocateEntry(int data){
    entryNode *temp = malloc(sizeof(temp));
    temp->key = returnKey(data);
    temp->data = data;
    temp->next = NULL;
    return temp;
}
//Funkcia na pridanie prvku do hashovacej tabulky
void insert(hTable *hashTable, int data){
    int insertKey = returnKey(data);
    entryNode *tempEntry = hashTable->entries[insertKey];
    if(tempEntry == NULL){
        hashTable->entries[insertKey] = allocateEntry(data);
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
    int searchKey = returnKey(data);
    entryNode *tempEntry = hashTable->entries[searchKey];
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
    int deleteKey = returnKey(data);
    entryNode *deleteEntry = hashTable->entries[deleteKey];
    entryNode *prevEntry;
    if(deleteEntry!=NULL && deleteEntry->data==data){
        hashTable->entries[deleteKey] = deleteEntry->next;
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
int main(){
    //Vytvorime hashovaciu tabulku
    hTable *hashTable = malloc(sizeof(hashTable));
    hashTable->entries = malloc(sizeof(entryNode*)*SIZE);
    for(int i=0;i<SIZE;i++)
        hashTable->entries[i]=NULL;
    int i=0,j=0;
    int initValue, inputValue;
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
        else{
            insert(hashTable, inputValue);
        }
    }
    return 0;
}
