#include "min_heap.h"
#include <iostream>
#include <vector>

using namespace std;

MinHeap::MinHeap()
{ }

Node* MinHeap::min()
{
  return m_array[0];
}

void MinHeap::add(Node* n)
{
  m_array.push_back(n); /*
  for (int i = 0; i < m_array.size(); ++i) {
    for (int j = 0; j <= i; ++j) {
      if(m_array[j]->fscore < m_array[i]->fscore) {
        Node* temp = m_array[j];
        m_array[j] = m_array[i];
        m_array[i] = temp; //Sorting for idiots!
      }
    }
  } */
  //Add function sorts list in ascending order by fscore
}

void MinHeap::remove(Node* n)
{
  for (int i = 0; i < m_array.size(); ++i) {
    if (m_array[i] == n) {
      m_array.erase(m_array.begin() + i);
      return;
    }
  }
}
void MinHeap::pop()
{
  m_array.erase(m_array.begin());
}

void MinHeap::print() const
{
  for(Node* n : m_array) {
    cout << "X: " << n->x << " Y: " << n->y << " GSCORE: " << n->gscore << " FSCORE: " << n->fscore << endl;
  }
}

int MinHeap::size() const
{
  return m_array.size();
}

