#include "catalogo.h"

Catalogo::Catalogo(unsigned max): maxfilmes(max) {}

unsigned Catalogo::getQuantidadeFilme(){ return filmes.size(); }
unsigned Catalogo::getLimiteFilme(){ return maxfilmes; }
filme& Catalogo::getFilme(unsigned indice){ return filmes[indice]; }

int Catalogo::getMaiorNota()
{
    double maiorNota = 0;
    int indice = -1;

    for (unsigned i = 0; i < filmes.size(); i++)
    {
        if (filmes[i] > maiorNota)
        {
            maiorNota = filmes[i].nota;
            indice = i;
        }
    }

    return indice; 
}

int Catalogo::operator() (string &nome)
{
    for (unsigned i = 0; i < filmes.size(); i++)
    {
        if (nome == filmes[i].nome)
        {
            return i;
        }
        
    }
    return -1; 
}

int Catalogo::operator() (string &nomeFilme, string &nomeAtributo, string &novoValor)
{
    filme copia;
    int indice = 0;

    for (unsigned i = 0; i < novoValor.size(); i++)
    {
        if (!isprint(novoValor[i]))//Tratamento letras nao printaveis
        {
            return -1;
        }
        if (isupper(novoValor[i]))//Tratamento letras maiusculas transforma em minusculas
        {
            novoValor[i] = tolower(novoValor[i]);
        }
    }

    indice = (*this)(nomeFilme);
    if (indice == -1)
    {
        return -1;
    }

    if (nomeAtributo == "nome")
    {
        copia = filmes[indice];

        (*this) -= filmes[indice];

        copia.nome = novoValor;

        (*this) += copia;
    }
    else if (nomeAtributo == "produtora")
    {
        filmes[indice].produtora = novoValor;
    }
    else
    {
        return -1;
    }

    return indice; 
}

int Catalogo::operator() (string &nomeFilme, string &nomeAtributo, double &novoValor)
{
    int indice = 0;

    //verificando se a nota esta no intervalo correto
	if(novoValor>10.0 || novoValor<0.0)
    { 
	    return -1;
	}

    indice = (*this)(nomeFilme);
    if (indice == -1)
    {
        return -1;
    }

    if (nomeAtributo == "nota")
    {
        filmes[indice].nota = novoValor;
    }
    else
    {
        return -1;
    }

    return indice; 
}

int Catalogo::operator-= (filme &f)
{
    int indice = 0;

    indice = (*this)(f.nome);
    //Verificando se o nome existe
    if (indice == -1)
    {
        return -1;
    }

    filmes.erase( filmes.begin() + indice);

    return indice; 
}

int Catalogo::operator+= (filme &f)
{
    bool primeiro = false;
    bool entrei = false;
    unsigned indice = 0;

    //caso nao tenha espaço
    if (filmes.size() >= maxfilmes)
    {
        return -1;
    }
    //verificando se a nota esta no intervalo correto
	if(f.nota>10.0 || f.nota<0.0)
    { 
	    return -1;
	}
    //Tratamento no nome do filme
    for (unsigned i = 0; i < f.nome.size(); i++)
    {
        if (!isprint(f.nome[i]))//Tratamento letras nao printaveis
        {
            return -1;
        }
        if (isupper(f.nome[i]))//Tratamento letras maiusculas transforma em minusculas
        {
            f.nome[i] = tolower(f.nome[i]);
        }
    }
    //Tratamento no nome da produtora
    for (unsigned i = 0; i < f.produtora.size(); i++)
    {
        if (!isprint(f.produtora[i]))//Tratamento letras nao printaveis
        {
            return -1;
        }
        if (isupper(f.produtora[i]))//Tratamento letras maiusculas transforma em minusculas
        {
            f.produtora[i] = tolower(f.produtora[i]);
        }
    }
    //Verificando se o nome ja existe
    if ((*this)(f.nome) != -1)
    {
        return -1;
    }
    //encontrando a posicao na ordem alfabetica
    for (unsigned i = 0; i < filmes.size(); i++)
    {
        entrei = true;
        if (filmes[i] > f && !primeiro)
        {
            indice = i;
            primeiro = true;
        }
    }

    if (entrei && !primeiro)
    {
        filmes.insert( filmes.begin() + filmes.size(), f);
        return filmes.size();
    }
    else
    {
        filmes.insert( filmes.begin() + indice, f);
        return indice;
    }
}

int Catalogo::operator+= (vector<filme> &vf)
{
    int retorno = -1;

    for (unsigned i = 0; i < vf.size(); i++)
    {
        retorno = ((*this) += vf[i]);
        if (retorno == -1)
        {
            return -1;
        }
    }
    return retorno; 
}