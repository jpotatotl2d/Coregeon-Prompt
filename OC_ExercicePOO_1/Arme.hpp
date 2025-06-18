#ifndef DEF_ARME
#define DEF_ARME

#include <iostream>
#include <string>

class Arme
{
    public:

    Arme();
    Arme(std::string nom, int degats);
    void changer(std::string nom, int degats);
    void afficher(int m_statsLevelUp);
    int getDegats() const;
    void SetName (std::string WpName);
    void afficherPlayer(int statsLevel);

    private:

    std::string m_nom;
    long long m_degats;
};

#endif
