# So_Long - 42 Project 🎮

<p align="center">
  <img src="textures/preview.gif" alt="Game Preview" width="600"/>
</p>

## 📝 Descripción

So_Long es un pequeño juego 2D desarrollado como parte del currículum de 42. El objetivo es crear un juego básico donde un jugador debe recolectar todos los coleccionables y llegar a la salida en el menor número de movimientos posible.

## 🎯 Objetivos del Proyecto

- Gestión de ventanas y eventos
- Manejo de texturas y sprites
- Validación de mapas
- Gestión de memoria eficiente
- Implementación de mecánicas básicas de juego

## 🛠️ Tecnologías Utilizadas

- C
- MinilibX (Biblioteca gráfica de 42)
- Make

## 🏗️ Arquitectura del Proyecto

so_long/
├── mandatory/
│ ├── inc/ # Headers
│ └── src/
│ ├── core/ # Funcionalidades principales
│ │ ├── init/ # Inicialización
│ │ └── textures/ # Gestión de texturas
│ ├── graphics/ # Renderizado
│ └── utils/ # Utilidades
├── maps/ # Mapas del juego
├── textures/ # Assets gráficos
└── libft/ # Biblioteca de utilidades

## 🎮 Controles

- `W` o `↑`: Mover arriba
- `S` o `↓`: Mover abajo
- `A` o `←`: Mover izquierda
- `D` o `→`: Mover derecha
- `ESC`: Salir del juego

## 🗺️ Formato del Mapa

Los mapas deben seguir estas reglas:
- Extensión `.ber`
- Rectangular y cerrado por muros
- Contener:
  - `1`: Muros
  - `0`: Espacio vacío
  - `P`: Jugador (solo uno)
  - `E`: Salida
  - `C`: Coleccionables

Ejemplo:
```
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
```

## 🚀 Compilación y Ejecución
Compilar el juego
make
Ejecutar con un mapa
./so_long maps/map1.ber

## 🎨 Características Implementadas

- [x] Movimiento fluido
- [x] Contador de movimientos
- [x] Validación completa de mapas
- [x] HUD con información del juego
- [x] Gestión de colisiones
- [x] Mensajes en terminal
- [x] Limpieza de memoria

## 🧪 Validaciones del Mapa

- Verificación de caracteres válidos
- Comprobación de mapa rectangular
- Validación de muros
- Control de elementos únicos (jugador, salida)
- Verificación de tamaño mínimo y máximo
- Comprobación de ruta válida

## 📚 Recursos Utilizados

- [MinilibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [42 Docs](https://harm-smits.github.io/42docs/)
- [Pixel Art Tools](https://www.piskelapp.com/)

## 👤 Autor

- Github: [@cristiancarrero](https://github.com/cristiancarrero)
- 42 Intra: ccarrero

## 📄 Licencia

Este proyecto está licenciado bajo la Licencia MIT - ver el archivo [LICENSE](LICENSE) para más detalles.