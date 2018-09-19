# Tp0---Algo-II

Comentarios generales para el informe:

Se decidio hacer un arreglo que querys para las comparaciones, ademas de un arreglo de 
nombres de querys para brindar al usuario la opcion de consultar por varios sensores.

Se han implementado getters y setters para obtener datos de los atributos que son privados.
Tambien se implementaron templates para los arreglos, esto fue una ventaja ya que 
se utilizaron varios arreglos de distintos tipos y no fue necesario realizar una 
clase arreglo para cada tipo de variable. 

Segun el formato del archivo de texto presentado en el informe, la primer linea contiene 
los nombres de los sensores, estas se van a ubicar como columnas. En las siguientes lineas se 
encuentran los datos de los sensores, en cada linea se encuentra la misma fila de datos
para las distintas columnas de sensores.

/********************* Mensajes de error para el archivo de salida ************************/
//  "NO DATA"    ---> caso en que no hay ningun dato en el rango indicado.
//  "BAD QUERY"  ---> caso en que se ingresa un formato incorrecto.
//  "UNKNOW ID"  ---> caso en que se ingresa mal el nombre del sensor o no exixte.
/******************************************************************************************/

Recordar el caso en que no hay un dato en el vector de datos, no se cuenta en el promedio.
Tener en cuenta el caso del guion "-" que significa que no hay ningun dato. Esto es en el query,
en este caso se deben realizar los calculos por todos los sensores, ya que no se esta especificando
cual.


