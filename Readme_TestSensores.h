//  Para el caso de Test_RedSensores.cpp:
//  Se realizo la prueba para esta clase, se agregaron algunos metodos para esto.
//  Esta clase requiere de otras para su funcionamiento, se utilizaron casi todas las otras clases.

//  Mientras tanto se deja la version para compilar sin makefile.

//  Para compilar:
//  g++ -Wall -g -o tt Test_RedSensores.cpp RedSensores.cpp TemplateArray.h Query.cpp Sensor.cpp Data.cpp SegmentTree.cpp cmdline.cpp

//  Para ejecutar: 
//  ./tt --data prueba.csv

// Comentarios: la clase data toma los datos en un rango determinado, en el caso particular 
// en el que se necesite un solo dato de un sensor, se utiliza el metodo GetDatosSinProcesar().
// Este metodo define a los rangos en la misma posicion y hace que se pueda consultar por 
// el elemento del sensor deseado.

// En el testeo, se tomo la clase data y en caso de que no tenga valores no definidos, 
// no se imprimen. 
