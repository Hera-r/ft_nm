/mon_projet
│── /src             # Fichiers sources (.c)
│── /include         # Fichiers d'en-tête (.h)
│── /lib             # Bibliothèques tierces (si nécessaire)
│── /bin             # Fichiers binaires et exécutables
│── /tests           # Tests unitaires et fonctionnels
│── /docs            # Documentation du projet
│── /examples        # Exemples d'utilisation
│── /scripts         # Scripts utilitaires (build, CI/CD, etc.)
│── /build           # Fichiers de compilation (souvent ignorés par Git)
│── .gitignore       # Fichiers et dossiers à exclure de Git
│── README.md        # Présentation et instructions du projet
│── Makefile/CMakeLists.txt  # Instructions de compilation
│── LICENSE          # Licence du projet open-source
│── CONTRIBUTING.md  # Guide pour contribuer au projet
│── CHANGELOG.md     # Historique des modifications

--------------------------------------------------------------------
# L'En-tête ELF (ELF Header): le debut du fichier ELF
 Il est défini par la structure [Elf64_Ehdr]
typedef struct {
    unsigned char e_ident[16]; /* Magique ELF et autres infos */
    uint16_t e_type;           /* Type du fichier */
    uint16_t e_machine;        /* Architecture */
    uint32_t e_version;        /* Version du fichier */
    uint64_t e_entry;          /* Adresse du point d’entrée */
    uint64_t e_phoff;          /* Offset du Program Header Table */
    uint64_t e_shoff;          /* Offset du Section Header Table */
    uint32_t e_flags;          /* Flags spécifiques à l’architecture */
    uint16_t e_ehsize;         /* Taille de l’en-tête ELF */
    uint16_t e_phentsize;      /* Taille d’une entrée du Program Header */
    uint16_t e_phnum;          /* Nombre d’entrées du Program Header */
    uint16_t e_shentsize;      /* Taille d’une entrée du Section Header */
    uint16_t e_shnum;          /* Nombre d’entrées du Section Header */
    uint16_t e_shstrndx;       /* Index de la section contenant les noms de sections */
} Elf64_Ehdr;
raha ijery ny structure ELF Header: readelf -h /bin/ls


# La Table des Sections (Section Header Table)
Chaque fichier ELF contient plusieurs sections, stockées dans la Table des Sections. Ces sections contiennent du code, des symboles et d'autres informations utiles.[Elf64_Shdr]
typedef struct {
    uint32_t sh_name;      /* Nom de la section (index dans la table des chaînes) */
    uint32_t sh_type;      /* Type de la section */
    uint64_t sh_flags;     /* Attributs */
    uint64_t sh_addr;      /* Adresse virtuelle (si mappé en mémoire) */
    uint64_t sh_offset;    /* Offset dans le fichier */
    uint64_t sh_size;      /* Taille de la section */
    uint32_t sh_link;      /* Index d’une autre section (dépend du type) */
    uint32_t sh_info;      /* Information supplémentaire (dépend du type) */
    uint64_t sh_addralign; /* Alignement */
    uint64_t sh_entsize;   /* Taille d’une entrée si la section contient une table */
} Elf64_Shdr;

* Les sections principales :

Nom	                Description
---------------------------------------------------------------------
.text	    Contient le code machine du programme.
.data	    Contient des données initialisées (variables globales).
.bss	    Contient des données non initialisées.
.rodata	    Contient des données en lecture seule.
.symtab	    Contient la table des symboles.
.strtab	    Contient les chaînes de caractères associées aux symboles.
.shstrtab	Contient les noms des sections.
----------------------------------------------------------------------------
raha ijery ireo karana section: readelf -S /bin/ls

# La Table des Symboles (Symbol Table)
Ces symboles sont stockés dans la table des symboles, qui est définie par [Elf64_Sym]

typedef struct {
    uint32_t st_name;  /* Nom du symbole (index dans .strtab) */
    uint8_t  st_info;  /* Type et liaison */
    uint8_t  st_other; /* Visibilité */
    uint16_t st_shndx; /* Section index */
    uint64_t st_value; /* Adresse du symbole */
    uint64_t st_size;  /* Taille du symbole */
} Elf64_Sym;





