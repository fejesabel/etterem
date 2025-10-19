#ifndef ASZTAL_H_INCLUDED
#define ASZTAL_H_INCLUDED

#include "tipusok.h"

extern void asztal_hozzaad(ElemAsztal** pEleje, Asztal sUjAsztal);
extern void asztal_felszabadit(ElemAsztal* pEleje);
extern void asztal_hozzaad_felhaszn(ElemAsztal** pEleje);
extern void asztal_torles_felhaszn(ElemAsztal** pEleje);
extern void asztal_foglaltsag_felhaszn(ElemAsztal* pEleje);
extern void kirajz_terkep(ElemAsztal* pEleje);

#endif // ASZTAL_H_INCLUDED
