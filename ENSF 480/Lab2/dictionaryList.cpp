/*
* File Name: dictionaryList.cpp
* Assignment: Lab 2 Exercise A
* Lab section: B02
* Completed by: Gerardo Garcia de Leon
* Development Date: Sept 20, 2023
*/
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include "dictionaryList.h"
#include "mystring_B.h"

using namespace std;

Node::Node(const Key& keyA, const Datum& datumA, Node *nextA)
  : keyM(keyA), datumM(datumA), nextM(nextA)
{
}

DictionaryList::DictionaryList()
  : sizeM(0), headM(0), cursorM(0)
{
}

DictionaryList::DictionaryList(const DictionaryList& source)
{
  copy(source);
}

DictionaryList& DictionaryList::operator =(const DictionaryList& rhs)
{
  if (this != &rhs) {
    destroy();
    copy(rhs);
  }
  return *this;
}

DictionaryList::~DictionaryList()
{
  destroy();
}

int DictionaryList::size() const
{
  return sizeM;
}

int DictionaryList::cursor_ok() const
{
  return cursorM != 0;
}

const Key& DictionaryList::cursor_key() const
{
  assert(cursor_ok());
  return cursorM->keyM;
}

Datum& DictionaryList::cursor_datum() const
{
  assert(cursor_ok());
  return cursorM->datumM;
}

void DictionaryList::insert(const int& keyA, const Mystring& datumA)
{
  // Add new node at head?                                                                                  
  if (headM == 0 || keyA < headM->keyM) {
    headM = new Node(keyA, datumA, headM);
    sizeM++;
  }
	
  // Overwrite datum at head?                                                                               
  else if (keyA == headM->keyM)
    headM->datumM = datumA;
	
  // Have to search ...                                                                                     
  else {
      
    //POINT ONE
		
    // if key is found in list, just overwrite data;                                                        
    for (Node *p = headM; p !=0; p = p->nextM)
		{
			if(keyA == p->keyM)
			{
				p->datumM = datumA;
				return;
			}
		}
		
    //OK, find place to insert new node ...                                                                 
    Node *p = headM ->nextM;
    Node *prev = headM;
		
    while(p !=0 && keyA >p->keyM)
		{
			prev = p;
			p = p->nextM;
		}
		
    prev->nextM = new Node(keyA, datumA, p);
    sizeM++;
  }
  cursorM = NULL;
	
}

void DictionaryList::remove(const int& keyA)
{
    if (headM == 0 || keyA < headM -> keyM)
        return;
    
    Node *doomed_node = 0;
    
    if (keyA == headM-> keyM) {
        doomed_node = headM;
        headM = headM->nextM;
        
        // POINT TWO
    }
    else {
        Node *before = headM;
        Node *maybe_doomed = headM->nextM;
        while(maybe_doomed != 0 && keyA > maybe_doomed-> keyM) {
            before = maybe_doomed;
            maybe_doomed = maybe_doomed->nextM;
        }
        
        if (maybe_doomed != 0 && maybe_doomed->keyM == keyA) {
            doomed_node = maybe_doomed;
            before->nextM = maybe_doomed->nextM;
        }
        
        
    } 
    if(doomed_node == cursorM)
        cursorM = 0;
    
    delete doomed_node;           // Does nothing if doomed_node == 0.
    sizeM--;
}

void DictionaryList::go_to_first()
{
    cursorM = headM;
}

void DictionaryList::step_fwd()
{
    assert(cursor_ok());
    cursorM = cursorM->nextM;
}

void DictionaryList::make_empty()
{
    destroy();
    sizeM = 0;
    cursorM = 0;
}

ostream& operator <<(ostream& os, DictionaryList& rhs) //This is the implementation of the binary operator << as a non-member function
{
	rhs.go_to_first();
	while(rhs.cursor_ok()){
		os << rhs.cursor_key() << " " << rhs.cursor_datum() <<endl;
		rhs.step_fwd();
	}
	return os;
}


const char* DictionaryList::operator [](int index) //This is the implementation of the binary operator [] as a member function
{
	this->go_to_first();
	assert(index >= 0 && index < this->size());
	for (int i = index; i > 0; i--)
	{
		this->step_fwd();
	}
	
	return this->cursor_datum().c_str();
}

// The following function are supposed to be completed by the stuents, as part
// of the exercise B part II. the given fucntion are in fact place-holders for
// find, destroy and copy, in order to allow successful linking when you're
// testing insert and remove. Replace them with the definitions that work.

void DictionaryList::find(const Key& keyA)
{
	if(headM == 0){
		cout << "There is no list to search" << endl;
		exit(1);
	}
	
	for(Node* ptr = headM; ptr != 0; ptr = ptr ->nextM){
		if(keyA == ptr -> keyM){ //If keyA matches the value held by the current nodes's keyM, set cursorM to that node
			cursorM = ptr;
			return;
		}
	}
	cursorM = NULL; //We didn't find a key, so set to null
}


void DictionaryList::destroy()
{
  while(headM != 0){
	  Node* temp = headM;
	  headM = headM -> nextM;
	  delete temp;
  }
  
  headM = 0; //headM should already be 0 after the while loop, but just to be safe we set it to zero
}


void DictionaryList::copy(const DictionaryList& source)
{
  if(source.headM == 0){
	  this -> headM = 0;
	  this -> cursorM = 0;
	  this -> sizeM = 0;
	  return;
  }
  
  this -> headM = new Node (source.headM -> keyM, source.headM -> datumM, nullptr); //Creating the first node
  Node* next_src_node = source.headM -> nextM;
  Node* next_cpy_node = this -> headM;
  
  while(next_src_node != 0){ //As long as there's nodes to copy
	  next_cpy_node -> nextM = new Node(next_src_node -> keyM, next_src_node -> datumM, nullptr);
	  next_cpy_node = next_cpy_node -> nextM;
	  next_src_node = next_src_node -> nextM;
  }
  
  this -> sizeM = source.sizeM; //Copying the size
  
  if(source.cursorM == 0){ // If there is no cursor set, we set our copy's cursor to 0
	  this -> cursorM = 0;
  }
  else{ // We use two iterators going at the same speed to stop when we find the source cursor. I'm sure there is a more efficient way of doing this but I can't think of it
	  Node* src_cursor = source.headM;
	  Node* cpy_cursor = this -> headM;
	  
	  while(src_cursor != source.cursorM){
		  src_cursor = src_cursor -> nextM;
		  cpy_cursor = cpy_cursor -> nextM;
	  }
	  this -> cursorM = cpy_cursor;
  }
}


