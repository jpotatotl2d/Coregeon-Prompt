#ifndef DEF_ARME
#define DEF_ARME

#include <iostream>
#include <string>

class Personnage;

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
    int setDegats(Personnage &player);

    private:

    std::string m_nom;
    long long m_degats;
};

#endif
