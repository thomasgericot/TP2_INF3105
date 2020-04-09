
#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#include "medicament_tree.h"




int avl_tree::height(avl* t)
{
    int h = 0;
    if (t != NULL)
    {
        int l_height = height(t->l);
        int r_height = height(t->droite);
        int max_height = max(l_height, r_height);
        h = max_height + 1;
    }
    return h;
}
int avl_tree::difference(avl* t)
{
    int l_height = height(t->l);
    int r_height = height(t->droite);
    int b_factor = l_height - r_height;
    return b_factor;
}
avl* avl_tree::rr_rotat(avl* parent)
{
    avl* t;
    t = parent->droite;
    parent->droite = t->l;
    t->l = parent;
    cout << "Right-Right Rotation";
    return t;
}
avl* avl_tree::ll_rotat(avl* parent)
{
    avl* t;
    t = parent->l;
    parent->l = t->droite;
    t->droite = parent;
    cout << "Left-Left Rotation";
    return t;
}
avl* avl_tree::lr_rotat(avl* parent)
{
    avl* t;
    t = parent->l;
    parent->l = rr_rotat(t);
    cout << "Left-Right Rotation";
    return ll_rotat(parent);
}
avl* avl_tree::rl_rotat(avl* parent)
{
    avl* t;
    t = parent->droite;
    parent->droite = ll_rotat(t);
    cout << "Right-Left Rotation";
    return rr_rotat(parent);
}

avl* avl_tree::insert(avl* r, string v)
{
    if (r == NULL)
    {
        r = new avl;
        r->nom = v;
        r->l = NULL;
        r->droite = NULL;
        return r;
    }
    else if (v < r->nom)
    {
        r->l = insert(r->l, v);
        r = balance(r);
    }
    else if (v >= r->nom)
    {
        r->droite = insert(r->droite, v);
        r = balance(r);
    } return r;
}

avl* avl_tree::balance(avl* t)
{
    int bal_factor = difference(t);
    if (bal_factor > 1)
    {
        if (difference(t->l) > 0)
            t = ll_rotat(t);
        else
            t = lr_rotat(t);
    }
    else if (bal_factor < -1)
    {
        if (difference(t->droite) > 0)
            t = rl_rotat(t);
        else
            t = rr_rotat(t);
    }
    return t;
}

void avl_tree::postorder(avl* t)
{
    if (t == NULL)
        return;
    postorder(t->l);
    postorder(t->droite);
    cout << t->nom << " ";
}

avl* avl_tree::trouverNomMedicament(avl* t,string NomMedicament)
{

    while (t !=NULL )
    {
        if (NomMedicament > t->nom)
        {
             trouverNomMedicament(t->droite, NomMedicament);
        }
        if(NomMedicament<t->nom)
        {
             trouverNomMedicament(t->l, NomMedicament);
        }
        if(NomMedicament==t->nom)
        {
            return t;
        }


    }
    if (t == NULL)
    {
        return NULL;
    }
}

