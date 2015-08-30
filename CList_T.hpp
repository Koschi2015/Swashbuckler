#ifndef TCLINKEDLIST_H
#define TCLINKEDLIST_H

template <class U>
struct St_Element
{
public:
    // Inhalt
    U* Object;
    // Vorgänger
    St_Element* Next;
    // Nachfolger
    St_Element* Prev;
};

template <class T>
class CTLinkedList
{
private:
    // ListenElemnet
    St_Element<T>* List;
    //
    int ElementCounter;
public:
    // Konstruktor
    CTLinkedList();
    // Destruktor
    ~CTLinkedList();
    // geht ein Element vor
    bool Prev();
    // geht ein Elemnet zurück
    bool Next();
    // geht zum ersten Elemnt der Liste
    void First() {while(Prev());}
    // geht zum letten Elemnt der Liste
    void Last() {while(Next());}
    // Fügt an erster stelle ein neues Element ein
    void Add_First(T Element);
    // Fügt am ende der Liste ein Element ein
    void Add_Last(T Element);
    // Fügt ein Element vor dem Aktuellen Element ein
    void Insert_Befor(T Element);
    // Fügt ein Element hinter dem Aktuellen Element ein
    void Insert_After(T Element);
    // Löscht das Aktuelle Objekt
    bool Remove_Element();
    // Löscht die ganze Liste
    void Clear_List() {while(Remove_Element());}
    // Gibt den Inhalt des Elements zurück
    T Get_Object();
    // Gibt zurück ob die Liste Leer ist oder nicht
    bool IsEmpty();
};
template < typename T >
CTLinkedList<T>::CTLinkedList()
{
    List = 0;
    ElementCounter = 0;
}
template < typename T >
CTLinkedList<T>::~CTLinkedList()
{
    Clear_List();
}
template < typename T >
bool CTLinkedList<T>::Prev()
{
    if(List->Prev)
    {
        List = List->Prev;
        return true;
    }
    return false;
}
template < typename T >
bool CTLinkedList<T>::Next()
{
    if(List->Next)
    {
        List = List->Next;
        return true;
    }
    return false;
}
template < typename T >
void CTLinkedList<T>::Add_First(T Element)
{
    if(List == 0)
    {
        List = new St_Element<T>;
        List->Object = new T;
        List->Next = 0;
        List->Prev = 0;
        *List->Object = Element;
    }
    else
    {
        First();
        List->Prev = new St_Element<T>;
        List->Prev->Next = List;
        List->Prev->Prev = 0;
        *List->Prev->Object = Element;
        List = List->Prev;
    }
}
template < typename T >
void CTLinkedList<T>::Add_Last(T Element)
{
    if(List == 0)
    {
        List = new St_Element<T>;
        List->Object = new T;
        List->Next = 0;
        List->Prev = 0;
        *List->Object = Element;
    }
    else
    {
        Last();
        List->Next = new St_Element<T>;
        List->Next->Prev = List;
        List->Next->Next = 0;
        *List->Next->Object = Element;
        List = List->Next;
    }
}
template < typename T >
void CTLinkedList<T>::Insert_Befor(T Element)
{
    if(List == 0)
    {
        List = new St_Element<T>;
        List->Object = new T;
        List->Next = 0;
        List->Prev = 0;
        *List->Object = Element;
    }
    else
    {
        St_Element<T>* Temp = new St_Element<T>;
        if(List->Prev)
        {
            Temp->Prev = List->Prev;
            Temp->Next = List;
            List->Prev = Temp;
            Temp->Prev->Next = Temp;
            *Temp->Object = Element;
        }
        else
        {
            Temp->Prev = 0;
            Temp->Next = List;
            List->Prev = Temp;
            *Temp->Object = Element;
        }
    }
}
template < typename T >
void CTLinkedList<T>::Insert_After(T Element)
{
    if(List == 0)
    {
        List = new St_Element<T>;
        List->Object = new T;
        List->Next = 0;
        List->Prev = 0;
        *List->Object = Element;
    }
    else
    {
        St_Element<T>* Temp = new St_Element<T>;
        if(List->Next)
        {
            Temp->Next = List->Next;
            Temp->Prev = List;
            List->Next = Temp;
            Temp->Next->Prev = Temp;
            *Temp->Object = Element;
        }
        else
        {
            Temp->Next = 0;
            Temp->Prev = List;
            List->Next = Temp;
            *Temp->Object = Element;
        }
    }
}
template < typename T >
bool CTLinkedList<T>::Remove_Element()
{
    if(List==0)
    {
        return false;
    }
    else
    {
        St_Element<T>* Temp = List;
        if(Temp->Next && Temp->Prev)
        {
            List = List->Next;
            Temp->Next->Prev = Temp->Prev;
            Temp->Prev->Next = Temp->Next;
            delete Temp->Object;
            delete Temp;
            Temp = 0;
            return true;
        }
        else if(Temp->Next == 0 && Temp->Prev)
        {
            List = List->Prev;
            delete Temp->Object;
            delete Temp;
            Temp = 0;
            List->Next = 0;
            return true;
        }
        else if(Temp->Next && Temp->Prev == 0)
        {
            List = List->Next;
            delete Temp->Object;
            delete Temp;
            Temp = 0;
            List->Prev = 0;
            return true;
        }
        else if (Temp->Next == 0 && Temp->Prev == 0)
        {
            delete List->Object;
            delete List;
            List = 0;
            Temp = 0;
            return true;
        }
        else
        {
            return false;
        }
    }
}
template < typename T >
T CTLinkedList<T>::Get_Object()
{
    if(List)
    {
        return List->Object;
    }
    else
    {
        return;
    }
}
template < typename T >
bool CTLinkedList<T>::IsEmpty()
{
    if(List)
    {
        return true;
    }
    return false;
}
#endif // TCLINKEDLIST_H
