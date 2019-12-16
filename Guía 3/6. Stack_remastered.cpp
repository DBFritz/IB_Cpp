#include <iostream>
#include <string>

#ifndef STACK3_H
#define STACK3_H

template <class T>
class Stack {
    struct Link {
        T data;
        Link* next;
        Link(T dat, Link* nxt){
            data = dat;
            next = nxt;
        }
        ~Link() {}
    }* head;
public:
    class Underflow { };
    Stack() { head = nullptr; }
    Stack(T * obj, int size) {
        head = nullptr; 
        for(int i=0; i<size;i++) push(obj[i]);
    }
    ~Stack() {
        while (head != nullptr) pop();
    }
    T push(T dat){
        head = new Link(dat, head);
        return dat;
    }
    T peek(){
        if ( head == nullptr )
            throw Underflow();
        return head->data;
    }
    T pop(){
        if( head == nullptr )
            throw Underflow();
        T result = head->data;
        Link* oldHead = head;
        head = head->next;
        delete oldHead;
        return result;
    }
};

#endif

int main()
{
    using namespace std;
    string mySentences[] = {"pepe", "de", "italia"};
    string ** myptrSentences = new string*[3];
    for (int i=0; i<3; i++)
        myptrSentences[i] = &mySentences[i];
    Stack<string *> myStack(*myptrSentences,3);
    return 0;
}
