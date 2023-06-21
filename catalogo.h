#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef struct filme
{
    string nome;
    string produtora;
    double nota;
    bool operator> (filme &f)
    {
        if (nome > f.nome)
        {
            return true;
        }
        return false; 
    };
    bool operator> (double &n)
    {
        if (nota > n)
        {
            return true;
        }
        return false; 
    };
}filme;

class Catalogo
{
    public:
        Catalogo(unsigned);

        int operator() (string &);
        int operator() (string &, string &, string &);
        int operator() (string &, string &, double &);
        int operator-= (filme &);
        int operator+= (filme &);
        int operator+= (vector<filme> &);

        unsigned getQuantidadeFilme();
        unsigned getLimiteFilme();

        filme& getFilme(unsigned);
        int getMaiorNota();

    private:
        vector <filme> filmes;
        unsigned maxfilmes;
};