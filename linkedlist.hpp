//Author: Logan Markley
//Class: CS1575
//Semester: Fall 2022
//Due Date: Mon, 11/7/22

using namespace std;

//START - big 3 member functions ----- DONE

template <class T>
LinkedList<T>::~LinkedList()
{
    clear();
    delete m_head;
    m_head = NULL;
}

template <class T>
const LinkedList<T>& LinkedList<T>::operator= (const LinkedList<T>& rhs)
{
    clear();

    LLNode<T>* rpRHS = rhs.m_head;    //pointer for RHS
    while(m_size != rhs.m_size)
    {
        insert_back(rpRHS -> m_data);
        rpRHS = rpRHS -> m_next;
    }
    rpRHS = NULL;

    return *this;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& rhs)
{
    m_size = 0;
    m_head = new LLNode<T>;

    LLNode<T> * rpRHS = rhs.m_head;    //pointer for RHS
    while(m_size != rhs.m_size)
    {
        insert_back(rpRHS -> m_data);
        rpRHS = rpRHS -> m_next;
    }
    rpRHS = NULL;
}

//END - auxiliary functions -----



//START - basic accessor operations ----- DONE

template <class T>
int LinkedList<T>::size() const
{
    return m_size;
}

template <class T>
bool LinkedList<T>::isEmpty() const
{
    if( m_size == 0 )
        return true;
    else
        return false;
}

template <class T>
LLNode<T>* LinkedList<T>::getFirstPtr()
{
    if( isEmpty() ) //if empty return NULL
        return NULL;
    else
        return m_head;
}

template <class T>
LLNode<T>* LinkedList<T>::getAtPtr(int i)
{
    if( i<0 || i>=m_size)
        return NULL;
    else
    {
        LLNode<T>* runningPtr = m_head;  //running pointer to traverse array until index i is reached
        for(int k=0; k<i; k++) //k is equivalent to the node index
        {
            runningPtr = runningPtr -> m_next;
        }
        return runningPtr;
    }
}

//END - basic accessor operations -----



//START - basic mutator operations ----- DONE

template <class T>
void LinkedList<T>::clear()
{
    LLNode<T>* tmp = m_head -> m_next;
    for(int i=0; i<m_size; i++)
    {
        delete m_head;
        m_head = tmp;
        tmp = m_head -> m_next;
    }
    m_size = 0;
    tmp = NULL;
    return;
}

template <class T>
void LinkedList<T>::insert_front(const T& x)
{
    LLNode<T>* tmp = m_head;
    m_head = new LLNode<T>;
    m_head -> m_data = x;
    m_head -> m_next = tmp;
    tmp = NULL;
    m_size++;
    return;
}

template <class T>
void LinkedList<T>::insert_back(const T& x)
{
    LLNode<T>* rp = m_head;
    while(rp -> m_next != NULL) //get rp to the sentinel
    {
        rp = rp -> m_next;
    }
    rp -> m_data = x; //turn current sentinel into x
    rp -> m_next = new LLNode<T>; //add sentinel to end
    rp = NULL;
    m_size++;
    return;
}

template <class T>
void LinkedList<T>::insert(const T& x, LLNode<T>* pos)
{
    LLNode<T>* rp = m_head;
    while(rp -> m_next != pos)
    {
        rp = rp -> m_next;
    }
    rp -> m_next = new LLNode<T>;
    rp = rp -> m_next;
    rp -> m_data = x;
    rp -> m_next = pos;
    rp = NULL;
    m_size++;
    return;
}

template <class T>
void LinkedList<T>::remove_front()
{
    LLNode<T>* tmp = m_head -> m_next;
    delete m_head;
    m_head = tmp;
    tmp = NULL;
    m_size--;
    return;
}

template <class T>
void LinkedList<T>::remove_back()
{
    LLNode<T>* rp = m_head;
    LLNode<T>* tmp = rp -> m_next; //tmp is one element in front of rp
    for(int i=0; i<m_size-2; i++) //get rp to one before the back and tmp onto the back
    {
        rp = rp -> m_next;
        tmp = rp -> m_next;
    }
    rp -> m_next = tmp -> m_next; //make second to last element m_next point to the sentinel
    delete tmp; //delete last element
    rp = NULL;
    tmp = NULL;
    m_size--;
    return;
}

template <class T>
void LinkedList<T>::remove(LLNode<T>* pos)
{
    LLNode<T>* rp = m_head;
    while(rp -> m_next != pos)
    {
        rp = rp -> m_next;
    }
    rp -> m_next = pos -> m_next;
    delete pos;
    rp = NULL;
    m_size--;
    return;
}

//END - basic mutator operations



//START - complex mutator operations ----- DONE

template <class T>
bool LinkedList<T>::operator== (const LinkedList<T>& rhs) const
{
    if(m_size != rhs.m_size)
        return false;

    LLNode<T>* leftSidePTR = m_head;
    LLNode<T>* rightSidePTR = rhs.m_head;
    for(int i=0; i<m_size; i++)
    {
        if( (leftSidePTR -> m_data) != (rightSidePTR -> m_data) ) //if not same data values, stop comparing
        {
            leftSidePTR = NULL;
            rightSidePTR = NULL;
            return false;
        }
        else //if they are the same, keep iterating through and checking
        {
            leftSidePTR = leftSidePTR -> m_next;
            rightSidePTR = rightSidePTR -> m_next;
        }
    }
    leftSidePTR = NULL;
    rightSidePTR = NULL;
    return true;
}

template <class T>
LLNode<T>* LinkedList<T>::find(const T& x)
{
    LLNode<T>* tmp = m_head;
    for(int i=0; i<m_size; i++)
    {
        if(tmp -> m_data == x)
            return tmp;
        else
            tmp = tmp -> m_next;
    }
    tmp = NULL;
    return tmp;
}

template <class T>
void LinkedList<T>::reverse()
{
    LLNode<T>* tmp = m_head;
    LLNode<T>* next = NULL;
    LLNode<T>* prev = new LLNode<T>; //make a new Node that will be the new sentinel
    while(tmp -> m_next != NULL)
    {
        next = tmp -> m_next;
        tmp -> m_next = prev;
        prev = tmp;
        tmp = next;
    }
    delete tmp; //deletes the old sentinel
    m_head = prev;
    tmp = NULL;
    next = NULL;
    prev = NULL;
    return;
}

template <class T>
void LinkedList<T>::append(const LinkedList<T>& l2)
{
    LLNode<T>* rp = l2.m_head;
    for(int i=0; i<l2.m_size; i++) //this for loop adds every element from l2 onto this list
    {
        insert_back(rp -> m_data);
        rp = rp -> m_next;
    }
    rp = NULL;
    return;
}

template <class T>
void LinkedList<T>::slice(const LinkedList<T>& l2, LLNode<T>* start, LLNode<T>* stop)
{
    clear(); //clear this list
    LLNode<T>* rp = l2.m_head;
    while(rp != start)
    {
        rp = rp -> m_next;
    }
    while(rp != stop)
    {
        insert_back(rp -> m_data);
        rp = rp -> m_next;
    }
    rp = NULL;
    return;
}

//END - complex mutator operations -----



template <class T>
std::ostream& operator << (std::ostream& out, const LinkedList<T>& list)
{
    out << "[ ";
    LLNode<T>* rp = list.m_head;
    for(int i=0; i<list.m_size; i++)
    {
        out << rp -> m_data << ", ";
        rp = rp -> m_next;
    }
    out << "]";
    rp = NULL;
    return out;
}
