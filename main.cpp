#include <iostream>
using namespace std;
struct node
{
    int user_id;
    string name;
    node *next;
};

struct ticket
{
    int user_id, ticket_id;
    string description;
    ticket *next;
};

node *head = NULL;
ticket *front = NULL;
ticket *rear = NULL;

ticket *resolved = new ticket[100];
int resolved_count = 0;
int resolved_capacity = 100;

bool id_exists(int id)
{
    node *temp = head;

    while (temp != NULL)
    {

        if (temp->user_id == id)
        {
            return true;
        }

        temp = temp->next;
    }

    return false;
}

void registration(string name, int id)
{

    if (id_exists(id))
    {
        cout << "This ID is already exists" << endl;
    }

    else if (head != NULL)
    {
        node *temp = head;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        node *new_node = new node;
        new_node->user_id = id;
        new_node->name = name;
        temp->next = new_node;
        new_node->next = NULL; 
        cout << "Registration succeed :) " << endl ;
        }

    else
    {
        node *new_node = new node;
        head = new_node;
        new_node->user_id = id;
        new_node->name = name;
        new_node->next = NULL;
        cout << "Registration succeed :) " << endl ;
    }
}

void enqueue_ticket(int user_id, int ticket_id, string description)
{
    ticket *new_ticket = new ticket;
    new_ticket->user_id = user_id;
    new_ticket->ticket_id = ticket_id;
    new_ticket->description = description;

    if (rear == NULL)
    {
        front = rear = new_ticket;
        new_ticket->next = NULL;
    }

    else
    {
        rear->next = new_ticket;
        rear = new_ticket;
        new_ticket->next = NULL;
    }
}

void submit_ticket()
{
    int user_id, ticket_id;
    string description;

    cout << "Enter user ID: ";
    cin >> user_id;

    if (id_exists(user_id))
    {
        cout << "Enter ticket ID: ";
        cin >> ticket_id;

        cout << "Please descripe your issue: " << endl;
        cin.ignore(); 
        getline(cin, description);

        enqueue_ticket(user_id, ticket_id, description);
        cout << "Ticket submitted successfully!" << endl;
    }

    else
    {
        cout << "This user ID isn't registerd " << endl;
    }
}

void resolve_ticket()
{
    if (front == NULL)
    {
        cout << "No tickets to resolve" << endl;
    }

    else
    {
        ticket *temp = front;
        front = front->next;

        if (front == NULL)
        {
            rear = NULL;
        }

        if (resolved_count < resolved_capacity)
        {
            resolved[resolved_count] = *temp;
            resolved_count++;
            cout << "Ticket resolved successfully " << endl;
        }

        else
        {
            cout << "Sorry resolved tickets array is full " << endl;
        }

        delete temp;
    }
}

void display()
{
    if (front == NULL)
    {
        cout << "No tickets to display" << endl;
        return;
    }

    ticket *temp = front;
    cout << "Current tickets: " << endl;

    while (temp != NULL)
    {
        cout << "User ID: " << temp->user_id << ", Ticket ID: " << temp->ticket_id << endl;
        cout << "Description: " << temp->description << endl;
        cout << "--------------------------" << endl;
        temp = temp->next;
    }
}

void search(int id)
{
    ticket *temp = front;
    bool found = false;

    while (temp != NULL)
    {
        if (temp->user_id == id || temp->ticket_id == id)
        {
            cout << "Ticket found in current tickets:" << endl;
            cout << "User ID: " << temp->user_id << ", Ticket ID: " << temp->ticket_id << endl;
            cout << "Description: " << temp->description << endl;
            cout << "Status: Pending" << endl;
            found = true;
            break;
        }

        temp = temp->next;
    }

    if (found == false)
    {
        for (int i = 0; i < resolved_count; i++)
        {
            if (resolved[i].user_id == id || resolved[i].ticket_id == id)
            {
                cout << "Ticket found in resolved tickets:" << endl;
                cout << "User ID: " << resolved[i].user_id << ", Ticket ID: " << resolved[i].ticket_id << endl;
                cout << "Description: " << resolved[i].description << endl;
                cout << "Status: Resolved" << endl;
                found = true;
                break;
            }
        }
    }

    if (found == false)
    {
        cout << "Ticket not found" << endl;
    }
}

int main()
{
    int choice;
    int id;
    string name;
    do
    {
        cout << "\n========== Ticket System Menu ==========" << endl;
        cout << "1. Register User" << endl;
        cout << "2. Submit Ticket" << endl;
        cout << "3. Resolve Ticket" << endl;
        cout << "4. Display Current Tickets" << endl;
        cout << "5. Search Ticket by ID" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter your name: ";
            cin >> name;
            cout << "Enter your ID: ";
            cin >> id;
            registration(name, id);
            break;

        case 2:
            submit_ticket();
            break;

        case 3:
            resolve_ticket();
            break;

        case 4:
            display();
            break;

        case 5:
            cout << "Enter user ID or ticket ID to search: ";
            cin >> id;
            search(id);
            break;
        case 6:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Try again!" << endl;
        }

    } while (choice != 6);

    return 0;
}
