#ifndef _KDTREE_HEADER
#define _KDTREE_HEADER

#include <vector>
#include <cstddef>
#include "geometry.hpp"

struct KDNode
{
    KDNode(Point p);

    const Point point();
    KDNode* p_left, *p_right;
private:
    Point p_point;
};

KDNode::KDNode(Point p): p_point(p) {}

const Point KDNode::point()
{
    return p_point;
}

class KDTree
{
public:
    KDTree();
    ~KDTree();

    KDNode* find(Point p);
    void insert(Point p);
    std::vector<KDNode*>* search(Rectangle r);
    void clear();
private:
    KDNode* root = nullptr;

    KDNode* find_(KDNode* root, KDNode* fnode, std::size_t dim);
    KDNode* insert_(KDNode* root, KDNode* nnode, std::size_t dim);
    void search_(KDNode* root, Rectangle r, std::vector<KDNode*>*, std::size_t dim);

    void clear_(KDNode* root);
};

KDTree::KDTree() { }

void KDTree::clear_(KDNode* root)
{
    // evita erros após 'exclusões consecutivas'
    if (root != nullptr)
        return;

    if (root->p_left != nullptr)
        clear_(root->p_left);
    if (root->p_right != nullptr)
        clear_(root->p_right);
    delete root;
}

KDTree::~KDTree()
{
    clear();
}

void KDTree::clear()
{
    clear_(root);
}

void KDTree::insert(Point p)
{
    root = insert_(root, new KDNode(p), 0);
}

KDNode* KDTree::insert_(KDNode* root, KDNode* nnode, std::size_t dim)
{
    if (root == nullptr)
        return nnode;

    if (root->point().dim(dim % 2) > nnode->point().dim(dim % 2))
        root->p_left = insert_(root->p_left, nnode, dim + 1);
    else
        root->p_right = insert_(root->p_right, nnode, dim + 1);
    return root;
}

KDNode* KDTree::find(Point p)
{
    return find_(root, new KDNode(p), 0);
}

KDNode* KDTree::find_(KDNode* root, KDNode* fnode, std::size_t dim)
{
    std::size_t actualDim = dim % 2;
    std::size_t nextDim = (dim + 1) % 2;

    if (root == nullptr)
        return nullptr;

    // Identifica se o nó atual possuí o elemento procurado
    if (fnode->point().dim(actualDim) == root->point().dim(actualDim) && 
            fnode->point().dim(nextDim) == root->point().dim(nextDim))
        return root;

    // Caso o nó corrente não seja o selecionado, então a busca inicia novamente
    // considerando uma nova dimensão
    if (root->point().dim(actualDim) > fnode->point().dim(actualDim))
        return find_(root->p_left, fnode, dim + 1);
    else
        return find_(root->p_right, fnode, dim + 1);
    return nullptr;
}

std::vector<KDNode*>* KDTree::search(Rectangle r)
{
    std::vector<KDNode*>* reported = new std::vector<KDNode*>();
    search_(root, r, reported, 0);

    return reported;
}

void KDTree::search_(KDNode* root, Rectangle r, 
                        std::vector<KDNode*>* reported, std::size_t dim)
{
    std::size_t actualDim = dim % 2;
    std::size_t nextDim = (dim + 1) % 2;
    Range actualDimRange = r.dim(actualDim);
    Range nextDimRange = r.dim(nextDim); 

    if (root == nullptr)
        return; // Para evitar falha de segmentação

    // Verifica se o elemento está dentro do intervalo delimitado
    // Caso uma dimensão seja igual, a outra dimensão é verificada, se a segunda
    // dimensão for igual, então o elemento é reportado
    if (root->point().dim(actualDim) >= actualDimRange.min() && 
        root->point().dim(actualDim) <= actualDimRange.max()) 
    {
        if (root->point().dim(nextDim) >= nextDimRange.min() && 
            root->point().dim(nextDim) <= nextDimRange.max())
                reported->push_back(root);
                // O fato de não fazer retorno nesta parte, indicando por exemplo o fim de uma recursão
                // indica que mesmo encontrando um elemento, os lados precisam do nó precisam ser verificados.
    }

    // Nesta parte, o que está sendo feito é eliminar os lados da árvore
    // que não tem os 'requisitos' do range, ou melhor, que não estão dentro
    // do intervalo selecionado
    if (actualDimRange.min() <= root->point().dim(actualDim))
        search_(root->p_left, r, reported, dim + 1);
    if (actualDimRange.max() >= root->point().dim(actualDim))
        search_(root->p_right, r, reported, dim + 1);
}

#endif
