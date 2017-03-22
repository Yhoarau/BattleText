#ifndef INVENTAIRE_H
#define INVENTAIRE_H


#include <vector>
#include <algorithm>
#include "Objet.h"

class Inventaire
{
    public:
        Inventaire();
        virtual ~Inventaire();
        std::vector<std::string> getNomsObj() ;
        std::vector<unsigned> getExemplaires() const;
        std::vector<std::string> getType() ;
        std::vector<std::string> getDescription() ;
        std::vector<Objet> getContenu() const;
        void setContenu(std::vector<Objet> objs);
        void setExemplaires(std::vector<unsigned> nbObj);
       // void setType(std::vector<std::string> type);
       // void setDescription(std::vector<std::string> description);
        void ajouterObjet(Objet nom, unsigned nb);
        void refreshInventaire();
        bool checkInventaire();

    protected:

    private:
        std::string m_nom;
        unsigned m_taille;
        std::vector<Objet> m_contenu;
        std::vector<unsigned> m_exemplaires;
       // std::vector<std::string> m_type;
       // std::vector<std::string> m_description;
};

#endif // INVENTAIRE_H
