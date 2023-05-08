//stack.c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "stack.h"

IntStack *start = NULL;

// Stack Initialisieren
int stackInit(IntStack *self){

	if(start == NULL){
		if((self = malloc(sizeof(IntStack))) != NULL){ //allokiere speicher,
			self->top = (StackStruct *) NULL; //zeigt immer auf oberstes Element (StackStruct)
			start = self;
            self->count = 0;
			return 0;
		}else{
			fprintf(stderr,"stackInit(IntStack *self): Konnte keinen Speicher allokieren; errno: %d\n",errno);
			exit(-1);
		}
	}else{
		fprintf(stderr,"stackInit(IntStack *self): Stack wurde schon initialisiert \n");
		exit(-1);
	}
}

// Stack freigeben
void stackRelease(IntStack *self){

	while(self->count > 0){
		stackPop(self);
	}
	free(start);
	printf("stackRelease(IntStack *self): Stack wurde freigegeben\n");
}

// push
void stackPush(IntStack *self, int i){

	StackStruct *new;
	if((new = malloc(sizeof(StackStruct))) != NULL){
		new->data = i; //erstelle neue StackStruct
		new->next =  self->top;
		self->top = new; //ändere Top pointer des Stacks
		self->count++; //erhöhe Anzahl der gespeicherten Elemente
	}else{
		fprintf(stderr,"stackPush(IntStack *self, int i): Konnt keinen Speicher allokieren; errno: %d\n",errno);
		exit(-1);
	}
}

// top
int stackTop(const IntStack *self){

	if(self->count < 1){
		fprintf(stderr,"stackTop(IntStack *self): Der Stack ist leer\n");
		exit(-1);
	}else{
		return self->top->data;
		}
}

// pop
int stackPop(IntStack *self){
printf("called stackpop\n");
	if(self->count > 0){
		StackStruct *temp = self->top;
		int data = self->top->data;
		self->top = (StackStruct *) self->top->next; //setze Top Pointer auf das 2. oberste Element
		free(temp); //free das oberste Element
		self->count--;
		return data;

	}else{
		fprintf(stderr,"stackPop(IntStack *self): Der Stack ist leer\n");
		exit(-1);
	}
}

// is empty
int stackIsEmpty(const IntStack *self){

	if(self->count < 1){
		return 1;
	}else{
		return 0;
	}
}

// Ausgeben
void stackPrint(const IntStack *self){
	printf("called stackprint\n");

	if(self->count < 1){
		fprintf(stderr,"stackPrint nicht möglich. Der Stack ist leer\n");
		exit(-1);
	}
	long i = self->count;
	StackStruct *temp = self->top;
	while(i > 0){
		printf("wert: %d	stacknr: %d\n",temp->data,i--);
		temp = (StackStruct *) temp->next;
	}
}
/* Testen des Stacks
int main() {
	IntStack stack;

	if (stackInit(&stack) != 0)
		return -1;
	
	stackPush(&stack, 1);
	stackPush(&stack, 2);
	stackPush(&stack, 3);
	
	while (!stackIsEmpty(&stack))
		printf("%i\n", stackPop(&stack));
	
	stackPop(&stack);
	
	stackRelease(&stack);
	return 0;
}


 Erwartete Ausgabe:
3
2
1
<<Fehlermeldung, da IntStack leer>>

*/