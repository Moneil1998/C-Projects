#include <stdio.h>
#include <stdlib.h>
#include <string.h>

	struct Data {
		char title[50];
		char author[50];
		int stockNumber;
		float wholesalePrice;
		float retailPrice;
		int wholesaleQuantity;
		int retailQuantity;
	};

	typedef struct Node {
		struct Data book;
		struct Node *next;
	} Node;

void getDataAndBuildList(Node **headPtr);
Node *createNodeAndGetData(void);
void insert(Node **headPtr, Node *newNodePtr);
void delete(Node **headPtr, int prodNumberToDelete);
void getUserOption(Node **head);
double calculateTotalRevenue(const Node *head);
double calculateInvestmentInInventory(const Node *head);
double calculateTotalWholesaleCost(const Node *head);
double calculateTotalProfit(const Node *head);
int calculateTotalBooksSold(const Node *head);
double calculateAverageProfit(const Node *head);
void printList(const Node *head);
void freeAllNodes(Node **headPtr);

int main() {
	Node *head = NULL;
	getDataAndBuildList(&head);
	getUserOption(&head);
	return 0;
}

void getDataAndBuildList(Node **headPtr) {
	Node *newNodePtr;
	printf("Please enter data about the books.\n\n");
	while (newNodePtr = createNodeAndGetData()) {
		insert(headPtr, newNodePtr);
	}
}

Node *createNodeAndGetData(void) {
	Node *newNodePtr;
	newNodePtr = malloc (sizeof(Node));
	if (newNodePtr == NULL) {
		printf("Error: memory could not be allocated for enough nodes. ");
		printf("Terminating program!\n");
		exit (0);
	}
	else {
		scanf("%[^\n]", newNodePtr->book.title);
		if (strcmp(newNodePtr->book.title, "END_DATA") == 0) {
			/* free Node if end of book data detected */
			free(newNodePtr);			
			return NULL;
		}
		else {
			/* consume newline before author string */
			getchar();				
			scanf("%[^\n]s", newNodePtr->book.author);
			scanf("%i", &newNodePtr->book.stockNumber);
			scanf("%f", &newNodePtr->book.wholesalePrice);
			scanf("%f", &newNodePtr->book.retailPrice);
			scanf("%i", &newNodePtr->book.wholesaleQuantity);
			scanf("%i", &newNodePtr->book.retailQuantity);
			/* consume newline before next title string */
			getchar();				
		}
		return newNodePtr;
	}
}

/*
This function inserts new books into the list 

*/
void insert(Node ** headPtr, Node *newNodePtr) {
  Node * traversePtr;
  Node * priorNodePtr;
  traversePtr = *headPtr;
  if (*headPtr == NULL)
    {
      *headPtr = newNodePtr;
      newNodePtr->next=NULL;
      printf("Book stock number %d was added to the inventory\n",newNodePtr->book.stockNumber);
    }
  else if (newNodePtr->book.stockNumber<traversePtr->book.stockNumber)
    {
      newNodePtr->next=*headPtr;
      *headPtr = newNodePtr;
      printf("Book stock number %d was added to the inventory\n",newNodePtr->book.stockNumber);
    }
  else
    {
      priorNodePtr=traversePtr;
      traversePtr = traversePtr->next;
      while((traversePtr!=NULL) && (newNodePtr->book.stockNumber>traversePtr->book.stockNumber))
	{
	  priorNodePtr=traversePtr;
	  traversePtr = traversePtr->next;
	}
      newNodePtr->next=traversePtr;
      priorNodePtr->next=newNodePtr;
      printf("Book stock number %d was added to the inventory\n",newNodePtr->book.stockNumber);

    }

  
}
/*
This function gets the option the user wants to use and calls the repsective function
 */
void getUserOption(Node **headPtr) {
	int option;
	Node *newNodePtr;
	int bookNumToDelete;
	do {
		printf("\nPlease enter an integer between 1 and 9 to select an operation on the data:\n");
		scanf("%i", &option);
		getchar();
		switch (option){
			case 1:
				printList (*headPtr);
				break;
			case 2:
				printf("\nTotal revenue: %.2f\n", calculateTotalRevenue(*headPtr));
				break;
			case 3:
				printf("\nTotal wholesale cost: %.2f\n", calculateTotalWholesaleCost(*headPtr));
				break;
			case 4:
				printf("\nTotal investment in inventory: %.2f\n", calculateInvestmentInInventory(*headPtr));
				break;
			case 5:
				printf("\nTotal profit: %.2f\n", calculateTotalProfit(*headPtr)); 
				break;
			case 6:
				printf("\nTotal number of books sold = %i\n", calculateTotalBooksSold(*headPtr));
				break;
			case 7:
				printf("\nAverage profit: %.2f\n", calculateAverageProfit(*headPtr));
				break;
			case 8:		
				printf("\nPlease enter the data for the book you wish to add:\n\n");
				newNodePtr = createNodeAndGetData();
				insert(headPtr, newNodePtr);			
				break;
			case 9:
				printf("\nPlease enter the book stock number of the book you wish to delete, ");
				printf("followed by enter.\n");
				scanf("%i", &bookNumToDelete);
				delete (headPtr, bookNumToDelete);
				break;
			case 10:
				freeAllNodes(headPtr);
				break;
			default:
				printf("Valid option choices are 1 to 10. Please choose again!\n");
				break;
		} 
	} while (option != 10);
}

/*
This function calculate the total revenue and returns it


 */

double calculateTotalRevenue(const Node *head) { 
  double total = 0.0;
  Node *traversePtr;
  traversePtr=(Node*)head;
  while (traversePtr!=NULL){
    total += traversePtr->book.retailQuantity * traversePtr->book.retailPrice;
    traversePtr=traversePtr->next;
  }
  return total;
}

/*
This function calculates investment in inventory and returns it
 */
double calculateInvestmentInInventory(const Node *head) { 
  double invInInventory = 0.0;
  Node *traversePtr;
  traversePtr=(Node*)head;
  while (traversePtr!=NULL){
    invInInventory +=traversePtr->book.wholesalePrice*(traversePtr->book.wholesaleQuantity - traversePtr->book.retailQuantity);
    traversePtr=traversePtr->next;
  }
  return invInInventory;
}

/*
This function calculates total wholesale cost and returns it
 */
double calculateTotalWholesaleCost(const Node *head) { 

  double totalWhole = 0.0;
  Node *traversePtr;
  traversePtr=(Node*)head;
  while (traversePtr!=NULL){
    totalWhole += traversePtr->book.wholesaleQuantity * traversePtr->book.wholesalePrice;
    traversePtr=traversePtr->next;
  }
  return totalWhole;
}

/*
This function calculates total profit and returns it
 */
double calculateTotalProfit(const Node *head) { 
  double totalProfit;
  totalProfit = (calculateTotalRevenue(head)-calculateTotalWholesaleCost(head))+calculateInvestmentInInventory(head);
  return totalProfit;


}

/*
This function calculates total books sold and returns it
 */
int calculateTotalBooksSold(const Node *head) { 

  double booksSold = 0.0;
  Node *traversePtr;
  traversePtr=(Node*)head;
  while (traversePtr!=NULL){
    booksSold += traversePtr->book.retailQuantity;
    traversePtr=traversePtr->next;
  }
  return booksSold;
}

/*
This function calculates investment in inventoryaverage profit and returns it
*/
double calculateAverageProfit(const Node *head) {
  double avgProfit;
  avgProfit += calculateTotalProfit(head)/calculateTotalBooksSold(head);
  return avgProfit;
}

/*
This function deletes a book from the list
 */
void delete(Node ** headPtr, int stockNumToDelete) {
  Node *traversePtr;
  struct Node *priorNodePtr;
  traversePtr=*headPtr;
  if(traversePtr==NULL)
    {
      printf("\n ERROR: there are no nodes to delete\n");
    }
  else if (traversePtr->book.stockNumber == stockNumToDelete)
    {
      *headPtr=traversePtr->next;
      free(traversePtr);
      printf("\nBook stock number %d was deleted from the inventory\n",stockNumToDelete);
    }
  else
    {
      priorNodePtr=traversePtr;
      traversePtr=traversePtr->next;
      while(traversePtr!=NULL)
	{
	  if(traversePtr->book.stockNumber == stockNumToDelete)
	    {
	      priorNodePtr=traversePtr;
	      traversePtr=traversePtr->next;
	      priorNodePtr->next = traversePtr->next;
	      free(traversePtr);
	      printf("\nBook stock number %d was deleted from the inventory\n",stockNumToDelete);
	      return;
	    }
	  else
	    {
	      printf("\nError: Book stock number %d not found in the list!\n",stockNumToDelete);
	      return;
	    }
	}
    }		
}

/*
This function prints the books in the list
 */
void printList(const Node *head) {
	const Node *traversePtr = head;
	printf("\nBook list:\n");
	while (traversePtr != NULL) {		/* determine not at end of list */
		printf("%s\n", traversePtr->book.title); 
		traversePtr = traversePtr->next;
	}
	printf("\n");
}

/*
This function free all nodes called by calloc or malloc
 */
void freeAllNodes(Node **headPtr) {
	Node *traversePtr = *headPtr;
	Node *restOfListPtr = *headPtr;    
	while (restOfListPtr != NULL) {         /* determine list is not empty */
		restOfListPtr = restOfListPtr->next;
		free(traversePtr);
		traversePtr = restOfListPtr;
	}
	*headPtr = NULL; /* set headPtr back to NULL after space freed */
}

