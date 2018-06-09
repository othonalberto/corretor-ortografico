// Simple trie data structure using STL. Based on code by Vivek Narayanan.
// - rlyeh, 2013-2015 zlib/libpng licensed ~~ listening to Baroness / March to the Sea.

#pragma once
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

#define   TRIE_VERSION "1.0.1" // additional tree implementation
//#define TRIE_VERSION "1.0.0" // initial commit

template<typename K, typename V = int>
class trie
{
    public:

    trie() : flag(false)
    {}

    bool has( const K &collection ) const {
        for( const auto &it : children ) {
            if( it.second.has(collection) ) {
                return true;
            }
        }
        return flag && collection == branch ? true : false;
    }

    V& insert( const K &collection ) {
        trie *node = this;
        for( auto &c : collection ) {
            auto found = node->children.find( c );
            if( found == node->children.end() ) {
                auto copy = node->branch;
                std::back_inserter( copy ) = c;
                node->children[c] = trie( copy );
            }
            node = &(node->children[c]);
        }
        node->flag = true;
        return node->leaf;
    }

    V& operator[]( const K &collection ) {
        return insert( collection );
    }

    std::vector<const K *> list() const {
        std::vector<const K *> results;
        if( flag ) {
            results.push_back( &branch );
        }
        for( const auto &it : children ) {
            auto keys = it.second.list();
            for( const auto &key : keys ) {
                results.push_back( key );
            }
        }
        return results;
    }

    std::vector<const K *> complete( const K &prefix ) const {
        const trie *node = this;
        for( auto &elem : prefix ) {
            const auto found = node->children.find( elem );
            if( found == node->children.end() ) {
                return std::vector<const K *>();
            }
            node = &found->second;
        }
        return node->list();
    }

    unsigned size() const {
        return list().size();
    }

    // ================================================================= //
    int ondeErro(const K &entrada) {
        int i = 0,
            tamanho = entrada.size(),
            cont = 0;

        trie *node = this;

        for (i = 0; i < tamanho; i++) { 
            auto achado = node->children.find(entrada[i]);
            if (achado != node->children.end()) {
                cont++;
                node = &achado->second;
            } else return cont;
        }

        return cont;
    }

    std::vector<const K *> possiveisCandidatos(const K original, unsigned int erro) const {
        string linhaAux;
        linhaAux = original.substr(0, erro);
        auto arvore = this;
 
        auto ponteirosCandidatos = arvore->complete(linhaAux);
        unsigned int qtd = 0;

        do {
            linhaAux = original.substr(0, erro);
            auto ponteirosCandidatos = arvore->complete(linhaAux);
            qtd = ponteirosCandidatos.size();
                    
            if (qtd < 1) {
                erro--;
            }
   
        } while (qtd < 1 && erro != 0); // se nao tiver nenhuma sugestao, ou a substring acabar
    
        if (erro == 0) return std::vector<const K *>();
        else return ponteirosCandidatos;

    }

    string substituicao(string original) const {
        // essa funcao irá mudar a primeira letra da palavra e tentar encontra UMA
        // nova string
    
        // exemplo: Wedro
        // Aedro existe? Nao
        // Bedro existe? Nao
        // Cedro existe? Sim!
        // Então, retorna
    
        // Creio que para isso cria-se um vetor das letras do alfabeto
        // faz um laço for pra ficar substituindo
        // e aplica o método .has()

        string copia = original;

        int i;

        for (i = 97; i < 123; i++ ) {
            copia[0] = char(i); 

            if (this->has(copia)) 
                return copia;
        }
   
        return string();
    }

    protected:

    trie( const K &branch ) : branch(branch), flag(false)
    {}

    K branch;
    V leaf;
    bool flag;
    std::map< typename K::value_type, trie > children;
};

