/*
    Created by: Hector Soto
    This is a circular doubly linked list template with functionality
    to work as different data structures.
*/
#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#define LL_TAIL -1 //If you insert at -1, the data will be inserted at the end as the new tail.

namespace ll //Linked list namespace
{
    template <class Type>
    class LinkedList
    {
        public:
            LinkedList() //CONSTRUCTOR
            {

            }
            ~LinkedList() //DESTRUCTOR
            {
                while(Remove(0)); //Remove all nodes.
            }
            //Linked List functions.
            void Insert(Type NewData, int Index) //Inserts new data at given position.
            {
                if(Head)
                {
                    Node *temp = Head;
                    Node *NewNode = new Node;
                    NewNode->Data = NewData;
                    if(Index == LL_TAIL)
                    {
                        if(Tail == Head)
                        {
                            Tail = NewNode;
                            Head->Next = Tail;
                            Head->Previous = Tail;
                            Tail->Next = Head;
                            Tail->Previous = Head;
                        }
                        else
                        {
                            Tail->Next = NewNode;
                            NewNode->Previous = Tail;
                            Tail = NewNode;
                            Tail->Next = Head;
                            Head->Previous = Tail;
                        }
                    }
                    else
                    {
                        if(Index >= 0) //Positive
                        {
                            for(int i = 0; i < Index; ++i)
                            {
                                temp = temp->Next;
                            }
                        }
                        else //Negative
                        {
                            for(int i = 0; i > Index; --i)
                            {
                                temp = temp->Previous;
                            }
                        }
                        NewNode->Previous = temp->Previous;
                        NewNode->Next = temp;
                        temp->Previous->Next = NewNode;
                        temp->Previous = NewNode;
                        if(temp == Head)
                        {
                            Head = NewNode;
                            Tail->Next = Head;
                        }
                    }
                }
                else
                {
                    Head = new Node;
                    Head->Data = NewData;
                    Head->Next = Head;
                    Head->Previous = Head;
                    Tail = Head;
                }
                ++Size;
            }
            bool Remove(int Index) //Returns false if list is empty.
            {
                if(Head)
                {
                    if(Index == LL_TAIL) //To ensure LL_TAIL use is consistent.
                    {
                        Index = Size - 1;
                    }
                    Node *temp = Head;
                    if(Index >= -1) //Positive + Tail;
                    {
                        for(int i = 0; i < Index; ++i)
                        {
                            temp = temp->Next;
                        }
                    }
                    else //Negative
                    {
                        for(int i = 0; i > Index; --i)
                        {
                            temp = temp->Previous;
                        }
                    }
                    if((temp == Head) && (temp == Tail))
                    {
                        Head = nullptr; Tail = nullptr;
                    }
                    else if(temp == Head)
                    {
                        Head = Head->Next;
                        Head->Previous = Tail;
                        Tail->Next = Head;
                        if(Head == Tail)
                        {
                            Head->Next = Head;
                        }
                    }
                    else if(temp == Tail)
                    {
                        Tail = Tail->Previous;
                        Tail->Next = Head;
                        Head->Previous = Tail;
                    }
                    else
                    {
                        temp->Previous->Next = temp->Next;
                        temp->Next->Previous = temp->Previous;
                    }
                    delete temp;
                    --Size;
                    return true;
                }
                return false;
            }
            Type Get(int Index)
            {
                Type ReturnData;
                if(Head)
                {
                    if(Index == LL_TAIL) //To ensure LL_TAIL use is consistent.
                    {
                        Index = Size - 1;
                    }
                    Node *temp = Head;
                    if(Index >= -1) //Positive + Tail;
                    {
                        for(int i = 0; i < Index; ++i)
                        {
                            temp = temp->Next;
                        }
                    }
                    else //Negative
                    {
                        for(int i = 0; i > Index; --i)
                        {
                            temp = temp->Previous;
                        }
                    }
                    ReturnData = temp->Data;
                }
                return ReturnData;
            }
            //Stack functions.
            void Push(Type NewData) //Wrapper of Insert(). For stacks.
            {
                Insert(NewData, 0);
            }
            Type Pop(int Index) //Will pop data from the list at the given index. For stacks.
            { //Same as Remove() except it will return data removed.
                Type ReturnData; //Return data will be uninitialized.
                if(Head)
                {
                    if(Index == LL_TAIL) //To ensure LL_TAIL use is consistent.
                    {
                        Index = Size - 1;
                    }
                    Node *temp = Head;
                    if(Index >= -1) //Positive + Tail;
                    {
                        for(int i = 0; i < Index; ++i)
                        {
                            temp = temp->Next;
                        }
                    }
                    else //Negative
                    {
                        for(int i = 0; i > Index; --i)
                        {
                            temp = temp->Previous;
                        }
                    }
                    if((temp == Head) && (temp == Tail))
                    {
                        Head = nullptr; Tail = nullptr;
                    }
                    else if(temp == Head)
                    {
                        Head = Head->Next;
                        Head->Previous = Tail;
                        Tail->Next = Head;
                        if(Head == Tail)
                        {
                            Head->Next = Head;
                        }
                    }
                    else if(temp == Tail)
                    {
                        Tail = Tail->Previous;
                        Tail->Next = Head;
                        Head->Previous = Tail;
                    }
                    else
                    {
                        temp->Previous->Next = temp->Next;
                        temp->Next->Previous = temp->Previous;
                    }
                    ReturnData = temp->Data;
                    delete temp;
                    --Size;
                }
                return ReturnData;
            }
            //Queue Functions
            void Enqueue(Type NewData) //Wrapper of Insert(). For queues.
            {
                Insert(NewData, 0);
            }
            Type Dequeue() //Wrapper of Pop(). For queues.
            {
                return Pop(LL_TAIL);
            }
            int Length() //Returns the size or length of the list in node amount.
            {
                return Size;
            }
        private:
            struct Node //Node structure used for list.
            {
                Type Data; //Data held in each node.
                Node *Next = nullptr;
                Node *Previous = nullptr;
            };

            Node *Head = nullptr; //Node at the start of the list.
            Node *Tail = nullptr; //Node at the end of the list.
            int Size = 0; //Amount of nodes in the list.
    };
}

#endif // LINKEDLIST_H_INCLUDED
