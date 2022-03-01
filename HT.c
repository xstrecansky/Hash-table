#include<stdio.h>
#include<stdlib.h>

#define SIZE 10
struct hash* hashTable[SIZE];

struct hash{
    int data;
    int key;
};
//Funkcia na pridanie hodnoty do tabulky
void insert(int key, int data){

}
//Funkcia na vypisanie hasovacej tabulky
void printHashTable(){
    for(int i=0;i<SIZE;i++){
        if(hashTable[i]!=NULL)
            printf(" (%d,%d)",hashTable[i]->key,hashTable[i]->data);
    }
}
//Funkcia na vratenie hodnoty
int returnKey(int key){
    return key%SIZE;
}
int main(){
    int i=0,j=0;
    int initValue, inputValue;
    printf("Vloz hodnotu do hasovacej tabulky\n");
    scanf("%d",&initValue);
    //insert();
    while(i==0){
        printf("Vloz dalsiu hodnotu do hasovacej tabulky\nAk vlozis %d, program skonci\n",initValue);
        scanf("%d",&inputValue);
        if(initValue==inputValue)
            while(j==0){
                printf("Vloz 1 ak chces vypisat hodnoty tabulky\nVloz 2 ak chces vymazat hodnotu v tabulky\nVloz 3 ak chces najst hodnotu v tabulke\nVloz 4 ak chces opat vlozit hodnoty tabulky\nVloz ine ak chces ukoncit program\n");
                scanf("%d",&inputValue);
                switch (inputValue){
                    case 1:
                        //vypiseme hodnoty
                        break;
                    case 2:
                        //vymazeme hodnoty
                        break;
                    case 3:
                        //najdeme hodnotu;
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
    return 0;
}