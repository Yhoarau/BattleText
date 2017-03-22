#ifndef OBJET_H
#define OBJET_H

#include <iostream>
#include <string>


class Objet
{
    public:
        Objet();
        Objet(std::string type);
        Objet(std::string nom, std::string type, std::string desc);
        virtual ~Objet();
        void setNom(std::string);
        void setType(std::string);
        void setDescription(std::string);
        std::string getNom();
        std::string getType();
        std::string getDescription();
        bool estEgal(Objet const& obj);
        bool operator==(Objet const& b);

    protected:
        std::string m_nom;
        std::string m_type;
        std::string m_description;
    private:

};

#endif // OBJET_H
