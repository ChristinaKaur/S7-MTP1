#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;
const string EOS = "#";

struct Llibre 
{
    string titol, editorial, autor;
    int categoria, codi;
    double preu;
};

const int MAX = 100;
typedef Llibre Llibres[MAX];

struct Taula_llibres
{
    Llibres ll;
    int n;
};

void afegir_a_taula(Llibre llibre, Taula_llibres& t)
{
    t.ll[t.n] = llibre;
    t.n++;
}

void intercanvia(Llibre& a, Llibre& b)
{
    //Pre: a=A i b=B
    //Post: a=B i b=A
    Llibre aux = a;
    a = b;
    b = aux;
}

int posicio_del_minim_des_de(const Taula_llibres t, int inici)
{
    //Pre: 0 <= inici < t.n <= MAX
    //Post: retorna la posició del llibre amb codi minim de t[inici..n - 1] i si n'hi ha dos amb la mateix codi
    int pos_min = inici;
    for (int i = inici + 1; i < t.n; i++)
    {
        if (t.ll[i].codi < t.ll[pos_min].codi)
            pos_min = i;
    }
    return pos_min;
}

void ordenar_per_codi(Taula_llibres& t)
{
    //Pre: 0<=t.n<=MAX, t=T
    //Post: t[0..t.n-1] conté el elements de T[0..t.n-1] ordenats per gravetat decreixent
    for (int i = 0; i < t.n; i++)
    {
        int pos_min = posicio_del_minim_des_de(t, i);
        intercanvia(t.ll[i], t.ll[pos_min]);
    }
}

void mostrar(const Llibre ll)
{
    cout << ll.codi << " - " << ll.autor << ", " << ll.titol << ". Ed. " << ll.editorial << " - " << ll.preu << " eur." << endl;
}

void llibres_per_preu(const double preu, const Taula_llibres t)
{
    cout << "Llibres amb preu no superior a " << preu << ":" << endl;
    
    for (int i = 0; i < t.n; i++)
    {
        if (t.ll[i].preu <= preu)
            mostrar(t.ll[i]);
    }
}

void llibres_per_titol(const string titol, const Taula_llibres t)
{
    bool trobat = false;
    int i = 0;
    while (i < t.n and !trobat)
    {
        if (t.ll[i].titol == titol)
        {
            mostrar(t.ll[i]);
            trobat = true;
        }
        i++;
    }

    if (!trobat)
        cout << "No s'ha trobat cap llibre amb aquest titol." << endl;
}

void llibres_per_autor(const string autor, const Taula_llibres t)
{
    cout << "Llibres de l'autor " << autor << ":" << endl;
    for (int i = 0; i < t.n; i++)
    {
        if (t.ll[i].autor == autor)
            mostrar(t.ll[i]);
    }
}

int main()
{
    string titol;
    cout << "Introdueix els llibres - Titol editorial autor categoria codi preu - titol " << EOS << " per acabar: " << endl;
    cin >> titol;

    Taula_llibres llibres;
    llibres.n = 0;
    Llibre llibre;
    while (titol != EOS)
    {
        llibre.titol = titol;
        cin >> llibre.editorial >> llibre.autor >> llibre.categoria >> llibre.codi >> llibre.preu;
        afegir_a_taula(llibre,llibres);
        cin >> titol;
    }

    ordenar_per_codi(llibres);
    cout << "Cataleg de llibres:" << endl;
    for (int i = 0; i < llibres.n; i++)
    {
        mostrar(llibres.ll[i]);
    }

    char opcio = 'a';
    while (opcio != 's')
    {
        cout << "Selecciona: sortir(s) - cercar per titol(t), autor(a) o preu(p): ";
        cin >> opcio;

        if (opcio == 't')
        {
            cout << "Entra el titol: ";
            cin >> titol;

            llibres_per_titol(titol, llibres);
        }
        else if (opcio == 'a')
        {
            string autor;
            cout << "Entra l'autor: ";
            cin >> autor; 

            llibres_per_autor(autor, llibres);
        }
        else if (opcio == 'p')
        {
            double preu;
            cout << "Entra preu maxim: ";
            cin >> preu;

            llibres_per_preu(preu, llibres);
        }
    }
    
    cout << "Fins aviat!" << endl;

    return 0;
}
