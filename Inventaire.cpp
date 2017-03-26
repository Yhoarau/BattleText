#include "Inventaire.h"

using namespace std;

Inventaire::Inventaire() : m_nom("Sac de guerrier"), m_taille(10)
{
    //ctor
}

Inventaire::~Inventaire()
{
    //dtor
}


std::vector<std::string> Inventaire::getNomsObj()
{
    vector<string> Contenu;
    Contenu.resize(m_contenu.size());
    for( unsigned i(0); i < Contenu.size() ; ++i)
    {
        Objet O = *(m_contenu[i]);
        Contenu[i] = (O.getNom());
    }

    return Contenu;
}

std::vector<unsigned> Inventaire::getExemplaires() const
{
    return m_exemplaires;
}

std::vector<std::string> Inventaire::getType()
{
    vector<string> Types;
    Types.resize(m_contenu.size());
    for( unsigned i(0); i < Types.size() ; ++i)
    {
        Objet O = *(m_contenu[i]);
        Types[i] = (O.getNom());
    }
    return Types;
}

std::vector<std::string> Inventaire::getDescription()
{
    vector<string> Descriptions;
    Descriptions.resize(m_contenu.size());
    for( unsigned i(0); i < Descriptions.size() ; ++i)
    {
        Objet O = *(m_contenu[i]);
        Descriptions[i] = (O.getNom());
    }
    return Descriptions;
}

vector<Objet*> Inventaire::getContenu() const
{

    return m_contenu;
}

void Inventaire::setContenu(vector<Objet*> objs)
{
    m_contenu.resize(objs.size());
    for(unsigned i(0); i < objs.size() ; ++i)
        m_contenu[i] = objs[i];
}

void Inventaire::setExemplaires(std::vector<unsigned> nbObj)
{
    m_exemplaires.resize(0);
    for(unsigned & Ex : nbObj )
        m_exemplaires.push_back(Ex);
}

/*void Inventaire::setType(vector<string> types)
{
    m_type.resize(0);
    for(string & type : types )
        m_type.push_back(type);
}

void Inventaire::setDescription(vector<string> descriptions)
{
    m_type.resize(0);
    for(string & description : descriptions )
        m_type.push_back(description);
} */

void Inventaire::ajouterObjet(Objet nom, unsigned nb)
{
    for(unsigned i(0); i < m_contenu.size() ; ++i)
        {
            if(nom == *(m_contenu[i]) )
                m_exemplaires[i] += nb;
            else
            {
                m_contenu.resize(m_contenu.size() + 1);
                m_contenu[m_contenu.size() - 1] = &nom;
                m_exemplaires.resize(m_exemplaires.size() + 1);
                m_exemplaires[m_exemplaires.size() - 1] = nb;
            }
        }

/*
    vector<Objet>::iterator it = find(m_contenu.begin(), m_contenu.end(), nom);
    unsigned i = distance(m_contenu.begin(), it);
    if (it != m_contenu.end())
        m_exemplaires[i] += nb;
    else
    {
        m_contenu.resize(m_contenu.size() + 1);
        m_contenu[m_contenu.size() - 1] = nom;
        m_exemplaires.resize(m_exemplaires.size() + 1);
        m_exemplaires[m_exemplaires.size() - 1] = nb;
    } */
}

void Inventaire::refreshInventaire()
{
   /* for(unsigned i(0); i < m_contenu.size() ; ++i)
        if(m_exemplaires[i] == 0)
        {
            m_contenu.erase(m_contenu.begin() + i);
            m_type.erase(m_type.begin() + i);
            m_exemplaires.erase(m_exemplaires.begin() + i);
        } */

    vector<unsigned>::iterator it = find(m_exemplaires.begin(), m_exemplaires.end(), 0);
    unsigned i = distance(m_exemplaires.begin(), it);
    if (it != m_exemplaires.end())
        {
            m_contenu.erase(m_contenu.begin() + i);
            //m_type.erase(m_type.begin() + i);
            m_exemplaires.erase(m_exemplaires.begin() + i);
        }

}

bool Inventaire::checkInventaire()
{
    return (m_contenu.size() == m_exemplaires.size());
}
