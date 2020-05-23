/*------------ hw1ie1.c -------------------------------------------------------------
      Program: homework 1
       Author: 강 혁 (KANG HYUK)
   Student ID: 12130919
      User ID: s12130919
       E-mail: k941026h@naver.com
 
     Creation: Nov.  11, 2019
 Modification: Nov.  11, 2019
     Due Date:
-------------------------------------------------------------------------------*/ 
#include <stdio.h>
#include <stdlib.h>
#define endOfFile 0
#define endOfLine 13
#define EOLN '\n'

enum nodetype {binop, unop, number};

struct node{
	enum nodetype tag;
	char bOperator, uOperator;
	int num;
	struct node *operand, *leftOperand, *rightOperand;
};

char savedChar = ' ';
/*********************************************************************
 	Prototypes for function
*********************************************************************/
struct node *term();
struct node *expr();
struct node *factor();

char getChar(void){
	char c;
	
	if(savedChar != ' '){
		c = savedChar;
		savedChar = ' ';
	}
	else if(savedChar == EOF){
		c = (char)(endOfFile);
	}
	else if(savedChar == EOLN){
		c = (char)(endOfLine);
	}
	else{
		c = getchar();
		printf("%c", c);
	}
	return(c);
}

void ungetChar(char c){
	if(savedChar == ' '){
		savedChar = c;
	}
	else{
		printf("%c can't unget more than one character at a time", c);
	}
}

char nextChar(void){
	char c;
	c = getChar();
	return(c);
}

int charToInt(char c){
	int charToINT;
	
	if(c < '0' || c > '9'){
		printf("charToint: %c is not a digit", c);
		charToINT = 0;
	}
	else{
		charToINT = (int)(c - '0');
	}
	return(charToINT);
}

int getNum(char c){
	int n;
	n = 0;
	do{
		n = 10 * n + charToInt(c);
		c = getChar();
	}while ('0' <= c && c <= '9');
	ungetChar(c);
	return(n);
}

struct node *binopNode(char opor, struct node *lopand, struct node *ropand){
	struct node *n;
	if(lopand == NULL || ropand == NULL){	
		n = NULL;
	}
	else{
		n = (struct node *)malloc(sizeof(struct node));
		n->tag = binop;
		n->uOperator = ' ';
		n->bOperator = opor;
		n->operand = NULL;
		n->leftOperand = lopand;
		n->rightOperand = ropand;
	}

	/*do something*/
	return(n);
}

struct node *unopNode(char opor, struct node *opand){
	struct node *n;
	
	if(opand == NULL){
		n = NULL;
	}
	else{
		n = (struct node *)malloc(sizeof(struct node));
		n->tag = unop;
		n->uOperator = opor;
		n->bOperator = ' ';
		n->operand = opand;
		n->leftOperand = n->rightOperand = NULL;
	}
	return(n);
}

struct node *numberNode(int i){
	struct node* n;
	
	n = (struct node *)malloc(sizeof(struct node));
	n->tag = number;
	n->num = i;
	n->leftOperand = n->rightOperand = n->operand = NULL;
	return(n);
}

void ptree(struct node *n, int depth){
	switch(n->tag){
	case binop:
		printf("%d, %c\n", depth, n->bOperator);
		ptree(n->leftOperand, depth + 2);
		ptree(n->rightOperand, depth + 2);
		break;
	case unop:
		printf("%d, %c\n", depth, n->uOperator);
		ptree(n->operand, depth + 2);
		break;
	case number:
		printf("%d, %d\n", depth, n->num);
		break;
	default:
		break;
	}
}

void PrintTree(struct node *n){
	printf("Parse Tree:\n");
	ptree(n, 0);
}

struct node *factor(void) {
	char c;
	struct node *Factor;
	int num;
	Factor = (struct node *)malloc(sizeof(struct node));
	
	c = nextChar();
	
	if('0' <= c && c <= '9'){
		num = getNum(c);
		Factor = numberNode(num);
	}
	else if(c == '-'){
		Factor = factor();
		Factor = unopNode(c, Factor);
	}
	else if(c == '('){
		Factor = expr();
		c = nextChar();
	}
	/* do something*/
	
	return(Factor);
}

struct node *term(void){
	char c;
	struct node *n, *Term;
	
	n = (struct node *)malloc(sizeof(struct node));	
	Term = (struct node *)malloc(sizeof(struct node));
	n = factor();
	c = nextChar();
	
	if(c == '*' || c == '/'){
		Term = term();
		Term = binopNode(c, n, Term);
	}
	else{
		savedChar = c;
		Term = n;
	}

	/*do something*/

	return(Term);
}

struct node *expr(void){
	char c;
	struct node *n, *Expr;
	
	n = term();
	c = nextChar();
	
	if(c == '+' || c == '-'){
		Expr = expr();
		Expr = binopNode(c, n, Expr);
	}
	else{
		savedChar = c;
		Expr = n;
	}
	/*do something*/

	return(Expr);
}

int eval(struct node *n){
	int op1, op2, EVAL;
	
	switch (n->tag){
	case binop:
		op1 = eval(n->leftOperand);
		op2 = eval(n->rightOperand);
		switch(n->bOperator){
		case '+':EVAL = op1 + op2; break;
		case '-':EVAL = op1 - op2; break;
		case '*':EVAL = op1 * op2; break;
		case '/':EVAL = op1 / op2; break;
		}
		break;
	case unop:
		EVAL = -eval(n->operand);
		break;		
	case number:
		EVAL = n->num;
		break;
	}
	return(EVAL);
}

int run(void){
	struct node *n;
	
	n = NULL;
	printf("> ");
	n = expr();
	if(n != NULL){
		printf("\n");
		PrintTree(n);
		printf("\n");
		printf("Result = %d\n", eval(n));
	}
	return 0;
}

void main(void){
	printf("\n\tMy calculator: \n");
	printf("\tEnter an arithmetic expression and hit <RETURN>.\n");
	printf("\tI will print a parse tree and evaluate the expression.\n");

	run();
}

/*************************************** End of file***************************************/
