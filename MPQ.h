#ifndef MPQ_H_
#define MPQ_H_
#include <iostream>
#include <vector>

using namespace std;

template <class comparable>
struct MPQ_node
{
	comparable height;
	int label;
	MPQ_node(int l,comparable h): label(l), height(h){}
	MPQ_node() :label(0),height()
	{}
};

template <class comparable>
class MPQ
{
public:
	explicit MPQ(int capacity = 100);

	bool isFull(); // returns true if full
	bool IsEmpty(); // return true if empty
	comparable  findMax(); // return maximum element in the heap

	void insert(const comparable &x, int label); // insert element to heap
	int deleteMax(comparable label); // remove
	
private:
	int currentsize; // size of vec_height array
	vector<MPQ_node<comparable>> vec_height;
	vector<MPQ_node<comparable>> vec_label;
	void percolateDown(int hole);
};

template<class comparable>
MPQ<comparable>::MPQ(int capacity)
{
	vec_height.resize(capacity + 1);
	vec_label.resize(10000);
	currentsize = 0;
	for (int i = currentsize / 2; i > 0; --i)
		percolateDown(i);
}

template<class comparable>
bool MPQ<comparable>::isFull()
{
	if (vec_height.size() == currentsize + 1)
		return true;
	else
		return false;
}

template<class comparable>
comparable  MPQ<comparable>::findMax()
{
	return vec_height[1].height;
}

template<class comparable>
void MPQ<comparable>::insert(const comparable & x,int label)
{
	if (isFull())
	{
		vec_height.resize(vec_height.size() * 2);
	}

	int hole = ++currentsize;
	MPQ_node<comparable> copy(label, x);
	for (; x < vec_height[hole / 2].height&&hole!=1; hole /= 2)
	{
		vec_height[hole] = vec_height[hole / 2];
		vec_label[vec_height[hole].label] = vec_height[hole];
		vec_label[vec_height[hole].label].label = hole;
	}
	vec_height[hole] = copy;
	vec_label[vec_height[hole].label] = vec_height[hole];
	vec_label[vec_height[hole].label].label = hole;
}
template<class comparable>
void MPQ<comparable>::percolateDown(int hole)
{
	int child;
	MPQ_node<comparable> tmp = vec_height[hole];

	for (; hole * 2 <= currentsize; hole = child)
	{
		child = hole * 2;
		if (child != currentsize && vec_height[child + 1].height < vec_height[child].height)
			child++;  // child is the minimum of the children
		if (vec_height[child].height < tmp.height)
		{
			vec_height[hole] = vec_height[child];
			vec_label[vec_height[hole].label] = vec_height[hole];
			vec_label[vec_height[hole].label].label = hole;
		}
		else
			break;
	}
	vec_height[hole] = tmp;
	vec_label[vec_height[hole].label] = vec_height[hole];
	vec_label[vec_height[hole].label].label = hole;
}
template<class comparable>
int MPQ<comparable>::deleteMax(comparable label)
{
	MPQ_node<comparable> temp;
	int x = vec_label[label].label;
	temp = vec_height[x];
	vec_height[x] = vec_height[currentsize--];
	vec_label[vec_height[x].label] = vec_height[x];
	vec_label[vec_height[x].label].label = x;
	percolateDown(x);
	return temp.height;
}
template<class Comparable>
bool MPQ<Comparable>::IsEmpty()
{
	return currentsize == 0;
}
#endif
