#include <iostream>
#include <fstream>
using namespace std;
struct NODE
{
    int key;
    NODE *p_next;
};
struct Stack
{
    NODE *top;
};
// khai bao
Stack *initializeStack();
void push(Stack &s, int key);
int pop(Stack &s);
int size(Stack s);
bool isEmpty(Stack s);
void printStack(Stack &s);
// dinh nghia
Stack *initializeStack()
{
    Stack *st = new Stack();
    st->top = nullptr;
    cout << "EMPTY" << endl;
    return st;
}
void push(Stack &s, int key)
{
    NODE *newnode = new NODE();
    newnode->key = key;
    newnode->p_next = nullptr;
    if (isEmpty(s))
    {
        s.top = newnode;
        return;
    }
    newnode->p_next = s.top;
    s.top = newnode;
}
int pop(Stack &s)
{
    if (isEmpty(s))
    {
        cout << "Empty" << endl;
        return -1;
    }
    NODE *cur = s.top;
    int val = cur->key;
    s.top = s.top->p_next;
    delete cur;
    return val;
}
int size(Stack s)
{
    if (isEmpty(s))
    {
        return 0;
    }
    int count = 0;
    NODE *read = s.top;
    while (read)
    {
        count++;
        read = read->p_next;
    }
    return count;
}
bool isEmpty(Stack s)
{
    return s.top == nullptr;
}
void printStack(Stack &s, ofstream &ofs)
{
    if (isEmpty(s))
    {
        ofs << "Stack: EMPTY" << endl;
        return;
    }
    NODE *read = s.top;
    ofs << "Stack:" << endl;
    while (read != nullptr)
    {
        ofs << read->key << endl;
        read = read->p_next;
    }
}

int main()
{
    Stack *s;
    string command;
    ifstream ifs;
    ofstream ofs;
    ifs.open("input.txt");
    ofs.open("output.txt");
    if(!ofs.is_open())
    {
        cout << "Error opening file" << endl;
        return 1;
    }
    if (ifs.is_open())
    {
        while (ifs >> command)
        {
            if (command == "init")
            {
                s = initializeStack();
                printStack(*s, ofs);
            }
            else if (command == "push")
            {
                int key;
                ifs >> key;
                push(*s, key);
                printStack(*s, ofs);
            }
            else if (command == "pop")
            {
                pop(*s);
                printStack(*s, ofs);
            }
        }
    }
    else
    {
        cout << "Error opening file" << endl;
    }
    ifs.close();
    ofs.close();
    delete s;
}
