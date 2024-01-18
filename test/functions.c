

#define LIMIT 100
void push()
{
	int stack[LIMIT], top, element;
	if(top == LIMIT- 1)
	{
		printf("Stack Overflow\n");
	}
	else
	{
		printf("Enter the element to be inserted:");
		scanf("%d", &element);
		top++;
		stack[top]=element;
	}
}

void pop()
{
	int stack[LIMIT], top, element;
	if(top == -1)
	{
		printf("Stack underflow\n");
	}
	else
	{
		element=stack[top];
		printf("The deleted item is %d\n",stack[top]);
		top--; // The element below the topmost element is deleted
	}
}


void display()
{
	int stack[LIMIT], top, i;
	if(top == -1)
	{
		printf("Stack underflow\n"); // Stack is empty
	}
	else if(top > 0)
	{
		printf("The elements of the stack are:\n");
		for(i = top; i >= 0; i--) // top to bottom traversal
		{
			printf("%d\n",stack[i]);
		}
	}
}
