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

/*
NAME
    ELF – Executable and Linkable Format

SYNOPSIS
    Un fichier ELF est organisé en plusieurs parties :
    1. L’en-tête ELF (ELF Header)
    2. La table des sections (Section Header Table)
    3. La table des symboles (Symbol Table)
    4. Éventuellement d’autres informations (segments, relocations, etc.)

DESCRIPTION

--------------------------------------------------------------------------------
# L’En-tête ELF (ELF Header)

Le début d’un fichier ELF est décrit par la structure Elf64_Ehdr :
*/
typedef struct {
    unsigned char e_ident[16]; /* Magie ELF et autres informations */
    uint16_t e_type;           /* Type du fichier (relocatable, exécutable…) */
    uint16_t e_machine;        /* Architecture (x86_64, ARM, etc.) */
    uint32_t e_version;        /* Version du fichier ELF (généralement 1) */
    uint64_t e_entry;          /* Adresse virtuelle du point d’entrée */
    uint64_t e_phoff;          /* Offset de la table des segments (Program Header) */
    uint64_t e_shoff;          /* Offset de la table des sections (Section Header) */
    uint32_t e_flags;          /* Flags spécifiques à l’architecture */
    uint16_t e_ehsize;         /* Taille de cet en-tête ELF */
    uint16_t e_phentsize;      /* Taille d’une entrée dans la table des segments */
    uint16_t e_phnum;          /* Nombre d’entrées dans la table des segments */
    uint16_t e_shentsize;      /* Taille d’une entrée dans la table des sections */
    uint16_t e_shnum;          /* Nombre d’entrées dans la table des sections */
    uint16_t e_shstrndx;       /* Index de la section contenant les noms de sections */
} Elf64_Ehdr;

/*
 Champs principaux :
    - e_ident[16]  : Contient la “magie ELF” (0x7F, 'E', 'L', 'F'), la classe (32/64 bits), l’endianness, etc.
    - e_type       : Type de fichier (ET_REL, ET_EXEC, etc.).
    - e_machine    : Architecture (EM_X86_64, EM_ARM, etc.).
    - e_version    : Version (toujours 1 pour ELF).
    - e_entry      : Adresse de la routine de démarrage (si exécutable).
    - e_phoff      : Offset de la table des segments dans le fichier.
    - e_shoff      : Offset de la table des sections dans le fichier.
    - e_flags      : Flags spécifiques à l’architecture.
    - e_ehsize     : Taille de l’en-tête ELF.
    - e_phentsize  : Taille d’une entrée du Program Header.
    - e_phnum      : Nombre d’entrées dans le Program Header.
    - e_shentsize  : Taille d’une entrée du Section Header.
    - e_shnum      : Nombre d’entrées dans le Section Header.
    - e_shstrndx   : Index de la section .shstrtab (noms de sections).

Pour afficher l’en-tête ELF d’un binaire :
    readelf -h /bin/ls

--------------------------------------------------------------------------------
# La Table des Sections (Section Header Table)

Chaque fichier ELF est découpé en sections décrites dans la table des sections (Section Header Table),
définie par Elf64_Shdr :
*/
typedef struct {
    uint32_t sh_name;      /* Index du nom de la section dans .shstrtab */
    uint32_t sh_type;      /* Type de la section (SHT_PROGBITS, SHT_SYMTAB, etc.) */
    uint64_t sh_flags;     /* Attributs (exécutable, allocable, etc.) */
    uint64_t sh_addr;      /* Adresse virtuelle si la section est mappée */
    uint64_t sh_offset;    /* Offset dans le fichier */
    uint64_t sh_size;      /* Taille de la section en octets */
    uint32_t sh_link;      /* Index d'une autre section (dépend du type) */
    uint32_t sh_info;      /* Infos supplémentaires (dépend du type) */
    uint64_t sh_addralign; /* Alignement en mémoire */
    uint64_t sh_entsize;   /* Taille d’une entrée si la section est une table */
} Elf64_Shdr;

/*
 Champs principaux :
    - sh_name      : Index vers la chaîne de caractères du nom dans .shstrtab.
    - sh_type      : Type de la section (code, données, symboles...).
    - sh_flags     : Indique si la section est exécutable, allocable, etc.
    - sh_addr      : Adresse virtuelle de la section en mémoire (si chargé).
    - sh_offset    : Offset (en octets) depuis le début du fichier ELF.
    - sh_size      : Taille de la section en octets.
    - sh_link      : Lien vers une autre section (ex. pour symboles ou relocations).
    - sh_info      : Informations supplémentaires dépendant du type.
    - sh_addralign : Alignement mémoire requis.
    - sh_entsize   : Si la section est une table, taille de chaque entrée.

Exemples de sections courantes :

    Nom         Description
    .text       Contient le code machine (instructions).
    .data       Contient des données initialisées.
    .bss        Contient des données non initialisées (réservées en mémoire).
    .rodata     Contient des données en lecture seule.
    .symtab     Table des symboles (dans les fichiers objets).
    .strtab     Chaînes de caractères associées aux symboles.
    .shstrtab   Chaînes de caractères pour les noms des sections.

Pour afficher la liste des sections d’un binaire :
    readelf -S /bin/ls

--------------------------------------------------------------------------------

# La Table des Symboles (Symbol Table)

La table des symboles contient les informations sur les symboles (fonctions, variables, etc.).
Elle est décrite par Elf64_Sym :
*/
typedef struct {
    uint32_t st_name;  /* Index vers le nom du symbole dans .strtab */
    uint8_t  st_info;  /* Type (fonction, objet) et liaison (global, local) */
    uint8_t  st_other; /* Visibilité du symbole */
    uint16_t st_shndx; /* Index de la section associée au symbole */
    uint64_t st_value; /* Valeur/adresse du symbole */
    uint64_t st_size;  /* Taille en octets (surtout pour les données) */
} Elf64_Sym;

/*
 Champs principaux :
    - st_name   : Index vers la chaîne du nom (dans .strtab).
    - st_info   : Combine le type et la liaison du symbole.
    - st_other  : Détermine la visibilité (default, hidden, etc.).
    - st_shndx  : Indique dans quelle section se trouve le symbole.
    - st_value  : Adresse ou valeur associée au symbole.
    - st_size   : Taille du symbole.

--------------------------------------------------------------------------------
EXEMPLES :

    Visualiser l’en-tête ELF :
        readelf -h /bin/ls

    Lister les sections d’un binaire :
        readelf -S /bin/ls

    Lister les symboles présents :
        readelf -s /bin/ls

--------------------------------------------------------------------------------

nm /usr/lib/gcc/x86_64-linux-gnu/13/libitm.a



#define ARMAG "!<arch>\n"
#define SARMAG 8

struct ar_hdr {
    char ar_name[16];
    char ar_date[12];
    char ar_uid[6];
    char ar_gid[6];
    char ar_mode[8];
    char ar_size[10];
    char ar_fmag[2];
};

Début du fichier .a
   ↓
   +-------------+-------------+----------+---+-------------+ ...
   | ar_hdr(1)   | Données(1)  | padding? |   | ar_hdr(2)   | ...
   +-------------+-------------+----------+---+-------------+ ...
                            ↑
                        (fin du membre 1)

+-------------------------------------+
|   Début de l'archive ".a"           |
|   "!<arch>\n" (8 octets)            |
+-------------------------------------+
|   En-tête ar_hdr (membre 1)         |
+-------------------------------------+
|   Contenu du membre 1               |
|   (peut-être un ELF, ou un /SYMDEF) |
+-------------------------------------+
|   [padding éventuel si taille impaire]
+-------------------------------------+
|   En-tête ar_hdr (membre 2)         |
+-------------------------------------+
|   Contenu du membre 2 (peut-être ELF)
+-------------------------------------+
           ...
