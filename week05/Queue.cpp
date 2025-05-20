#include<iostream>
#include<fstream>
using namespace std;
struct NODE
{
    int key;
    NODE *p_next;
};
struct Queue
{
    NODE *p_head;
    NODE *p_tail;
};
// khai bao
Queue *initializeQueue();
void enequeue(Queue &q, int key);
int dequeue(Queue &q);
int size(Queue q);
bool isEmpty(Queue q);
void printQueue(Queue &q, ofstream &ofs);
void freeQueue(Queue *&q);
// dinh nghia
Queue *initializeQueue()
{
    Queue *q = new Queue();
    q->p_head = nullptr;
    q->p_tail = nullptr;
    return q;
}
void enequeue(Queue &q, int key)
{
    NODE *newnode = new NODE();
    newnode->key = key;
    newnode->p_next = nullptr;
    if (isEmpty(q))
    {
        q.p_head = newnode;
        q.p_tail = newnode;
        return;
    }
    q.p_tail->p_next = newnode;
    q.p_tail = newnode;
}
int dequeue(Queue &q)
{
    if (isEmpty(q))
    {
        cout << "Empty" << endl;
        return -1;
    }
    NODE *cur = q.p_head;
    int val = cur->key;
    q.p_head = q.p_head->p_next;
    delete cur;
    return val;
}
int size(Queue q)
{
    if (isEmpty(q))
    {
        return 0;
    }
    int count = 0;
    NODE *cur = q.p_head;
    while (cur != nullptr)
    {
        count++;
        cur = cur->p_next;
    }
    return count;
}
bool isEmpty(Queue q)
{
    return q.p_head == nullptr;
}
void printQueue(Queue &q, ofstream &ofs)
{
    if (isEmpty(q))
    {
        ofs << "EMPTY" << endl;
        return;
    }
    NODE *cur = q.p_head;
    while (cur != nullptr)
    {
        ofs << cur->key << " -> ";
        cur = cur->p_next;
    }
    ofs << "NULL" << endl;
}
void freeQueue(Queue *&q)
{
    if (q == nullptr) return;
    NODE *cur = q->p_head;
    while (cur != nullptr)
    {
        NODE *temp = cur;
        cur = cur->p_next;
        delete temp;
    }
    delete q;
    q = nullptr;
}
int main()
    {
        Queue *q;
        string command;
        ifstream ifs;
        ofstream ofs;
    
        ifs.open("input1.txt");
        ofs.open("output1.txt");
    
        if (ifs.is_open())
        {
            while (ifs >> command)
            {
                if (command == "init")
                {
                    q = initializeQueue();
                    printQueue(*q, ofs);
                }
                else if (command == "enqueue")
                {
                    int key;
                    ifs >> key;
                    enequeue(*q, key);
                    printQueue(*q, ofs);
                }
                else if (command == "dequeue")
                {
                    dequeue(*q);
                    printQueue(*q, ofs);
                }
                else if (command == "size")
                {
                    ofs << "Size: " << size(*q) << endl;
                }
            }
        }
        ofs.close();
        return 0;
}