#ifndef UNIQUEARRYLMP_H
#define UNIQUEARRYLMP_H

/*
UniqueArray c'tor
INPUT:
	unsigned int size - max size of element* array
*/
template <class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(unsigned int size):
	max_size(size), cur_size(0){
	element_arr = new Element* [max_size];
	index_arr = new bool [max_size];
	for (int i = 0; i < max_size; i++) {
		index_arr[i] = false;
	}
	//compareElenets is automaticly the given compare class
}

/*
UniqueArray copy c'tor
INPUT:
	const UniqueArray& other - source uniquearray
*/
template <class Element, class Compare>
UniqueArray<Element, Compare>::UniqueArray(const UniqueArray& other): 
	max_size(other.max_size), cur_size(other.cur_size) {
	element_arr = new Element * [max_size];
	index_arr = new bool[max_size];
	for (int i = 0; i < max_size; i++) {
		if (other.index_arr[i]) {
			element_arr[i] = new Element(*(other.element_arr[i]));
		}
		index_arr[i] = other.index_arr[i];
	}
}

/*
UniqueArray d'tor
*/
template <class Element, class Compare>
UniqueArray<Element, Compare>::~UniqueArray() {
	for (unsigned int i = 0; i < max_size; i++) {
		if (index_arr[i]) {
			delete element_arr[i];
		}
	}
	delete[] element_arr;
	delete[] index_arr;
}

/*
insert: inserts given element into
INPUT:
	const Element& element - ref to element
OUTPUT:
	returns element index
*/
template <class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::insert(const Element& element) {
  
	
	//checking if in array
	unsigned int index = 0;
	if (getIndex(element, index) != false) {
		return index;
	}

	//checks for "full" exception
	else if (cur_size == max_size) {
		throw UniqueArrayIsFullException();
	}
	
	//else, inserts
	getFirstEmptyIndex(index);
	element_arr[index] = new Element(element);
	cur_size++;
	index_arr[index] = true;
	return index;
}

/*
getIndex: inserts index of element into given reference
INPUT:
	const Element& element - ref to element
	unsigned int& index - ref to "future element index"
OUTPUT:
	returns true if element in array and false if not
	changes given index accordingly
*/
template <class Element, class Compare>
bool UniqueArray<Element, Compare>::
getIndex(const Element& element, unsigned int& index) const{
	for (unsigned int i = 0; i < max_size; i++) {
		if (index_arr[i] && compareElements(*(element_arr[i]), element)) {
			index = i;
			return true;
		}
	}
	return false;
}

/*
operator[]: returns element from UniqueArray
INPUT:
	const Element& element - reference to element 
OUTPUT:
	returns the requested *element from UniqueArray
*/
template <class Element, class Compare>
const Element* UniqueArray<Element, Compare>::
operator[] (const Element& element) const{
	unsigned int index = 0;
	if (getIndex(element, index) == true) {
		return element_arr[index];
	}
	//else
	return nullptr;
}

/*
remove: removes element 
INPUT:
	const Element& element - reference to element
OUTPUT:
	returns true if was removed, else returns false
*/
template <class Element, class Compare>
bool UniqueArray<Element, Compare>::
remove(const Element& element) {
	
	//checking if in array
	unsigned int index = 0;
	if (getIndex(element, index) == false) {
		return false;
	}

	//else, removes
	delete element_arr[index];
	cur_size--;
	index_arr[index] = false;
	return true;
}

/*
getCount: returns cur_size value
*/
template <class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::getCount() const {
	return cur_size;
}

/*
getSize: returns max_size value
*/
template <class Element, class Compare>
unsigned int UniqueArray<Element, Compare>::getSize() const {
	return max_size;
}

//FILTER
template <class Element, class Compare>
UniqueArray<Element, Compare> UniqueArray<Element, Compare>::
filter(const Filter& f) const {
	UniqueArray<Element, Compare> filtered_UniqueArray(*this);
	for (unsigned int i = 0; i < max_size; i++) {
		if (index_arr[i] && !f(*element_arr[i])) {
			filtered_UniqueArray.remove(*(element_arr[i]));
		}
	}
	return filtered_UniqueArray;
}

/**
 * @tparam Element
 * @tparam Compare
 * @return The index of the first empty place
 */
template <class Element, class Compare>
bool UniqueArray<Element, Compare>::getFirstEmptyIndex(unsigned int& index)
const {
    for(int i = 0; i < max_size; i++) {
        if(index_arr[i] == false) {
			index = i;
			return true;
        }
    }
    return false;

}


/**
 * get the index_arr array
 * @tparam Element
 * @tparam Compare
 * @return bool* index_arr
 */
template <class Element, class Compare>
bool* UniqueArray<Element, Compare>::getIndexArr() const {
	return index_arr;
}


/**
 * get the element_arr array
 * @tparam Element
 * @tparam Compare
 * @return Element** element_arr
 */
template <class Element, class Compare>
Element** UniqueArray<Element, Compare>::getElementArr() const {
	return element_arr;
}
#endif //UNIQUEARRYLMP_H
