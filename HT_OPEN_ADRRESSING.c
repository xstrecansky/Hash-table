#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define EMPTY_SPACE -1

int hash(int value, int size){
    return value%size;
}
void initHashTable(int size, int *hashTable){
    for(int i=0;i<size;i++){
        (hashTable)[i]=EMPTY_SPACE;
    }
}
//Funkcia na vypisanie hodnot v tabulke
void printHashTable(int size, int *hashTable){
    for(int i=0;i<size;i++){
        if((hashTable)[i]==EMPTY_SPACE)
            printf("%d\t---\n",i);
        else
            printf("%d\t%d\n",i,hashTable[i]);
    }
}
//Funkcia na vlozenie prvku do hashovacej tabulky
void insert(int size , int *hashTable, int data, int key){
    if(hashTable[key]==EMPTY_SPACE)
        hashTable[key]=data;
    else{
        key++;
        if(key>=(size))
            key=0;
        insert(size, hashTable, data, (key));
    }
    return;
}
//Funkcia na vyhladanie prvku v tabulke
int search(int size, int *hashTable, int data, int key){
    if(hashTable[key]==EMPTY_SPACE)
        return EMPTY_SPACE;
    if(hashTable[key]==data)
        return data;
    else{
        key++;
        if(key>=(size))
            key=0;
        search(size, hashTable, data, key);
    }
    return data;
}
//funkcia na vymazanie prvku v tabulke
void delete(int size, int *hashTable, int data, int key){
    if(hashTable[key]==EMPTY_SPACE)
        return;
    if(hashTable[key]==data){
        hashTable[key]=EMPTY_SPACE;
        return;
    }
    else{
        key++;
        if(key>=size)
            key=0;
        delete(size, hashTable, data, key);
    }
    return;
}
//Pozrieme sa na pocet vyplnenych prvkov v tabulke
//V pripade vyplnenia vratime 1
//V pripade nezaplnenej polovice vratime -1
int checkSize(int size, int *hashTable){
    int counter=0;
    for(int i=0;i<(size);i++){
        if((hashTable)[i]!=EMPTY_SPACE)
            counter++;
    }
    if(counter>=size){
        return 1;
    }
    else if((counter*2)<size){
        return -1;
    }
    return 0;
}
int main(){
    int i=0,j=0, initValue, inputValue;
    printf("Vloz hodnotu do hasovacej tabulky\n");
    scanf("%d",&initValue);
    int size=2;
    int *hashTable = malloc(sizeof(int)*size);
    initHashTable(size, (hashTable));
    insert(size, hashTable, initValue, hash(initValue, size));
    while(i==0){
        j=0;
        printf("Vloz dalsiu hodnotu do hasovacej tabulky\nAk vlozis %d, program skonci\n",initValue);
        scanf("%d",&inputValue);
        if(initValue==inputValue){
            while(j==0){
                printf("Vloz 1 ak chces vypisat hodnoty tabulky\nVloz 2 ak chces vymazat hodnotu v tabulky\nVloz 3 ak chces najst hodnotu v tabulke\nVloz 4 ak chces opat vlozit hodnoty tabulky\nVloz ine ak chces ukoncit program\n");
                scanf("%d",&inputValue);
                switch (inputValue){
                    case 1:
                        printHashTable(size, hashTable);
                        break;
                    case 2:
                        scanf("%d",&inputValue);
                        delete(size, hashTable, inputValue, hash(inputValue, size));
                        //Pripad kedy zmensujeme tabulku
                        if((checkSize(size, hashTable))==-1){
                            int *tempTable = malloc(sizeof(int)*size);
                            initHashTable(size, tempTable);
                            for(int i=0;i<size;i++){
                                tempTable[i]=hashTable[i];
                            }
                            hashTable = realloc(hashTable, sizeof(int)*(size/2));
                            initHashTable(size/2,hashTable);
                            for(int i=0;i<size;i++){
                                insert((size/2), hashTable, tempTable[i], tempTable[i]%(size/2));
                            }
                            size/=2;
                        }
                        break;
                    case 3:
                        scanf("%d",&inputValue);
                        if(search(size, hashTable, inputValue, hash(inputValue, size)))
                            printf("Hodnota %d sa nachadza v tabulke\n", inputValue);
                        else
                            printf("Hodnota %d sa nenachadza v tabulke\n", inputValue);
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
        insert(size,hashTable,inputValue, inputValue);
        //Pripad kedy zvacsujeme tabulku
        if((checkSize(size, hashTable))==1){
            int *tempTable = malloc(sizeof(int)*size);
            initHashTable(size, tempTable);
            for(int i=0;i<size;i++){
                tempTable[i]=hashTable[i];
            }
            hashTable = realloc(hashTable, sizeof(int)*(size*2));
            initHashTable(size*2,hashTable);
            for(int i=0;i<size;i++){
                insert((size*2), hashTable, tempTable[i], tempTable[i]%(size*2));
            }
            size*=2;
        }
    }
    return 0;
}