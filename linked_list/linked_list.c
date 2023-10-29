#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct people{
    char name[50];
    int age;
    char gender;
    char cpf[12];
    char phone[12];
    struct people *next;
}people;

//global
int option;
people *start=NULL, *new_person;

void clear_memory(){
    people *clear_person;
    while(start!=NULL){
        clear_person=start;
        start=start->next;
        free(clear_person);
        clear_person=NULL;
    }
}

people* person_search(){
    people *person=start;
    char person_cpf[12];
    printf("\nEnter the registered individual's CPF: ");
    scanf("%s", person_cpf);
    while(person!=NULL){
        if(strcmp(person_cpf, person->cpf)==0){
            return person;
        }
        person=person->next;
    }
    printf("\nUnregistered person.\n");
    return NULL;
}

void dequeue(){
    people *dequeue_person=start;
    if(start!=NULL){
        start=start->next;
        printf("\nCaller:\nName: %s |Age: %d |Gender: %c |CPF: %s |Phone: %s\n", dequeue_person->name,
        dequeue_person->age, dequeue_person->gender, dequeue_person->cpf, dequeue_person->phone);
        free(dequeue_person);
        dequeue_person=NULL;
    }else{
        printf("\nRegister at least one person.\n"); 
    }
}

void delete(){
    people *person_delete=person_search();
    people *current_person=start;
    if(person_delete!=NULL){
        if(person_delete==start){
            start=start->next;
        }else{
            while(current_person->next!=person_delete){
                current_person=current_person->next;
            }
            current_person->next = person_delete->next;
        }
        if(person_delete->next==NULL){//To prevent the pointer (*new_person) from becoming NULL
            new_person=current_person;
        }
        free(person_delete);
        person_delete=NULL;
        printf("\nPerson sucessfully deleted.\n");
    }
}

void modify(){
    people *person_modify=person_search();
    int choice;
    if(person_modify!=NULL){
        do{
            printf("\nName: %s |Age: %d |Gender: %c |CPF: %s |Phone: %s\n", person_modify->name,
            person_modify->age, person_modify->gender, person_modify->cpf, person_modify->phone);
            
            printf("\n1-Change name\n2-Change age\n3-Change gender\n4-Change CPF\n5-Change phone\n0-Save\n\nOption: ");
            scanf("%d", &choice);
            if(choice!=0){
                switch(choice){
                    case 1:
                        printf("\nName: ");
                        scanf("%s", person_modify->name);
                        break;
                    case 2:
                        printf("Age: ");
                        scanf("%d", &person_modify->age);
                        break;
                    case 3:
                        printf("Gender: ");
                        scanf(" %c", &person_modify->gender);
                        break;
                    case 4:
                        printf("CPF: ");
                        scanf("%s", person_modify->cpf);
                        break;
                    case 5:
                        printf("Phone: ");
                        scanf("%s", person_modify->phone);
                        break;
                    default:
                        printf("\nPlease enter a valid choice.\n");
                }
            }
        }while(choice!=0);
    }
}

void search(){
    people *person=person_search();
    if(person!=NULL){
        printf("\nName: %s |Age: %d |Gender: %c |CPF: %s |Phone: %s\n", person->name,
        person->age, person->gender, person->cpf, person->phone);
    }
}

void display_people(){
    people *current_person=start;
    while(current_person!=NULL){
        printf("\nName: %s |Age: %d |Gender: %c |CPF: %s |Phone: %s\n", current_person->name,
        current_person->age, current_person->gender, current_person->cpf, current_person->phone);
        current_person=current_person->next;
    }
    if(start==NULL){
        printf("\nRegister at least one person.\n");
    }
}

void register_person(){
    if(start==NULL){
    new_person=(people*)calloc(1, sizeof(people));
    if(new_person==NULL){
        printf("\nError in allocating memory!\n");
        exit(1);
    }
    start=new_person; 
    }else{
    new_person->next=(people*)calloc(1, sizeof(people));
    if(new_person->next==NULL){
        printf("\nError in allocating memory!\n");
        exit(1);
    }
    new_person=new_person->next;
    }
    printf("Name: ");
    scanf("%s", new_person->name);
    printf("Idade: ");
    scanf("%d", &new_person->age);
    printf("Sexo: ");
    scanf(" %c", &new_person->gender);
    printf("CPF: ");
    scanf("%s", new_person->cpf);
    printf("Telefone: ");
    scanf("%s", new_person->phone);
    new_person->next=NULL;
}

int main(void){
    do{
        printf("\n1-Register\n2-Dispplay\n3-Search\n4-Modify\n5-Delete\n6-Dequeue\n0-Encerrar\n\nOption: ");
        scanf("%d", &option);
        if(option!=0){
            switch(option){
                case 1:
                    register_person();
                    break;
                case 2:
                    display_people();
                    break;
                case 3:
                    search();
                    break;
                case 4:
                    modify();
                    break;
                case 5:
                    delete();
                    break;
                case 6:
                    dequeue();
                    break;
                default:
                    printf("\nPlease enter a valid choice.\n");
            }
        }
    }while(option!=0);
    clear_memory();
    return 0;
}