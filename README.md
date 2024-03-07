# Juego-nave
Proyecto II, Juego de 3 niveles sobre una nave espacial que debe esquivar obstáculos y recoger objetos para ganar.

# Problemática
Una empresa nos ha encargado el desarrollo de un juego espacial. En este juego, una nave debe atravesar el espacio para entregar una carga de plantas al planeta Marte.

# Especificaciones
El juego incluirá el espacio exterior, la nave, asteroides, planetas, objetos de interés y hoyos negros. La nave se enfrentará a diferentes peligros, como lluvia de asteroides, planetas no identificados y hoyos negros, cada uno con sus características únicas que pueden dañar la estructura de la nave. Las cápsulas de vida son esenciales para mantener con vida a los tripulantes de la nave, así como la velocidad de la nave, distancia entre la nave y el peligroso objeto o fenómeno cósmico y la cantidad de misiles.
El juego consta de tres niveles.

## Nivel 1
En este nivel, el jugador atraviesa un área con algunos planetas, compuestos por distintos materiales. Algunos planetas pueden ser destruidos (sin vida), mientras que otros no, debido a que tienen vida.
La nave debe evadir los planetas si la distancia entre ambos está entre 8000 y 10000 km, y la velocidad de la nave supera los 12000 km/h. Si la distancia es de 8000 km o menos, sin importar la velocidad, la nave choca con el planeta y pierde el juego. Si la distancia es de 10000 km o más, sin importar la velocidad, la nave continúa su viaje.
Además, aparecerán objetos de interés. Por cada objeto capturado (siempre y cuando la distancia entre la nave y el objeto no exceda los 6000 km), la nave gana 5 cápsulas de vida, sin importar la velocidad. Sin embargo, hay una penalización de 3 cápsulas de vida por intentar capturar objetos sin cumplir las condiciones necesarias.
La nave puede destruir planetas sin vida si la distancia entre la nave y el planeta es igual o menor a 8000 km, y la velocidad de la nave es de 12000 km/h o más. Por cada planeta destruido, la nave pierde 25 cápsulas de vida y 50 misiles. Intentar destruir un planeta sin cumplir los requisitos necesarios resulta en una penalización de 15 cápsulas de vida y 30 misiles.
La nave comienza con 2000 cápsulas de vida y 8000 misiles. Este nivel se supera si la nave queda con al menos 7800 misiles y al menos 1900 cápsulas de vida. El jugador pierde si la nave tiene menos de 7800 misiles o menos de 1900 cápsulas de vida.

## Nivel 2
La nave espacial se adentra en un área repleta de peligros cósmicos: ¡los asteroides! Estos gigantes rocosos representan un desafío adicional para los hábiles pilotos que se aventuran en el espacio exterior en busca de nuevas aventuras.
La nave debe evadir los asteroides si la distancia entre ambos está entre 6000 y 8000 km, y la velocidad de la nave supera los 20000 km/h. Si la distancia es de 6000 km o menos, sin importar la velocidad, la nave choca con el asteroide y pierde el juego. Si la distancia es de 8000 km o más, sin importar la velocidad, la nave continúa su viaje.
Además, aparecerán objetos de interés. Por cada objeto capturado (siempre y cuando la distancia entre la nave y el objeto no exceda los 4000 km), la nave gana 10 cápsulas de vida, sin importar la velocidad. Sin embargo, hay una penalización de 7 cápsulas de vida por intentar capturar objetos sin cumplir las condiciones necesarias.
La nave puede destruir asteroides si la distancia entre la nave y el asteroide es igual o menor a 6000 km, y la velocidad de la nave es de 20000 km/h o más. Por cada asteroide destruido, la nave pierde 30 cápsulas de vida y 60 misiles. Intentar destruir un asteroide sin cumplir los requisitos necesarios resulta en una penalización de 20 cápsulas de vida y 40 misiles.
La nave comienza con 1900 cápsulas de vida y 7800 misiles. Este nivel se supera si la nave queda con al menos 7400 misiles y al menos 1500 cápsulas de vida. El jugador pierde si la nave tiene menos de 7400 misiles o menos de 1500 cápsulas de vida.

## Nivel 3
La nave espacial se enfrentará a uno de los fenómenos más misteriosos y peligrosos del universo: los hoyos negros. Estas formaciones cósmicas imponentes representan un desafío supremo para los intrépidos pilotos que se aventuran más allá de los límites conocidos del espacio.
La nave espacial se enfrentará a uno de los fenómenos más misteriosos y peligrosos del universo: los hoyos negros. Estas formaciones cósmicas imponentes representan un desafío supremo para los intrépidos pilotos que se aventuran más allá de los límites conocidos del espacio.
La nave debe evadir los hoyos negros si la distancia entre ambos está entre 4000 y 6000 km, y la velocidad de la nave supera los 28000 km/h. Si la distancia es de 4000 km o menos, sin importar la velocidad, la nave choca con el hoyo negro y pierde el juego. Si la distancia es de 6000 km o más, sin importar la velocidad, la nave continúa su viaje.
Además, aparecerán objetos de interés. Por cada objeto capturado (siempre y cuando la distancia entre la nave y el objeto no exceda los 2000 km), la nave gana 15 cápsulas de vida, sin importar la velocidad. Sin embargo, hay una penalización de 35 cápsulas de vida por intentar capturar objetos sin cumplir las condiciones necesarias para ello.
La nave puede destruir hoyos negros si la distancia entre la nave y el hoyo negro es igual o menor a 4000 km, y la velocidad de la nave es de 28000 km/h o más. Por cada hoyo negro destruido, la nave pierde 35 cápsulas de vida y 80 misiles. Intentar destruir un hoyo negro sin cumplir los requisitos necesarios resulta en una penalización de 30 cápsulas de vida y 50 misiles.
La nave comienza con 1500 cápsulas de vida y 7400 misiles. Este nivel se supera si la nave queda con al menos 6900 misiles y al menos 1000 cápsulas de vida. El jugador pierde si la nave tiene menos de 6900 misiles o menos de 1000 cápsulas de vida.

##Mecánica de velocidad: 
La velocidad cambiará cada 100 km recorridos.
**Nivel 1:** La velocidad inicial de la nave se establece en 12,000 km/h. Por cada 100 km recorridos, la velocidad puede variar en el rango de 12,000 a < 20,000 km/h.
**Nivel 2:** La velocidad inicial de la nave se establece en 20,000 km/h. Por cada 100 km recorridos, la velocidad puede variar en el rango de 20,000 a < 28,000 km/h.
**Nivel 3:** La velocidad inicial de la nave se establece en 28,000 km/h. Por cada 100 km recorridos, la velocidad puede variar en el rango de 28,000 a 40,000 km/h.