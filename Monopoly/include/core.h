#pragma once
// forward declare a structure
#define FWDS(type)	struct type; typedef struct type type;

// forward declare an union
#define FWDU(type)	union type; typedef union type type;

// declarations of structures and unions
FWDS(ArrayList)

FWDS(Board)

FWDS(Bot)

FWDS(Field)

FWDS(Game)

FWDU(PlayerController)

FWDS(Player)

FWDS(Realty)

// definitions of other types
typedef unsigned char PlayerType;

typedef unsigned char BoardPrintMode;

typedef unsigned char FieldType;