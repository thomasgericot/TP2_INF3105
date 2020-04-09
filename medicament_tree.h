
#if !defined(__MEDICAMENT_TREE_H__)
#define __MEDICAMENT_TREE_H__

using namespace std;
struct avl
{
    string nom;


    struct avl* l;
    struct avl* droite;
};

class avl_tree
{
public:
    
    avl* balance(avl*);
    int height(avl*);
    int difference(avl*);
    protected:
    avl* rr_rotat(avl*);
    avl* ll_rotat(avl*);
    avl* lr_rotat(avl*);
    avl* rl_rotat(avl*);
    avl* insert(avl*, string nom);
    void postorder(avl* t);
    avl* trouverNomMedicament(avl* t,string NomMedicament);

    avl_tree()
    {
        droite = nullptr;
    }

    ~avl_tree()
    {
        if (droite)
            delete droite;
        droite = nullptr;
    }

    avl* droite;
};
#endif
