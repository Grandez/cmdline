# An holistic proposal and tool to parse command line input

## disclaimer

Aqui el disclaimer

## Motivacion

Cualquier programa susceptible de ser ejecutado a traves de una linea de comandos necesita una serie de parámetros de entrada de lo contario siempre generaria el mismo resultado.

Ahora bien, dependiendo del sistema operativo, la forma habitual de indicar estos parámetros varía; es mas, cada programador podría definir un nuevo sistema de entrada de parámetros. Esto obliga, o al menos debería, a que un programa multiplataforma debería adecuarse a cada sistema para aceptar el estilo de cada uno de ellos.

### sistemas nix

Tipicamente estos sistemas utilizan los simbolos '-' o '--' para indicar un parámetro, donde:

- La primera forma se aplica a parámetros definidos por un solo caracter y permite además concatenarlos
- La segunda forma se entiende como parámetro extendido definido por una palabra

Ejemplos:

`command -h`
`command --help`
`command -af` 
`command -a -f`
`command -o output_file`

### sistemas windows

`command /h`
`command /-Y`
`command /D:value`
`command /o output_file`

y actualmente con Powershell tambien se soportan las formas '-' y '--' y en algunos casos combinadas con ':'

### ZOS y otros

Otros sistemas operativos soportan otros metodos. Por ejemplo zOS usa /_characters_, donde _characters_ es el mínimo numero de caracteres necesario para identificar un comando.

Por ejemplo `/pre pattern` y `/preffix pattern` son equivalentes en el sentido de que no existe mas que un comando que empiece por la secuencia `pre`

## Definiciones

Introduzcamos algunas definiciones:

**Parametro** o **argumento** son sinonimos y es cualquier elemento que aparece despues del comando en si mismo 

Ahora bien, estos parámetros pueden ser de tres tipos:

1. Datos de entrada
2. Opciones
3. Flags

Y cada programa puede aceptar un determinado número de opciones, incluida ninguna, y de flags, incluidos ninguno, pero en el caso de que exista al menos uno, este, por definición debe asumir un valor por defecto cuando no es especificado en la linea de comandos.

### Datos de entrada

Es cualquier elemento o secuencia de ellos que debe ser procesado por el programa.

Por ejemplo: `cat fichero.txt` mostrara por pantalla el contenido del fichero fichero.txt

### Opciones

Es cualquier elemento o secuencia de ellos que modifica o afecta al comportamiento del programa aportándole algun tipo de información

Por ejemplo: `grep -e _pattern_` o `grep --regexp _pattern_` indica a grep que patrón usar

### Flags

Es cualquier elemento que activa o desactiva alguna característica o funcionalidad del programa.
El caso mas típico seria el flag: `-h` o `--help` que indica al programa que muestre su ayuda

Otros ejemplos podrían ser:

`command -v` o `command --verbose` que suele usarse para generar información de progreso
`command -s` o `command --silent` que suele usarse para evitar que se genere esa información

Notese que estos flags son complementarios; es decir, afectan a las misma funcionalidad.

## Incoherencias

Con estos sistemas se plantean los siguientes problemas:

Dado un parametro P o Parameter:

- ¿Como podemos saber si es un flag o una opcion?
- Si es un flag, ¿Activa o desactiva esa funcionalidad? (Vease el caso -verbose y -silent)
- ¿Por que tengo que elegir como usuario, y controlar como desarrollador, las dos opciones -P y --Parameter?
- En el caso de que no exista una version corta del parámetro, ¿Por que necesito escribir Parameter si con la primera letra ya seria suficiente? 
- Cuanto mas caracteres tenga que escribir mas posible es que introduzca un error de tipografia

# Propuesta

El siguiente esquema propone resolver estas "deficiencias" y clarificar de cara al usuario los significados de cada parámetro:

1. Un flag se prefija siempre con los signos + o - y su significado es **siempre** el mismo: + activa la funcionalidad y - la desactiva.
2. Dado que los flags no necesitan información asociada se pueden concatenar en una secuencia de caracteres con la unica condicion de que ninguno de ellos empiece por el mismo caracter
3. Una opcion se prefija **siempre** con la barra / y su valor asociado se establece en la siguiente palabra
4. Cualquier parámetro queda definido en el momento en el que no existe duda acerca de la intención del usuario; es decir, no es necesario introducir el nombre completo del parámetro

Por ultimo, y como consejo, el manual de usuario o la ayuda en linea, deberia indicar los valores por defecto de todos los flags y opciones soportadas por el programa

