#include <stdio.h>
#include "stack.h"
#include "stack.c"

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


/* Erwartete Ausgabe:
3
2
1
<<Fehlermeldung, da IntStack leer>>
*/
