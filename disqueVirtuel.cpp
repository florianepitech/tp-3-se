/**
 * \file disqueVirtuel.cpp
 * \brief Implémentation d'un disque virtuel.
 * \author ?
 * \version 0.1
 * \date  2023
 *
 *  Travail pratique numéro 3
 *
 */

#include "disqueVirtuel.h"
#include <iostream>
#include <string>
//vous pouvez inclure d'autres librairies si c'est nécessaire

namespace TP3 {

    DisqueVirtuel::DisqueVirtuel() {

    }

    DisqueVirtuel::~DisqueVirtuel() {
    }

    /**
     * La méthode de formatage vient effacer le disque virtuel et créer
     * le système de fichier UFS.
     * - Cette méthode doit initialiser le bitmap des blocs libres dans le bloc 2. (OK)
     * - Initialiser le bitmap des i-nodes libres dans le bloc 3. (OK)
     * - Marquez tous les blocs de 0 à 23 comme non-libres, puisqu’ils seront utilisés par le système de fichier. (OK)
     * - Créer les i-nodes dans les blocs de 4 à 23 (1 par bloc).  (OK)
     * - Marquez tous les i-nodes de 1 à 19 comme libres (0 non libre)
     * - Créer le répertoire racine / avec l’i-node 1. Il est à noter qu’il
     *   n'est pas nécessaire de sauvegarder le nom du répertoire racine,
     *   car il est unique.
     * @return Cette méthode retourne soit 1 pour succès soit 0 pour échec.
     */
    int DisqueVirtuel::bd_FormatDisk() {
        this->m_blockDisque.clear();
        for (int i = 0; i < N_BLOCK_ON_DISK; i++) {
            this->m_blockDisque.push_back(Block());
        }
        //Initialisation du bitmap des blocs libres dans le bloc 2 (OK)
        this->m_blockDisque[FREE_BLOCK_BITMAP].m_type_donnees = S_IFBL;

        //Initialisation du bitmap des i-nodes libres dans le bloc 3 (OK)
        this->m_blockDisque[FREE_INODE_BITMAP].m_type_donnees = S_IFIL;
        //Marquez tous les blocs de 0 à 23 comme non-libres (OK)
        for (int i = 0; i < 24; i++) {
            // A revoir car cela ecrase la valeur de m_type_donnees de FREE_BLOCK_BITMAP et FREE_INODE_BITMAP
            this->m_blockDisque[i].m_type_donnees = S_IFIN;
        }
        //Créer les i-nodes dans les blocs de 4 à 23 (1 inode par bloc) (OK)
        for (int i = 4; i < 24; i++) {
            this->m_blockDisque[i].m_inode = new iNode(
                    i - 4,
                    S_IFREG,
                    0,
                    0,
                    i
            );
        }
        //Marquez tous les i-nodes de 1 à 19 comme libres (0 non libre) (A verifier)
        for (int i = 1; i < 20; i++) {
            this->m_blockDisque[FREE_BLOCK_BITMAP].m_bitmap[i] = false;
        }
        //Créer le répertoire racine / avec l’i-node 1
        addRootDirectory();
        std::cout << "Formatage du disque réussi" << std::endl;
        return 0;
    }

    /**
     * Le premier champ indique un répertoire (d)
     * ou un fichier (-). Le deuxième champ est
     * le nom du fichier ou du sous-répertoire.
     * Ceci est suivi de la taille (en octets),
     * le numéro d’i-node et le nombre de liens.
     * La taille du répertoire racine est 112 octets,
     * car on utilise 4 entrées dirEntry (4 * 28 pour les répertoires ., .., doc et le fichier a.txt).
     * La taille du répertoire doc est 56 octets, car on utilise 2 entrées
     * dirEntry (2 * 28 pour les répertoires . et ..). La taille du fichier a.txt est 0, car il
     * est vide. Le nombre de liens (nlink) pour l’i-node 1 est 3, car elle est référencée
     * deux fois dans le répertoire racine et une fois dans le répertoire doc (répertoire parent).
     * Le nombre de liens pour l’i-node 2 est 2, car elle est référence une fois dans le répertoire
     * racine et une fois dans le répertoire doc (répertoire courant). Le nombre de liens pour
     * l’i-node 3 est 1, car elle référencée seulement une seule fois dans le répertoire racine
     * concernant le fichier a.txt.
     * @param p_DirLocation Le chemin d'accès du répertoire à lister.
     * @return Cette méthode retourne un string contenant le formatage du contenue à afficher.
     */
    std::string DisqueVirtuel::bd_ls(const std::string &p_DirLocation) {

        return "";
    }

    /**
     * Cette méthode créer le répertoire pDirName. Si le chemin
     * d’accès à pDirName est inexistant, ne faites rien
     * et retournez 0, par exemple si on demande de
     * créer le répertoire /doc/tmp/test et que le
     * répertoire /doc/tmp n’existe pas. Assurez-vous que
     * l’i-node correspondant au répertoire est marqué comme
     * répertoire (st_mode est à S_IFDIR). Si le répertoire
     * pDirName existe déjà, retournez avec 0. Assurez-vous
     * aussi que le répertoire contiennent les deux répertoires
     * suivants : « . » et « .. ». N’oubliez-pas d’incrémenter
     * st_nlink pour le répertoire parent « .. ».
     * @param p_DirName Le nom du répertoire à créer.
     * @return Cette méthode retourne soit 1 pour succès soit 0 pour échec.
     */
    int DisqueVirtuel::bd_mkdir(const std::string &p_DirName) {

        return 0;
    }

    /**
     * Cette méthode vient créer un fichier vide (taille=0, donc sans bloc de données)
     * avec le nom et à l’endroit spécifié par le chemin d’accès pFilename. Par exemple,
     * si pFilename est égal à /doc/tmp/a.txt, vous allez créer le fichier a.txt dans
     * le répertoire /doc/tmp. Assurez-vous que ce répertoire existe, et que l’i-node
     * correspondant au fichier est marqué comme fichier (st_mode est à S_IFREG).
     * Assurez-vous aussi que ce fichier n’existe pas déjà.
     * @param p_DirName Le nom du répertoire à créer.
     * @return Cette méthode retourne soit 1 pour succès soit 0 pour échec.
     */
    int DisqueVirtuel::bd_create(const std::string &p_FileName) {
        return 0;
    }

    /**
     * Cette méthode provoque la délétion d’un fichier ou d’un répertoire.
     * Attention! Dans UFS, la délétion se fait en réduisant le nombre de
     * lien (st_nlink) et en détruisant l’entrée dans un fichier de répertoire.
     * Si st_nlink tombe à zéro, vous devez libérer les blocs de données
     * associés à l’i-node, et libérer aussi ce dernier. Si après bd_rm le
     * nombre de lien n’est pas zéro, vous ne devez pas libérer l’i-node,
     * puisqu’il est utilisé ailleurs. Si le string pFilename correspond à
     * un répertoire, vous ne pouvez le détruire que si il est vide, i.e.
     * ne contient pas d’autres répertoires autres que « . » et « .. ». Si
     * le répertoire n’est pas vide, ne faites rien et retournez 0.
     * N’oubliez-pas de décrémenter st_nlink pour le répertoire parent « .. »,
     * si un répertoire est retiré.
     * @param p_Filename Le nom du fichier à supprimer.
     * @return Cette méthode retourne soit 1 pour succès soit 0 pour échec.
     */
    int DisqueVirtuel::bd_rm(const std::string &p_Filename) {
        // Localiser l'inode qui contient le fichier à supprimer

        return 1;
    }

    // Vous pouvez ajouter ici d'autres méthodes publiques

    // Ajouté par Florian
    Block* DisqueVirtuel::getBlock(std::string p_DirLocation) {
        std::vector<std::string> path =
        // auto block_root = this->m_blockDisque[ROOT_INODE];
        // for (auto dirEntry : block_root.m_dirEntry) {
        //     if (dirEntry.m_filename == p_Filename) {
        //     }
        // }
        return nullptr;
    }


    // Ajouté par Florian
    void DisqueVirtuel::addRootDirectory() {
        this->m_blockDisque[5].m_type_donnees = S_IFDIR;
        this->m_blockDisque[5].m_inode = new iNode(
                1,
                S_IFDIR,
                0,
                0,
                ROOT_INODE
        );
        this->m_blockDisque[5]->dirEntry = new dirEntry(
                1,
                "/"
        );
        // Mettre a jour la liste des inode libres (bitmap)
        this->m_blockDisque[FREE_INODE_BITMAP].m_bitmap[1] = false;
    }

}//Fin du namespace
