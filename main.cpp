#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

char statie[50], a[40][40];
int traseu[6][20] = {0}, m[40][40];
int nrst, nrl, lm;
int mtrasee[40][40];

void statii()
{
    ifstream f("statii");
    nrst = 1;
    while (f.getline(statie, 40))
    {
        strcpy(a[nrst], statie);
        nrst++;
    }
    nrst--;
    f.close();
}

void afisare_statii()
{
    for (int i = 1; i <= nrst; i++)
        cout << i << "." << a[i] << endl;
}

void trasee()
{
    ifstream g("trasee");
    int nrs, nrstatii, nod;
    nrl = 1;
    while (g >> nrs >> nrstatii)
    {
        traseu[nrl][0] = nrs;
        for (int i = 1; i <= nrstatii; i++)
        {
            g >> nod;
            traseu[nrl][i] = nod;
        }
        nrl++;
    }
    nrl--;
    g.close();
}

void afisare_trasee()
{
    int j;
    for (int i = 1; i <= nrl; i++)
    {
        cout << traseu[i][0] << ": ";
        j = 1;
        while (traseu[i][j] != 0)
        {
            if (j != 1)
                cout << "--";
            cout << a[traseu[i][j]];
            j++;
        }
        cout << endl << endl;
    }
}

int vf[40] = {0};

void grad()
{
    for (int i = 1; i <= 39; i++)
        vf[i] = 0;
    int j;
    for (int i = 1; i <= nrl; i++)
    {
        j = 1;
        while (traseu[i][j] != 0)
        {
            vf[traseu[i][j]]++;
            j++;
        }
    }
}

void grad_maxim()
{
    int maxim = 0;
    for (int i = 1; i <= nrst; i++)
    {
        if (vf[i] > maxim)
            maxim = vf[i];
    }
    cout << "Urmatoarele statii sunt cele mai conectate:" << endl;
    for (int i = 1; i <= nrst; i++)
    {
        if (vf[i] == maxim)
            cout << a[i] << endl;
    }
    cin.get();
}

void noduri_nule()
{
    cout << "Urmatoarele statii nu mai sunt in functiune momentan:" << endl;
    for (int i = 1; i <= nrst; i++)
    {
        if (vf[i] == 0)
            cout << a[i] << endl;
    }
}

void ciclu()
{
    cout << "Urmatoarele trasee formeaza un ciclu:" << endl;
    int j;
    for (int i = 1; i <= nrl; i++)
    {
        j = 1;
        while (traseu[i][j] != 0)
        {
            if (traseu[i][j] == traseu[i][1] && traseu[i][j + 1] == 0 && j > 1)
                cout << traseu[i][0] << endl;
            j++;
        }
    }
    cout << "Apasati ENTER pentru a continua..." << endl;
}

void capete()
{
    cout << "Urmatoarele statii sunt capete:" << endl;
    int j;
    for (int i = 1; i <= nrl; i++)
    {
        j = 1;
        while (traseu[i][j] != 0)
        {
            if (j == 1)
                cout << a[traseu[i][j]] << " pentru " << traseu[i][0] << endl;
            if (traseu[i][j + 1] == 0 && traseu[i][j] != traseu[i][1])
                cout << a[traseu[i][j]] << " pentru " << traseu[i][0] << endl;
            j++;
        }
    }
}

void statii_speciale()
{
    grad();
    int tasta;
    do
    {
        system("CLS");
        cout << "1.Afisati statia care se regaseste de cele mai multe ori in trasee" << endl;
        cout << "2.Afisati statiile care au fost desfiintate" << endl;
        cout << "3.Afisati traseele care formeaza cicluri" << endl;
        cout << "4.Afisati capetele" << endl;
        cout << "0.EXIT" << endl;
        cout << "Optiune: ";
        cin >> tasta;
        cin.ignore(10000, '\n');
        
        switch (tasta)
        {
            case 1:
                system("CLS");
                grad_maxim();
                break;
            case 2:
                system("CLS");
                noduri_nule();
                cin.get();
                break;
            case 3:
                system("CLS");
                ciclu();
                cin.get();
                break;
            case 4:
                system("CLS");
                capete();
                cin.get();
                break;
        }
    } while (tasta != 0);
}

int st[40];
int np, ns;
int cnt;
int durata;
int duratamin, k;

void init()
{
    if (k > 1)
        st[k] = 0;
}

int succesor()
{
    if (st[k] < nrst)
    {
        st[k]++;
        return 1;
    }
    return 0;
}

int solutie()
{
    if (st[k] == ns)
    {
        durata = 0;
        for (int c = 2; c <= k; c++)
        {
            for (int i = 0; i < lm; i++)
            {
                if ((st[c] == m[i][0] && st[c - 1] == m[i][1]) || (st[c - 1] == m[i][0] && st[c] == m[i][1]))
                    durata = durata + m[i][2];
            }
        }
        return 1;
    }
    return 0;
}

int valid()
{
    int n1 = st[k], n2 = st[k - 1];
    for (int i = 1; i < k; i++)
        if (st[i] == st[k])
            return 0;

    for (int i = 1; i <= nrl; i++)
    {
        int j = 1;
        while (traseu[i][j] != 0)
        {
            if ((n1 == traseu[i][j] && n2 == traseu[i][j - 1]) || (n1 == traseu[i][j - 1] && n2 == traseu[i][j]))
                return 1;
            j++;
        }
    }
    return 0;
}

void afisare()
{
    cnt++;
    cout << cnt << ": ";
    for (int i = 1; i <= k; i++)
    {
        cout << a[st[i]];
        if (i < k)
        {
            for (int j = 1; j <= nrl; j++)
            {
                int c = 1;
                while (traseu[j][c] != 0)
                {
                    if ((traseu[j][c] == st[i] && traseu[j][c + 1] == st[i + 1]) ||
                        (traseu[j][c + 1] == st[i] && traseu[j][c] == st[i + 1]))
                    {
                        cout << "(" << traseu[j][0] << ")";
                    }
                    c++;
                }
            }
            cout << "--";
        }
    }
    cout << endl;
    if (durata < 60)
        cout << "Pret calatorie: 3 lei" << endl;
    else
        cout << "Pret calatorie: " << (durata / 60 + 1) * 3 << " lei" << endl;

    cout << durata << " minute" << endl << endl;

    if (durata < duratamin)
        duratamin = durata;
}

void afisareminim()
{
    if (durata == duratamin)
    {
        cout << "Cel mai scurt traseu este:" << endl;
        for (int i = 1; i <= k; i++)
        {
            cout << a[st[i]];
            if (i < k)
            {
                for (int j = 1; j <= nrl; j++)
                {
                    int c = 1;
                    while (traseu[j][c] != 0)
                    {
                        if ((traseu[j][c] == st[i] && traseu[j][c + 1] == st[i + 1]) ||
                            (traseu[j][c + 1] == st[i] && traseu[j][c] == st[i + 1]))
                        {
                            cout << "(" << traseu[j][0] << ")";
                        }
                        c++;
                    }
                }
                cout << "--";
            }
        }
        cout << endl << duratamin << " minute" << endl;
    }
}

void back()
{
    k = 2;
    int ev = 0, as = 0;
    init();
    while (k > 1)
    {
        do
        {
            as = succesor();
            if (as == 1)
                ev = valid();
        } while (as == 1 && ev == 0);

        if (as == 1)
        {
            if (solutie() == 1)
                afisare();
            else
            {
                k++;
                init();
            }
        }
        else
            k--;
    }
}

void back2()
{
    k = 2;
    int ev = 0, as = 0;
    init();
    while (k > 1)
    {
        do
        {
            as = succesor();
            if (as == 1)
                ev = valid();
        } while (as == 1 && ev == 0);

        if (as == 1)
        {
            if (solutie() == 1)
                afisareminim();
            else
            {
                k++;
                init();
            }
        }
        else
            k--;
    }
}

void timpstatii()
{
    ifstream t("timpstatii");
    lm = 0;
    int n1, n2, timp;
    while (t >> n1 >> n2 >> timp)
    {
        m[lm][0] = n1;
        m[lm][1] = n2;
        m[lm][2] = timp;
        lm++;
    }
    t.close();
}

void parcurgere_trasee()
{
    statii();
    trasee();

    cout << " Se afiseaza toate statiile disponibile: " << endl;
    afisare_statii();

    cout << "Citeste nr statiei de pornire (de la 1 la " << nrst << "): ";
    while (!(cin >> np) || np < 1 || np > nrst)
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Statie invalida! Introdu un numar intre 1 si " << nrst << ": ";
    }
    cin.ignore(10000, '\n');
    cout << "(" << a[np] << ")" << endl;

    cout << "Citeste nr statiei de destinatie (de la 1 la " << nrst << "): ";
    while (!(cin >> ns) || ns < 1 || ns > nrst)
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Statie invalida! Introdu un numar intre 1 si " << nrst << ": ";
    }
    cin.ignore(10000, '\n');
    cout << "(" << a[ns] << ")" << endl << endl;

    cnt = 0;
    duratamin = 10000;
    st[1] = np;
    timpstatii();
    back();

    int tasta;
    if (cnt == 0)
    {
        cout << "Nu exista traseu intre aceste statii." << endl;
        cout << "Doriti sa incercati alt traseu? (1=Da, 0=EXIT): ";
        cin >> tasta;
        cin.ignore(10000, '\n');
        if (tasta == 1)
        {
            system("CLS");
            parcurgere_trasee();
        }
        return;
    }

    cout << "Doriti sa vedeti care este cel mai scurt traseu? (1=Da, 0=EXIT): ";
    cin >> tasta;
    cin.ignore(10000, '\n');
    if (tasta == 1)
    {
        system("CLS");
        timpstatii();
        back2();
        cout << "\nApasati ENTER pentru a continua...";
        cin.get();
    }
}

struct datelogare
{
    char nume[30], prenume[30], user[30], parola[30];
    int logat;
} logare;

void adaugare_statie()
{
    char sta[40];
    int ok = 1, tasta;
    cout << "Cititi statia pe care doriti sa o adaugati: ";
    cin.getline(sta, 40);
    for (int i = 1; i <= nrst && ok == 1; i++)
    {
        if (strcmp(a[i], sta) == 0)
        {
            cout << "Statia este deja existenta!" << endl;
            ok = 0;
        }
    }
    if (ok == 0)
    {
        cout << "1.Incearca alta statie\n0. EXIT\nOptiune: ";
        cin >> tasta;
        cin.ignore(10000, '\n');
        if (tasta == 1)
        {
            system("CLS");
            adaugare_statie();
        }
    }
    else
    {
        ofstream f("statii", ios_base::app);
        f << endl << sta;
        f.close();
        statii();
        cout << "Statia a fost adaugata cu succes! Nu uitati sa adaugati si statiile de legatura." << endl;
    }
}

void elem_conexe()
{
    grad();
    int nrc = 1;
    cout << "Statii izolate(componente separate):" << endl;
    for (int i = 1; i <= nrst; i++)
    {
        if (vf[i] == 0)
        {
            cout << nrc << ": " << a[i] << endl;
            nrc++;
        }
    }
    cout << "\nTraseele conectate formeaza componenta: " << nrc << endl;
    for (int i = 1; i <= nrl; i++)
        cout << traseu[i][0] << " ";
    cout << endl;
}

void administrare()
{
    int tasta;
    statii();
    trasee();
    ifstream l("date");
    l >> logare.nume >> logare.prenume >> logare.user >> logare.parola;
    l.close();

    int exit_login = 0;
    char num[30], prenum[30], usern[40], parol[20];

    while (exit_login == 0)
    {
        system("CLS");
        cout << "AUTENTIFICARE (tastati '0' la nume pentru anulare)" << endl;
        cout << "Introduceti numele: ";
        cin >> num;
        if (strcmp(num, "0") == 0)
        {
            cin.ignore(10000, '\n');
            return;
        }
        cout << "Introduceti prenumele: ";
        cin >> prenum;
        cout << "Introduceti user-ul: ";
        cin >> usern;
        cout << "Introduceti parola: ";
        cin >> parol;
        cin.ignore(10000, '\n');
        
        if (strcmp(logare.nume, num) == 0 && strcmp(logare.prenume, prenum) == 0)
        {
            if (strcmp(logare.user, usern) == 0 && strcmp(logare.parola, parol) == 0)
            {
                logare.logat = 1;
                exit_login = 1;
                do
                {
                    system("CLS");
                    cout << "V-ati logat cu succes!\n" << endl;
                    cout << "1. Afiseaza toate statiile disponibile" << endl;
                    cout << "2. Afisare trasee" << endl;
                    cout << "3. Care sunt liniile si statiile speciale?" << endl;
                    cout << "4. Adaugati o statie" << endl;
                    cout << "5. Componente conexe" << endl;
                    cout << "0. Deconectare (EXIT)" << endl;
                    cout << "Optiune: ";
                    cin >> tasta;
                    cin.ignore(10000, '\n');

                    switch (tasta)
                    {
                        case 1: system("CLS"); afisare_statii(); cin.get(); break;
                        case 2: system("CLS"); afisare_trasee(); cin.get(); break;
                        case 3: system("CLS"); statii_speciale(); break;
                        case 4: system("CLS"); adaugare_statie(); cin.get(); break;
                        case 5: system("CLS"); elem_conexe(); cin.get(); break;
                    }
                } while (tasta != 0);
            }
            else
            {
                cout << "\nUser sau parola incorecte!" << endl;
                cout << "1.Incearca din nou\n0. Inapoi la meniul principal\nOptiune: ";
                cin >> tasta;
                cin.ignore(10000, '\n');
                if (tasta == 0)
                    exit_login = 1;
            }
        }
        else
        {
            cout << "\nNume sau prenume incorecte!" << endl;
            cout << "1. Incearca din nou\n0. Inapoi la meniul principal\nOptiune: ";
            cin >> tasta;
            cin.ignore(10000, '\n');
            if (tasta == 0)
                exit_login = 1;
        }
    }
}

int main()
{
    system("COLOR 71");
    cout << "\n\n\n\n\n";
    cout << "                  IIIIIIIIII                    ffffffffffffffff                        SSSSSSSSSSSSSSS TTTTTTTTTTTTTTTTTTTTTTTBBBBBBBBBBBBBBBBB " << endl;
    cout << "                  I::::::::I                   f::::::::::::::::f                      SS:::::::::::::::ST:::::::::::::::::::::TB::::::::::::::::B " << endl;
    cout << "                  I::::::::I                  f::::::::::::::::::f                    S:::::SSSSSS::::::ST:::::::::::::::::::::TB::::::BBBBBB:::::B " << endl;
    cout << "                  II::::::II                  f::::::fffffff:::::f                    S:::::S     SSSSSSST:::::TT:::::::TT:::::TBB:::::B     B:::::B " << endl;
    cout << "                    I::::Innnn  nnnnnnnn      f:::::f       ffffffooooooooooo         S:::::S            TTTTTT  T:::::T  TTTTTT  B::::B     B:::::B " << endl;
    cout << "                    I::::In:::nn::::::::nn    f:::::f             oo:::::::::::oo     S:::::S                    T:::::T          B::::B     B:::::B " << endl;
    cout << "                    I::::In::::::::::::::nn f:::::::ffffff       o:::::::::::::::o     S::::SSSS                 T:::::T          B::::BBBBBB:::::B " << endl;
    cout << "                    I::::Inn:::::::::::::::nf::::::::::::f       o:::::ooooo:::::o      SS::::::SSSSS            T:::::T          B:::::::::::::BB " << endl;
    cout << "                    I::::I  n:::::nnnn:::::nf::::::::::::f       o::::o     o::::o        SSS::::::::SS          T:::::T          B::::BBBBBB:::::B " << endl;
    cout << "                    I::::I  n::::n    n::::nf:::::::ffffff       o::::o     o::::o           SSSSSS::::S         T:::::T          B::::B     B:::::B " << endl;
    cout << "                    I::::I  n::::n    n::::n f:::::f             o::::o     o::::o                S:::::S        T:::::T          B::::B     B:::::B " << endl;
    cout << "                    I::::I  n::::n    n::::n f:::::f             o::::o     o::::o                S:::::S        T:::::T          B::::B     B:::::B " << endl;
    cout << "                  II::::::IIn::::n    n::::nf:::::::f            o:::::ooooo:::::o    SSSSSSS     S:::::S      TT:::::::TT      BB:::::BBBBBB::::::B " << endl;
    cout << "                  I::::::::In::::n    n::::nf:::::::f            o:::::::::::::::o    S::::::SSSSSS:::::S      T:::::::::T      B:::::::::::::::::B " << endl;
    cout << "                  I::::::::In::::n    n::::nf:::::::f             oo:::::::::::oo      S:::::::::::::::SS      T:::::::::T      B::::::::::::::::B " << endl;
    cout << "                  IIIIIIIIIInnnnnn    nnnnnnfffffffff               ooooooooooo         SSSSSSSSSSSSSSS        TTTTTTTTTTT      BBBBBBBBBBBBBBBBB " << endl;

    cout << "\nApasati ENTER pentru a incepe..." << endl;
    cin.get();

    int tasta;
    do
    {
        system("CLS");
        cout << "1. ADMINISTRARE" << endl;
        cout << "2. CALATORII" << endl;
        cout << "0. EXIT" << endl;
        cout << "Optiune: ";
        cin >> tasta;
        cin.ignore(10000, '\n');

        switch (tasta)
        {
            case 1:
                administrare();
                break;
            case 2:
                system("CLS");
                parcurgere_trasee();
                break;
        }
    } while (tasta != 0);

    return 0;
}