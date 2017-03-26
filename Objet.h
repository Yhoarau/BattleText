#ifndef OBJET_H
#define OBJET_H

#include <iostream>
#include <string>

enum e_Type
{
    ARME, POTION,
};


class Objet
{
    public:
        Objet();
        Objet(e_Type type);
        Objet(std::string nom, e_Type type, std::string desc);
        virtual ~Objet();
        void setNom(std::string);
        void setType(e_Type);
        void setDescription(std::string);
        std::string getNom();
        e_Type getType();
        std::string getDescription();
        //bool estEgal(Objet const& obj);
        bool operator==(Objet const& b);

    protected:
        std::string m_nom;
        e_Type m_type;
        std::string m_description;
    private:

};

#endif // OBJET_H
