#include "Arme.hpp"
#include "LocalizationManager.hpp"

using namespace std;

Arme::Arme() : m_nom("Epée rouillée"), m_degats(10)
{
}

Arme::Arme(string nom, int degats) : m_nom(nom), m_degats(degats)
{
}

void Arme::SetName (std::string WpName)
{
   // m_nom = WpName;
}

void Arme::changer(string nom, int degats)
{
    m_nom = nom;
    m_degats = degats;
}

void Arme::afficherPlayer(int statsLevel)
{
    cout << " " << LocalizationManager::Instance().Get("str_Char_Status_Wp") << m_nom << " (" << LocalizationManager::Instance().Get("str_Char_Status_WpDmg") << " " << m_degats + statsLevel << ")" << endl;
}

void Arme::afficher(int statsLevel)
{
    cout << " " << LocalizationManager::Instance().Get("str_Char_Status_Wp") << LocalizationManager::Instance().Get(m_nom) << " (" << LocalizationManager::Instance().Get("str_Char_Status_WpDmg") << " " << m_degats + statsLevel << ")" << endl;
}

int Arme::getDegats() const
{
    return m_degats;
}
