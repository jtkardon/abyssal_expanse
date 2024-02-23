#include "ObjectList.h"

df::ObjectList::ObjectList()
{
	count = 0;
}

// Insert object pointer in list.
	// Return 0 if ok, else -1.
int df::ObjectList::insert(Object* p_o)
{
	if (isFull())
		return -1;
	p_obj[count] = p_o;
	count++;
	return 0;
}

// Remove object pointer from list.
	// Return 0 if found, else -1.
int df::ObjectList::remove(Object* p_o)
{
	for (int i = 0; i < count; i++) {
		if (p_obj[i] == p_o) {
			for (int j = i; j < count - 1; j++)
				p_obj[j] = p_obj[j + 1];
			count--;
			return 0; 
		}
	}
	return -1; 
}

// Clear list (setting count to 0).
void df::ObjectList::clear()
{
	count = 0;
}

// Return count of number of objects in list.
int df::ObjectList::getCount() const
{
	return count;
}

// Return true if list is empty, else false.
bool df::ObjectList::isEmpty() const
{
	return count == 0;
}

// Return true if list is full, else false.
bool df::ObjectList::isFull() const
{
	return count >= MAX_OBJECTS;
}
