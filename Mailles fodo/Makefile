CXX = g++
CC = $(CXX)

CXXFLAGS += -std=c++11
CXXFLAGS += -pedantic -Wall     # pour les purs et durs
CXXFLAGS += -g                  # pour debugger
#CXXFLAGS += -pg                 # pour profiler
#LDFLAGS  += -pg                 # pour profiler
#CXXFLAGS += -O2                 # pour optimiser la vitesse


all: ExerciceP13 ExerciceP14 TestAccel_Maille_Fodo

Vecteur3D.o: Vecteur3D.cc Vecteur3D.h

particules.o: particules.cc particules.h Vecteur3D.h  constante.h dessinable.h support_a_dessin.h Case.h

element.o : Vecteur3D.h particules.h element.cc element.h constante.h dessinable.h support_a_dessin.h Case.h

accelerateur.o : accelerateur.cc particules.h element.h constante.h dessinable.h support_a_dessin.h faisceau.h	Case.h

text_viewer.o : text_viewer.cc text_viewer.h support_a_dessin.h element.h accelerateur.h particules.h faisceau.h

faisceau.o : faisceau.h faisceau.cc dessinable.h support_a_dessin.h accelerateur.h particules.h Case.h

ExerciceP13 : ExerciceP13.o Vecteur3D.o particules.o element.o faisceau.o accelerateur.o Case.o

ExerciceP13.o : ExerciceP13.cc  accelerateur.h particules.h element.h constante.h dessinable.h support_a_dessin.h faisceau.h Case.h

Case.o : Case.cc particules.o Vecteur3D.o

ExerciceP14 : ExerciceP14.o Vecteur3D.o particules.o element.o faisceau.o accelerateur.o Case.o

ExerciceP14.o : ExerciceP14.cc  accelerateur.h particules.h element.h constante.h dessinable.h support_a_dessin.h faisceau.h Case.h

TestAccel_Maille_Fodo: TestAccel_Maille_Fodo.o Vecteur3D.o particules.o element.o faisceau.o accelerateur.o Case.o

TestAccel_Maille_Fodo.o: TestAccel_Maille_Fodo.cc accelerateur.h particules.h element.h constante.h dessinable.h support_a_dessin.h faisceau.h Case.h
