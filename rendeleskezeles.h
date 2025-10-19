#ifndef RENDELESKEZELES_H_INCLUDED
#define RENDELESKEZELES_H_INCLUDED

#include "tipusok.h"

extern void rendeles_felszabadit(ElemRendeles* pEleje);
extern void rendeles_hozzaad(ElemRendeles** pEleje, Rendeles sUjRendeles);
extern void rendeles_hozzaad_felhaszn(ElemAsztal* pEleje_asztal, ElemMenu* pEleje_menu);


#endif // RENDELESKEZELES_H_INCLUDED
