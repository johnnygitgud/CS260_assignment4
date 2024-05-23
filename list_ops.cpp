#include <iostream>


//Using struct for simple public access to singly linked list creation
struct Node {
    int data;
    Node* next;
};
//Linked list class will hold methods for adding, removing, and getting elements.
class LinkedList {
    //Pointers for head and tails. They are empty at their declaration. Other functions will work with them to add and remove elements.
    Node* head;
    Node* tail;
    //Public constructor for linked list. It will initialize head and tail to nullptr. The syntax used is an initializer list.
public:
    LinkedList() : head(nullptr), tail(nullptr) {}

//Not conventional..Ideally this should not be made public and printing the list can be done in the class. However I wanted to practice accessing the head pointer from the main function.
public:
    Node* getHead() {
        return head;
    }

    //Begining of the add method. It will add a new node to the linked list. The function will take two parameters, The "data" for the new node will be in value and position will be used for indexing.
    //The function is not intended to return anything. Therefore it is declared with void
    void add(int value, int position) {
        Node* newNode = new Node();//newNode becomes the variable we can use to add a new node to the linked list. This syntax is a simple way of creating a new node.
        newNode->data = value;//Initialize data pointer of newNode to the value parameter.
        newNode->next = nullptr;//Initialize next pointer of newNode to nullptr.

    //Conditionals for the add fuction.
        if (head == nullptr) {
            //When the head is empty which is "nullptr" the new node will be the head and tail of the linked list.
            head = newNode;
            tail = newNode;
        } 
        // If the head is not empty then the new node will be added to the end of the linked list.
        else {
            Node* temp = head;// First we need the temp variable to point to the head of the linked list.
            //This loop executes only after the first node is created and it is intended to adjust the link in between nodes.
            // First the iterator is set to 0 because we need it to alwasy be lst than the postion parameter.
            // The position must be 1 less than the orginal positon to make sure we are the previous node to the position we want to add the new node. This is because the previous postion needs a link to the next node.
            // Both conditions need to be true for the loop to continue. 
            for (int i = 0; i < position - 1 && temp->next != nullptr; i++) {
                //The temp node is set to the next node in the linked list.
                temp = temp->next;
            }
            newNode->next = temp->next;//At first newNode was pointing to nullptr. In this line newNode->next is set to the node that follows after temp.
            temp->next = newNode; // Insert the new new node to the linked list by updating the next pointer of node currently pointed by temp..
            if (newNode->next == nullptr) {
                //if the next node is empty it becomes the tail. 
                tail = newNode;
            }
        }
    }
    //Remove method will remove a node from the linked list. The function will take one parameter, the position of the node to be removed.
    int remove(int position) {
        if (head == nullptr) {
            //Since the first index is 0 of any list, -1 represents an empty list.
            return -1;
        }

        Node* temp = head;//head is updated to the second node in the linked list.
        //Condition applies for when there is only one node in the linked list.
        if (position == 0) {
            head = temp->next;
            int removedData = temp->data;//store data from the node to be deleted
            delete temp; //delete the node that temp is pointing to. Not the data itself
            return removedData; //return the data of the deleted node.
        }
        //This loop is to help remove a node that is not at the beginning of the linked list.
        //the data for temp is checked to make sure it is not empty and the iterator position has to be one position less than the position parameter.
        for (int i = 0; temp != nullptr && i < position - 1; i++) {
            //when the conditions above are ment temp can be moved to the next node
            temp = temp->next;
        }

        //This condition checks that either the current or the next node are empty.
        if (temp == nullptr || temp->next == nullptr) {\
            //If either one is empty, the function will return -1.
            return -1;
        }
        // This section removes the actual node from the list.
        Node* next = temp->next->next;
        int removedData = temp->next->data;
        delete temp->next;
        temp->next = next;
        return removedData;
    }
    //This method can provide the position of the linked list. ***Note all lists start at 0.
    int get(int position) {
        Node* temp = head; //temp pointer to get the head of the linked list.
        //The loop conditions check that temp does not reach an empty node and it that the iterator is less than the position parameter.
        for (int i = 0; temp != nullptr && i < position; i++) {
            //If the conditions are met temp will be updated to the next node.
            temp = temp->next;
        }
        //If the temp node is empty, out of bounds, or negative, etc the function will return -1.
        if (temp == nullptr) {
            return -1;
        }

        return temp->data;
    }
};


//Tests with a main function

int main() {
    LinkedList list;
    list.add(1, 0);
    list.add(2, 1);
    list.add(3, 2);

 // Print the list after adding elements
    Node* temp = list.getHead();
    std::cout << "List after adding elements: ";
    while (temp != nullptr) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
    std::cout << "Element at position 0: " << list.get(0) << std::endl;
    std::cout << "Element at position 1: " << list.get(1) << std::endl;
    std::cout << "Element at position 2: " << list.get(2) << std::endl;
    list.remove(1);
    std::cout << "Element at position 1 after removal: " << list.get(1) << std::endl;
    list.add(4, 20);

    // Print the list after adding and removing elements
    // Print the list after adding elements
    Node* temp2 = list.getHead();
    std::cout << "List after adding elements: ";
    while (temp2 != nullptr) {
        std::cout << temp2->data << " ";
        temp2 = temp2->next;
    }
    return 0;
}