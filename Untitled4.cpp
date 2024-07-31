#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Node {
    char data[40];
    Node *next;
    Node *prev;
};

struct BSTNode {
    char data[40];
    BSTNode *left, *right;
};

char temp[40];
Node *head = NULL;
Node *current_node = NULL;
BSTNode *bstRoot = NULL;

BSTNode* createBSTNode(const char *data) {
    BSTNode *newNode = new BSTNode();
    
	strcpy(newNode->data, data);
    newNode->left = newNode->right = NULL;
    return newNode;
}


BSTNode* insertBST(BSTNode *node, const char *data)
 {
if (node == NULL) return createBSTNode(data);
if (strcmp(data, node->data) < 0) 
{
node->left = insertBST(node->left, data);
    } 
	else if (strcmp(data, node->data) > 0)
	 {
node->right = insertBST(node->right, data);
    }

    return node;
}

BSTNode* searchBST(BSTNode *root, const char *data) {
    if (root == NULL || strcmp(root->data, data) == 0)
        return root;
if (strcmp(data, root->data) < 0)
        return searchBST(root->left, data);

    return searchBST(root->right, data);
}

void insert(const char *song) {
    Node *new_node = new Node();
    
	strcpy(new_node->data, song);
    if (head == NULL)
	 {
        new_node->next = new_node->prev = new_node;
        head = current_node = new_node;
    } 
	else
	{
        Node *last = head->prev;
    new_node->prev = last;
    last->next = new_node;
    new_node->next = head;
        head->prev = new_node;
    }

    bstRoot = insertBST(bstRoot, song);  
}

void delete_element() 
{
    if (head == NULL)
	 {
        cout << "No Music is there to delete!" << endl;
        return;
    }
cout << "Enter Music Name to delete:" << endl;
cin.ignore();
cin.getline(temp, 40);
cout << endl;
Node *ptr = head;
do 
	{
if (ptr->next == ptr && strcmp(ptr->data, temp) == 0) {
cout << "One file deleted! Playlist is Empty Now!" << endl;
head = NULL;
    delete ptr;
    return;
        } 
else if (strcmp(ptr->data, temp) == 0) {
    Node *prev = ptr->prev;
    Node *next = ptr->next;
    prev->next = next;
            next->prev = prev;
            if (ptr == head) 
			{
                head = next;
    }
    delete ptr;
    cout << "Music deleted!" << endl;
        return;
        }
        ptr = ptr->next;
    }
	 while (ptr != head);
    cout << "No Music file is there!" << endl;
}

void show() {
    if (head == NULL)
	 {
        cout << "Playlist is Empty!" << endl;
        return;
    }
    Node *show_ptr = head;
    cout << endl;
    int i = 1;
    cout << "Displaying Playlist:" << endl;
    do {
    cout << "Song " << i << " : " << show_ptr->data << endl;
    i++;
    show_ptr = show_ptr->next;
    } while (show_ptr != head);
}

void next_node() {
    if (current_node == NULL) 
	{
    cout << "No songs in Playlist!" << endl;
    } 
	else 
	{
    current_node = current_node->next;
    cout << "Playing Next Song: " << current_node->data << endl;
    }
}

void prev_node() {
    if (current_node == NULL)
	 {
        cout << "No songs in Playlist!" << endl;
    }
	 else 
	{
    current_node = current_node->prev;
    cout << "Playing Previous Song: " << current_node->data << endl;
    }
}

void first_node() {
    if (head == NULL)
	 {
    cout << "Playlist is Empty!" << endl;
    } 
	else 
	{
    cout << "Playing First Music: " << head->data << endl;
    }
}

void last_node() {
    if (head == NULL) 
	{
    cout << "Playlist is Empty!" << endl;
    } 
	else
	 {
cout << "Playing Last Music: " << head->prev->data << endl;
    }
}

void specific_data() {
    if (head == NULL) {
cout << "No music is there to be searched!" << endl;
return;
    }
cout << "Enter Music Name to search:" << endl;
cin.ignore();
cin.getline(temp, 40);
cout << endl;
Node *ptr = head;
    do 
	{
        if (strcmp(ptr->data, temp) == 0)
		 {
            cout << "Music Found!" << endl;
            cout << "Playing Music: " << ptr->data << endl;
            return;
        }
        
ptr = ptr->next;
    } 
	while (ptr != head);
    cout << "There is no Music file with this name!" << endl;
}

void search_song_bst() {
    if (bstRoot == NULL)
	 {
        cout << "Playlist is Empty!" << endl;
        return;
    }
cout << "Enter Music Name to search:" << endl;
cin.ignore();
    cin.getline(temp, 40);
    cout << endl;

    BSTNode *result = searchBST(bstRoot, temp);
    if (result != NULL)
	 {
        cout << "Music Found: " << result->data << endl;
    } 
	else 
	{
    cout << "There is no Music file with this name!" << endl;
    }
}

void load_songs_from_file(const char* filename) {
ifstream infile(filename);
if (!infile)
	 {
    cout << "Could not open file!" << endl;
    return;
    }

while (infile.getline(temp, 40)) {
    insert(temp);
    }

    infile.close();
}

int main() {
    load_songs_from_file("songs.txt");

    int choice;
    while (true) {
        cout<<"\n-----Song Playlist-----\n";
        cout<<"1. Add Music\n";
        cout<<"2. Remove Music\n";
        cout<<"3. Show Playlist\n";
        cout<<"4. Play next file\n";
        cout<<"5. Play previous file\n";
        cout<<"6. Play first file\n";
        cout<<"7. Play Last file\n";
        cout<<"8. Play specific file\n";
        cout<<"9. Search using BST\n";
        cout<<"10. Exit\n\n";
        cin>>choice;

    switch (choice) {
    case 1:
        cout << "Enter Music Name:" << endl;
               cin.ignore();
        cin.getline(temp, 40);
            insert(temp);
    break;
    case 2:
        delete_element();
break;
    case 3:
        show();
    break;
    case 4:
    next_node();
    break;
    case 5:
        prev_node();
    break;
    case 6:
        first_node();
    break;
    case 7:
        last_node();
    break;
    case 8:
        specific_data();
    break;
    case 9:
        search_song_bst();
    break;
    case 10:
        return 0;
        default:
        cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
