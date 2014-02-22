#include "vector_jar.h"
#include <iostream>

VectorJar::VectorJar()
{

}

VectorJar::VectorJar(int len) 
{
    for (int i = 0; i < len; i++)
    {
        vec.push_back(Marble());
    }
}
// finish other constructions and functions by yourself

VectorJar::VectorJar(const VectorJar& jar)
{
    vec.clear();
    for (int i = 0; i < jar.marble_number(); i++)
    {
        vec.push_back(jar.get_elem(i));
    }
}

const Marble& VectorJar::get_elem(int i) const
{
    // need to boundary check here before returning the marble element
    if (i <= vec.size()-1 && i >= 0)
        return vec[i];
}

void VectorJar::add(const Marble& m)
{
    vec.push_back(m);
}

void VectorJar::remove(const Marble& m)
{
    // iterate through for loop and find marble m, and then erase it, and break out of for loop
    if (vec.size() != 0)
        for (int i = 0; i < vec.size(); i++)
        {
            if (m == vec[i])
                vec.erase(vec.begin()+i);
            break;
        }
}

Marble VectorJar::remove_any()
{
    int rand_remove = 0;
    if (vec.size() >= 1)
    {
        rand_remove = rand()%vec.size();
        vec.erase(vec.begin()+rand_remove);
    }
}

void VectorJar::clear()
{
    if (vec.size() >= 1)
    {
        for (int i = 0; i < vec.size(); i++)
        {
            vec.pop_back();
        }
    }
}

bool VectorJar::is_empty() const
{
    if (vec.size())
        return false;
}

bool VectorJar::is_in_jar(const Marble& m) const
{
    if (vec.size() > 0)
    {
        for (int i = 0; i < vec.size(); i++)
        {
            if (m == vec[i])
                return true;
        }
    }
    return false;
}

int VectorJar::marble_number() const
{
    int count = 0;
    if (vec.size() > 0)
    {
        for (int i = 0; i < vec.size(); i++)
        {
            count++;
        }
    }
    return count;
}

int VectorJar::marble_nsize(Marble:: Size s) const
{
    int count = 0;
    if (vec.size() > 0)
    {
        for(int i = 0; i < vec.size(); i++)
        {
            if (s == vec[i].get_size())
                count++;
        }
    }
    return count;
}

int VectorJar::marble_ncolor(Marble:: Color c) const
{
    int count = 0;
    if (vec.size() > 0)
    {
        for(int i = 0; i < vec.size(); i++)
        {
            if (c == vec[i].get_color())
                count++;
        }
    }
    return count;
}

void VectorJar::merge(const Jar& jar1, const Jar& jar2)
{
    vec.clear();
    if ((jar1.marble_number() && jar2.marble_number()) > 0)
    {
        for (int i = 0; i < jar1.marble_number(); i++)
        {
            vec.push_back(jar1.get_elem(i));
        }
        for (int j = 0; j < jar2.marble_number(); j++)
        {
            vec.push_back(jar2.get_elem(j));
        }
    }
}

void VectorJar::intersection(const Jar& jar1, const Jar& jar2)
{
    vec.clear();
    if ((jar1.marble_number() > 0) && (jar2.marble_number() > 0))
    {
        for (int i = 0; i < jar1.marble_number(); i++)
        {
            for (int j = 0; j < jar2.marble_number(); j++)
            {
                if (jar1.get_elem(i) == jar2.get_elem(j))   
                    vec.push_back(jar2.get_elem(j));
            }
        }
        for (int k = 0; k < vec.size(); k++)
            for (int l = 0; l < vec.size(); l++)
            {
                if (vec[k] == vec[l] && l!=k)
                   vec.erase(vec.begin() + k);
            }
    }
    
}

void VectorJar::difference(const Jar& jar1, const Jar& jar2)
{
    vec.clear();
    if ((jar1.marble_number() > 0) && (jar2.marble_number() > 0))
    {
        for (int i = 0; i < jar2.marble_number(); i++)
        {
            for (int j = 0; j < jar1.marble_number(); j++)
            {
                if (!(jar2.get_elem(i) == jar1.get_elem(j)))
                    vec.push_back(jar1.get_elem(j));
            }
        }
    }
}

ostream& operator<<(ostream& os, const VectorJar& jar)
{   
    if (jar.marble_number() > 0)
        for (int i = 0; i < jar.marble_number(); i++)
        {
            Marble m = jar.get_elem(i);
            os << m << endl;
        }
    return os;
}

