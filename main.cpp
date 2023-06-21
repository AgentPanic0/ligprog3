#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "catalogo.h"

using namespace std;

ostream& operator<<(ostream &Saida, filme &f)
{
    cout << "Nome: " << f.nome << "\n" << "Produtora: " << f.produtora << "\n" << "Nota: " << f.nota << endl;
    cout << endl;
    return Saida;
}

ostream& operator<<(ostream &Saida, Catalogo &c)
{
    for (unsigned i = 0; i < c.getQuantidadeFilme(); i++)
    {
        cout << c.getFilme(i);
    }
    cout << "----------------------------------------" << endl;

    return Saida;
}

void operator>>(string &Entrada, filme &f)
{
    string nome("");
    string produtora("");
    string notaString("");
    string buffer("");
    double nota;

    for (unsigned i = 0; i < Entrada.size(); i++)
    {
        if (Entrada[i] == ',')
        {
            if (nome == "")
            {
                nome = buffer;
                buffer = "";
            }
            else if (produtora == "")
            {
                produtora = buffer;
                buffer = "";
            } 
        }
        else
        {
            buffer += Entrada[i];
        }
    }
    notaString = buffer;

    f.nome = nome;
    f.produtora = produtora;

    nota = stod(notaString, NULL);
    f.nota = nota;

    return;
}

istream& operator>>(istream &Entrada, filme &f)
{
    string linha;

    getline(Entrada, linha,'\n');

    linha >> f;

    return Entrada;
}

int main (int argc, char *argv[]) 
{
    fstream file;
    string linha, linha2, campo;
    Catalogo catalogo(10);
    vector<filme> vetorFilmes;
    filme filme;
    
    bool cheio = false;
    int opcao = 0;
    double op = 0;

    if (argc != 2)
    {
        cout << "\nQuantidade de argumentos invalido!!\n>>E preciso que insira somente o nome do arquivo.\n" <<endl;
        return 0;
    }

    file.open(argv[1], fstream::in);

    if (!file.is_open())
    {
        cout << "\nArquivo nao existe.\n" << endl;
        return 0;
    }

    while (file.good()) 
    {
        getline(file, linha,'\n');
        linha>>filme;

        if ((catalogo.getQuantidadeFilme() + vetorFilmes.size())>= catalogo.getLimiteFilme())
        {
            cheio = true;
            cout << "\nCatalogo cheio!!\n"<< endl;
        }
        else
        {
            vetorFilmes.push_back(filme);
        }
    }

    file.close();

    if ((catalogo += vetorFilmes) == -1)    
    {
        cout << "\nBanco de dados com o fomato invalido!!"<< endl;
        cout << ">>Nao e permitido acentos e caracteresnao imprimiveis" << endl;
        cout << ">>Nao e permitido nome de filme repetido" << endl;
        cout << ">>Letras maiusculas sao consideradas como minusculas" << endl;
        cout << ">>E permitido somente notas no intervalo de 0 a 10\n" << endl;

        return 0;
    }

    cout << endl;
    cout <<  setw(25) <<"Bem vindo! :)" << endl;

    while(opcao != 6)
    {
        opcao = 0;

        cout << endl;

        //Menu Principal
        cout << setw(18) << "MENU" << endl;
        cout << "Digite o numero da opcao que deseja:" << endl;
        cout << left << setw(25) << "1.Exibir filme" << left << setw(25) << "2.Adicionar filme" << endl;
        cout << left << setw(25) << "3.Remover filme" << left << setw(25) << "4.Editar filme" << endl;
        cout << left << setw(25) << "5.Maior nota" << left << setw(25) << "6.Sair" << endl;
        cout << endl;

        cout << "Digite aqui:";
        cin >> opcao;
        cout << endl;

        switch(opcao)
        {
            case 1:

                cout << "Digite o nome do filme sem letras maiuscas e acentos que deseja exibir. \nSe nada for digitado todos os filmes serao exibidos." << endl;
                
                cout << endl;
                cout << "Digite aqui:";
                cin.ignore(100,'\n');
                getline(cin, linha,'\n');
                cout << endl;

                if (linha == "")
                {
                    cout << catalogo;
                }
                else
                {
                    if (catalogo(linha) == -1)
                    {
                        cout << "\n>>Filme: " << linha << " \n>>Nao encontrado!!\n" << endl;
                        break;
                    }
                    else
                    {
                        cout << catalogo.getFilme(catalogo((linha)));
                    }
                    
                }
                break;

            case 2:

                if (catalogo.getQuantidadeFilme() >= catalogo.getLimiteFilme())
                {
                    cout << "\nOps! :( \nCatalogo cheio!!\n"<< endl;
                }
                else
                {
                    cout << "Digite o nome do filme seguido por sua produtora e nota separando os campos por virgulas."<< endl;
                    cout << "Da seguite forma: nome do filme,nome da produtora,nota"<< endl;

                    cout << endl;
                    cout << "Digite aqui:";
                    cin.ignore(100,'\n');
                    getline(cin, linha,'\n');
                    cout << endl;

                    linha>>filme;

                    if ((catalogo += filme) == -1)
                    {
                        cout << "\nEntrada com o fomato invalido!!"<< endl;
                        cout << ">>Nao e permitido acentos e caracteresnao imprimiveis" << endl;
                        cout << ">>Nao e permitido nome de filme repetido" << endl;
                        cout << ">>Letras maiusculas sao consideradas como minusculas" << endl;
                        cout << ">>E permitido somente notas no intervalo de 0 a 10\n" << endl;
                    }
                }

                break;

            case 3:

                cout << "Digite o nome do filme deseja remover." << endl;
                
                cout << endl;
                cout << "Digite aqui:";
                cin.ignore(100,'\n');
                getline(cin, linha,'\n');
                cout << endl;

                if (catalogo(linha) == -1)
                {
                    cout << "\n>>Filme: " << linha << " \n>>Nao encontrado!!\n" << endl;
                    break;
                }
                else
                {
                    if ((catalogo -= catalogo.getFilme(catalogo(linha))) == -1)
                    {
                        cout << "\nErro inesperado!!"<< endl;
                    }
                }

                break;

             case 4:

                cout << "Digite o nome do filme que deseja Editar." << endl;
                
                cout << endl;
                cout << "Digite aqui:";
                cin.ignore(100,'\n');
                getline(cin, linha,'\n');
                cout << endl;

                cout << "Digite o nome do campo que deseja Editar." << endl;
                
                cout << endl;
                cout << "Digite aqui:";
                getline(cin, campo,'\n');
                cout << endl;

                for (unsigned i = 0; i < campo.size(); i++)
                {
                    if (isupper(campo[i]))//Tratamento letras maiusculas transforma em minusculas
                    {
                        campo[i] = tolower(campo[i]);
                    }
                }
                if (campo == "nota")
                {
                    cout << "Digite o novo valor da nota." << endl;
                
                    cout << endl;
                    cout << "Digite aqui:";
                    cin >> op;
                    cin.ignore(100,'\n');
                    cout << endl;

                    if (catalogo(linha, campo, op) == -1)
                    {
                        cout << "Falha na tentativa de edicao!!!" << endl;
                    }
                }
                else
                {
                   cout << "Digite o novo valor." << endl;
                
                    cout << endl;
                    cout << "Digite aqui:";
                    getline(cin, linha2,'\n');
                    cout << endl;

                    if (catalogo(linha, campo, linha2) == -1)
                    {
                        cout << "Falha na tentativa de edicao!!!" << endl;
                    }
                }
                break;

             case 5:

                if (catalogo.getMaiorNota() != -1)
                {
                    cout << catalogo.getFilme(catalogo.getMaiorNota());
                }
                else
                {
                    cout << "Falha na tentativa de busca pela maior nota!!!\n>>Possivelmente o catalogo esta vazio" << endl;
                }
		
                break;

            case 6:

                cout << "Deseja salvar?sim/nao" << endl;

                if (cheio)
                {
                    cout << "\nAviso: Tiveram filmes que nao entraram no catalogo!!!" << endl;
                    cout << "Aviso: Os filmes que nao entraram no catalogo nao serao descartados!!!" << endl;
                }

                cout << endl;
                cout << "Digite aqui:";
                cin.ignore(100,'\n');
                getline(cin, linha,'\n');
                cout << endl;

                for (unsigned i = 0; i < linha.size(); i++)
                {
                    if (isupper(linha[i]))//Tratamento letras maiusculas transforma em minusculas
                    {
                        linha[i] = tolower(linha[i]);
                    }
                }

                if (linha == "sim")
                {
                    file.open(argv[1], fstream::out);

                    if (!file.is_open())
                    {
                        cout << "\nFalha ao tentar salvar.\n" << endl;
                        return 0;
                    }

                    if (!file.good())
                    {
                        cout << "\nFalha ao tentar salvar.\n" << endl;
                        return 0;
                    }
                    
                    for (unsigned i = 0; i < catalogo.getQuantidadeFilme()-1; i++)
                    {
                        file << catalogo.getFilme(i).nome <<","<< catalogo.getFilme(i).produtora <<","<< catalogo.getFilme(i).nota << endl;
                    }

                    file << catalogo.getFilme(catalogo.getQuantidadeFilme()-1).nome <<","<< catalogo.getFilme(catalogo.getQuantidadeFilme()-1).produtora <<","<< catalogo.getFilme(catalogo.getQuantidadeFilme()-1).nota;

                    file.close();
                }
                
                cout << "Volte sempre! :)" << endl;
                cout << endl;
                break;

            default:
                cout << "Opcao invalida!!!" << endl;
        }
    }

    return 0;
}
