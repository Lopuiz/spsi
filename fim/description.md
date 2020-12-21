Uno de los retos con los que se encuentran los administradores de sistemas es controlar que no se modifiquen
los archivos del sistema de forma malintencionada. Muchos HIDS tienen módulos para monitorizar la integridad
de los ficheros.

Esta funcionalidad se puede conseguir mediante la utilización de algunos módulos del SO como pueden ser auditd,
inotify o ptrace en caso de los sistemas Linux, o el sistema de auditoría en caso de sistemas Windows. Otra
forma de monitorizar la integridad de los ficheros es mediante el uso de SHA. Este método es el que desarrollaremos
en esta sección.

El funcionamiento básico de un programa de este tipo es el siguiente. Se debe leer los ficheros y directorios que
el usuario desea monitorizar, realiza un escaneo inicial para guardar el estado (hashes y atributos) de los ficheros
a monitorizar. Durante la ejecución se realizan tests periódicos para comprobar si hay nuevos ficheros, si se han
modificado los hash o atributos de los ficheros existentes o se han eliminado ficheros. En caso de encontrar algún
cambio genera una alerta.

En clase se ha aprendido que son los algoritmos hash seguros y que tipos de algoritmos existen actualmente. También
se ha trabajado con la librería OpenSSL en clases de prácticas.

Esto es una prueba de concepto para intentar explicar como funciona un programa de este tipo. Solo es capaz de detectar
el cambio de usuario, grupo, contenido, y eliminación de un fichero pasado por parámetro.

Nota: el fichero debe existir al inicio de la ejecución del programa, y se detecta que el fichero ha sido eliminado
(o movido/renombrado) el programa para la ejecución.
