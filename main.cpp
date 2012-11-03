#include <vector>
#include <string>
#include <iostream>
#include <string.h>
#include <sstream>
using namespace std;

/*
** Simple example... 
*/
vector<string> thisWorks1()
{
    vector<string> ret;
    ret.push_back("thisWorks1");
    return ret;
}


/*
** another simple example... pushing a local var... this actually works because
** the magic of push_back makes a copy, here is an excerpt from the docs:

void push_back ( const T& x );
Add element at the end
Adds a new element at the end of the vector, after its current last element. 
-------------------------------------------------------------
The content of this new element is initialized to a copy of x.
-------------------------------------------------------------

This is fine, and it makes working with vectors easy, but also consumes
extra CPU when making copies of long strings.

*/
vector<string> thisWorks2()
{
    vector<string> ret;
    string str = "thisWorks2";
    ret.push_back(str);
    return ret;
}

/*
** Simple example of pushing a bunch of stuff on to the vector
*/
vector<string> thisWorks3()
{
    vector<string> ret;

    string str = "thisWorks3 ";
    for (int x = 0; x < 10; x++)
    {
        ret.push_back(str);
        /*
        ** pushing the same local string var onto the vector makes multiple copies
        ** each copy will have an extra splat (*) appended to the end...
        */
        str.append("*");
    }
    return ret;
}

/*
** Just to show how to use "iterators"
*/
void printStr(vector<string> val)
{
    vector<string>::iterator it;
    /*
    ** begin() points to the first element in the vector
    ** end() points to the last element in the vector
    ** it++ increments the iterator pointer to the next element in the vector
    */
    for (it = val.begin(); it < val.end(); it++)
    {
        /* Then dereferencing the iterator gives you the current element */
        cout<< *it <<endl;
    }
}

/*
** Here is the same as above except with string*
*/
void printStrPtr(vector<string*> val)
{
    vector<string*>::iterator it;
    for (it = val.begin(); it < val.end(); it++)
    {
        /*
        ** here I just dereference the iterator and that gives me a string*
        */
        string* str;
        str = *it;
        /*
        ** so now I must dereference the string* to get the actual string
        */
        cout<< *str <<endl;
    }
}

/*
** Here is a slightly more complex example, but might be something else you are missing
** stringstreams!
*/
vector<string*> thisWorks4()
{
    vector<string*> ret;
    string *str;
    ostringstream strStream;
    /*
    ** think of this as shifting in the string "thisWorks4 "... or pushing "thisWorks4 " into the stream...
    */
    strStream<<"thisWorks4 ";
    for (int x = 0; x < 10; x++)
    {
        /* allocate a new string* */
        str = new string();
        /*
        ** shift in the value of x into the stream, the stuff that has already been pushed into the stream
        ** is still floating downstream, in otherwords this does not "clear" the stream
        ** so when you look at the resulting string, it is as if you are appending the value of x
        ** to the end of the string. I suspect that when building newick string the stringstream might
        ** be helpful...
        */
        strStream<< x ;
        /* copy the stream to a string* */
        *str = strStream.str();
        /* push the string* on to to vector */
        ret.push_back(str);
    }
    return ret;
}

/*
** Free the allocated string* from above
*/
void freeStrPtr(vector<string*> val)
{
    vector<string*>::iterator it;
    for (it = val.begin(); it < val.end(); it++)
    {
        string* tmp;
        tmp = *it;
        /* again dereferencing the iterator gives string* so now we must dereference the string* to print the string */
        cout<<"deleting: "<< *tmp <<endl;
        /*
        ** and here we dereference the iterator to get the string* which we then delete
        ** delete(tmp); would also work here, it is the exact same thing as delete(*it);
        */
        delete (*it);
    }
}

int main()
{
    vector<string> vecStr;
    vector<string*> vecStrPtr;

    vecStr = thisWorks1();
    cout<<vecStr[0]<<endl;

    vecStr = thisWorks2();
    cout<<vecStr[0]<<endl;

    vecStr = thisWorks3();
    printStr(vecStr);

    vecStrPtr = thisWorks4();
    printStrPtr(vecStrPtr);
    freeStrPtr(vecStrPtr);

    return 0;
}
