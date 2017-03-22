#include "Objet.h"

using namespace std;

Objet::Objet()
{
    //ctor
}

Objet::Objet(string type) : m_type(type)
{
    //ctor
}

Objet::Objet(string nom, string type, string desc) : m_nom(nom), m_type(type), m_description(desc)
{
    //ctor
}

Objet::~Objet()
{
    //dtor
}

void Objet::setNom(string nom)
{
    m_nom = nom;
}

void Objet::setType(string type)
{
    m_type = type;
}

void Objet::setDescription(string desc)
{
    m_description = desc;
}

string Objet::getNom()
{
    return m_nom;
}

string Objet::getType()
{
    return m_type;
}

string Objet::getDescription()
{
    return m_description;
}

bool Objet::estEgal(Objet const& b)
{
    return (m_nom == b.m_nom && m_type == b.m_type && m_description == b.m_description);

}

 bool Objet::operator==(Objet const& b)
{
    return this->estEgal(b);
}
