// String splitter

#include "stringsplit.hpp"

using namespace std;

void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
  
  // Remove empty elems
  for(vector<string>::iterator it = elems.begin(); it != elems.end(); it++)
  {
    if((*it)[0] == delim)
    {
      // Remove empty entries
      it = elems.erase(it);
    }
  }
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

void split(char delim, vector<string>& elems)
{
  vector<string> newElems;
    
  for(vector<string>::iterator it = elems.begin(); it != elems.end(); it++)
  {
    if((*it) != "" && !(*it).empty())
    {
      // Split sub elements
      vector<string> temp = split((*it), delim);
      // Insert into new vector
      for(int i = 0; i < (int)temp.size(); i++)
      {
        newElems.push_back(temp[i]);
      }
    }
  }
    
  elems.assign( newElems.begin(), newElems.end());
}


vector<string> split(const string &s, char delim[]) {
  vector<string> elems;
  int i = 0;
  if(elems.empty())
  {
      split(s, delim[0], elems);
  }
  if(strlen(delim) > 1)
  {
      for(i = 1; i < (int)strlen(delim); i++)
      {
         split(delim[i], elems);
      }
  }
  return elems;
}
