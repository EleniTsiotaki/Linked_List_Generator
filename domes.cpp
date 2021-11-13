#include <iostream>
#include <random>
#include <functional> 
using namespace std;

class Node //we create a class for the node of every linked list containing its data and its pointer for the next node.
{
	public:
		int data;
		Node* next; 
};

Node *newNode(int data) 
{
    Node *new_node = new Node;//we create a new object node
    new_node->data = data;//we insert the data to the node
    new_node->next = NULL;//and then the pointer for the next node is set to NULL
    return new_node; 
}

Node* insertEnd(Node* head, int data) //inserts new node and data
{	
	if (head == NULL)//if the list is empty
	    return newNode(data);//we create the first node using newNode
	else
	    head->next = insertEnd(head->next, data);//otherwise we insert a node to the next adress using the pointer head->next
	return head;

}

void deleteList(Node** head_ref) //delete a whole list
{
    //deref head_ref to get the real head 
    Node* current = *head_ref; //we get the current head 
    Node* next = NULL; //and we set the next pointer to NULL
 
    while (current != NULL) //while the current pointer is not null, meaning until we reach the end of the list
    {
        next = current->next; //we get the next pointer
        free(current); //and we delete it
        current = next;//and the current head becomes the next pointer
    }

    //deref head_ref to affect the real head back in the caller. 
    *head_ref = NULL;
}

void traverse(Node* head)//prints the linked list
{
    while (head != NULL) //until we reach the end of the list
    {
        cout << head->data << "->"; //we print the data of each list...
        head = head->next; //...and the pointer head moves every time to the next node until we reach the end of the list
    }
    cout << "NULL" << endl; //when we reach the end of the list we display NULL
}


void insert(Node** root, int item) //insert a new node in the Output List.
{
    Node* temp = new Node; //we create a new objet node
    Node* ptr; //we create a pointer for the node
    temp->data = item; //the data contains a number that we will find in "Output"
    temp->next = NULL; //we set the pointer of the next node to null
  
    if (*root == NULL) //if the root pointer is null, we are at the start of the list...
        *root = temp; //...so the root pointer now contains the pointer of the first node
    else 
    {
        ptr = *root; //we set to ptr the current pointer
        while (ptr->next != NULL)//until we reach the end of the list
            ptr = ptr->next; //we insert a new node
        ptr->next = temp; //and then we point to the next node 
    }
}

Node *Output(int numbers[51], int k) //create the Output list.
{
	Node *root = NULL; //we set the first pointer to NULL.
   	for (int i = 0; i < 51; i++) //for each possible element that can appear from the data_element_distribution
    {
		if (numbers[i]>=(k+1)/2){insert(&root,i);} //if a value in the numbers array is greater than or equal to half of the number of lists the user asked(after we round it up with k+1)...
                                                   //...then we insert a new node to the Output list, where the data is the index number of the array that value was found.
   	}
   return root;
}

int main(){
	int k,i,size,element; 
	int numbers[51] = {};//this creates an array of 51 int values, each initialized with a value of zero, representing a counter
	int temp[51] = {};//another array of 51 int values that will help us to store the values of numbers[51], if needed.
	cout << "Enter the number of linked lists: " <<endl;//we ask the user the number of lists they want
	cin >> k; //and we insert it to the variable k

	default_random_engine gen; //generates random number 
    uniform_int_distribution<int> list_size_distribution(1,50); //list size number
    uniform_int_distribution<int> data_element_distribution(0, 50); //each data element of the list
    auto random_list_size = bind(list_size_distribution, gen); //function for the random list size number
	auto random_element = bind(data_element_distribution, gen); //function for the random data element
	
	Node* head = NULL;
	size = random_list_size(); //we use random_list_size to declare the size of each list
	cout << "Size: "<< size << endl;
	for (int i=1; i < k+1; i++)//for each linked list
    {
		if (i != 1){
    		deleteList(&head); //head is passed by reference because deleteList has "**"
		}
		for (int j=0; j < size; j++) //for each node of the linked list
        { 
			element = random_element(); //we use random_element to declare the element of each node
			head = insertEnd(head, element); //we insert a new node containing the current head, element and size of the list
		}
		cout << "Linked list " << i << ":" << endl;
		traverse(head); //display the current linked list
		
		while (head!=NULL) //until we reach the end of the list
		{
			numbers[head->data]+=1;//the index number of the array is the element of each node, and we use its value as a counter for the times they show up
			head = head->next;//the pointer head moves every time to the next node until we reach the end of the list
		}
		
		for (int i=0; i < 51; i++){ 
			if (numbers[i] > 0 ){ // checks if the number i is in a node (or more) of the list
				temp[i] += 1; // if it is, we increase temp[i]
				numbers[i] = 0; // because we will have to check the next list
			}
		}
		
		size = random_list_size(); //we declare a new size for the next list
		if (i != k){cout << endl << "Size: "<< size << endl;}
	}
	
	for (int i=0; i<51; i++){
		numbers[i] = temp[i]; // we pass to numbers the final temp array so as to save the frequency of every number in the linked lists
	}
	
	Node* root = Output(numbers,k); //we create the requested Output list, using the numbers array and the number of lists the user asked
	cout << endl << "Output list: " ;
	traverse(root); //we display the Output list

	return 0;
}

