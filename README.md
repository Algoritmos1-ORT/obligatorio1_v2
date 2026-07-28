# obligatorio1_v2
Reedición del primer obligatorio

## Compilación con CMake

Desde la raíz del proyecto, configurar y compilar:

```bash
cmake -S . -B build
cmake --build build
```

El ejecutable queda disponible en `build/obligatorio1`. Para ejecutarlo:

```bash
./build/obligatorio1
```

Para recompilar luego de modificar archivos, basta con ejecutar nuevamente:

```bash
cmake --build build
```

## VSCode
Desde el Visual Studio Code, con las extensiones recomendadas que posiblemente sugiera por defecto, se puede hacer compilar, ejecutar, o debuggear con los íconos debajo:

![VSCode tools para CMake](./assets/images/vscode.png)

## Ejecutar pruebas con Catch2

El ejecutable usa Catch2. Sin argumentos ejecuta todas las pruebas:

```bash
./build/obligatorio1
```

Para ejecutar una prueba específica, indicar su etiqueta o su nombre. Por ejemplo:

```bash
./build/obligatorio1 "[PruebaSuma]"
```

Para ejecutar todas las pruebas asociadas a un archivo, usar la etiqueta `file`:

```bash
./build/obligatorio1 "[file:listas]"
./build/obligatorio1 "[file:arboles]"
./build/obligatorio1 "[file:comienzo]"
```

Por defecto se usa el reporte de consola. Para una salida compacta, agregar la opción `--reporter`:

```bash
./build/obligatorio1 --reporter compact
```
