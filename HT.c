#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void initHashTable(int size, int *hashTable){
    for(int i=0;i<size;i++){
        (hashTable)[i]=0;
    }
}
//Funkcia na vypisanie hodnot v tabulke
void printHashTable(int size, int *hashTable){
    for(int i=0;i<size;i++){
        if((hashTable)[i]==0)
            printf("%d\t---\n",i);
        else
            printf("%d\t%d\n",i,hashTable[i]);
    }
}
//Funkcia na vlozenie prvku do hashovacej tabulky
void insert(int size , int *hashTable, int data, int key){
    if(hashTable[key]==0)
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
    if(hashTable[key]==0)
        return 0;
    if(hashTable[key]==data)
        return 1;
    else{
        key++;
        if(key>=(size))
            key=0;
        search(size, hashTable, data, key);
    }
    return 1;
}
//funkcia na vymazanie prvku v tabulke
void delete(int size, int *hashTable, int data, int key){
    if(hashTable[key]==0)
        return;
    if(hashTable[key]==data){
        hashTable[key]=0;
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
int main(){
    printf("Ak chces testovat O(n) stlac 1\n");
    int test;
    scanf("%d",&test);
    if(test == 1){
        clock_t start;
        double time;
        int value;
        printf("Casova zlozitost HT SZ:\n\n");
        printf("Pocet Prvkov\t\t|Insert\t\t|Search\t\t|Delete\n");
        for(int i=1;i<=10;i++){
            int size=1000*i+1;
            int hashTable[size];
            initHashTable(size, (hashTable));
            printf("------------------------+---------------+---------------+--------\n");
            printf("%d\t\t\t", (1000*i));
            start=clock();
            //Testujeme insert
            for(int j=0;j<(1000*i);j++){
                value = random()%(1000*i);
                insert(size, hashTable, value, value%size);
            }
            //printf("cauko\n");
            time=(clock()-start)/(double)CLOCKS_PER_SEC;
            printf("|%f\t",time);
            //Testujeme search

            start=clock();
            for(int j=0;j<(1000*i);j++){
                value = random()%(1000*i);
                search(size, hashTable, value, value%size);
            }
            time=(clock()-start)/(double)CLOCKS_PER_SEC;
            printf("|%f\t",time);
            //Testujeme delete
            start=clock();
            for(int j=0;j<(1000*i);j++){
                value = random()%(1000*i);
                delete(size, hashTable, value, value%size);
            }
            time=(clock()-start)/(double)CLOCKS_PER_SEC;
            printf("|%f\n",time);
        }
        printf("-----------------------------------------------------------------\n");
        return 0;
    }
    int i=0,j=0, initValue, inputValue;
    printf("Vloz hodnotu do hasovacej tabulky\n");
    scanf("%d",&initValue);
    int size=1000+1;
    int hashTable[size];
    initHashTable(size, (hashTable));
    insert(size, hashTable, initValue, initValue%size);
    while(i==0){
        printf("Vloz dalsiu hodnotu do hasovacej tabulky\nAk vlozis %d, program skonci\n",initValue);
        scanf("%d",&inputValue);
        if(initValue==inputValue)
            while(j==0){
                printf("Vloz 1 ak chces vypisat hodnoty tabulky\nVloz 2 ak chces vymazat hodnotu v tabulky\nVloz 3 ak chces najst hodnotu v tabulke\nVloz 4 ak chces opat vlozit hodnoty tabulky\nVloz ine ak chces ukoncit program\n");
                scanf("%d",&inputValue);
                switch (inputValue){
                    case 1:
                        printHashTable(size, hashTable);
                        break;
                    case 2:
                        scanf("%d",&inputValue);
                        delete(size, hashTable, inputValue, inputValue%size);
                        break;
                    case 3:
                        scanf("%d",&inputValue);
                        if(search(size, hashTable, inputValue, inputValue%size))
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
        insert(size,hashTable,inputValue, inputValue);
    }
    return 0;
}