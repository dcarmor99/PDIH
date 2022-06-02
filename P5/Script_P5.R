install.packages('tuneR', dep=TRUE)
install.packages('seewave', dep=TRUE)

library(tuneR)
library(seewave)
library(audio)


# Ejercicio 1 : Reproducir 2 archivos .mp3 diciendo mi nombre y apellidos

nombre <- readMP3('./nombre.mp3')
nombre
listen(nombre)


apellidos <- readMP3('./apellidos.mp3')
apellidos
listen(apellidos)

# Ejercicio 2 : Dibujar la forma de onda de ambos sonidos
plot( extractWave(apellidos, from = 1, to = length(apellidos)), main="Apellidos" )
plot( extractWave(nombre, from = 1, to = length(nombre)), main="Nombre" )

# Ejercicio 3 : Obtener la información de las cabeceras de ambos sonidos.

str(apellidos)
str(nombre)

# Ejercicio 4 : Unir ambos sonidos en uno nuevo

nombre@left <- nombre@left * (max(apellidos@left)/max(nombre@left))
nombre@right <- nombre@right * (max(apellidos@right)/max(nombre@right))
nombre_apellidos <- pastew(apellidos, nombre, output="Wave")

listen(nombre_apellidos)

plot( extractWave(nombre_apellidos, from = 1, to = length(nombre_apellidos)), main="Nombre+Apellidos" )

export(nombre_apellidos)



