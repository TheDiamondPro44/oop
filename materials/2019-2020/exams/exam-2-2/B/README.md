Трябва да имплементираме система за разпределно обработване на снимки. Всеки от вас трябва да напише приложение, което получава информация за картинка, прилага филтър върху нея и я връща.

1. Изисквания към приложението:
- когато се стартира да поиска картинка от централния сървър
- да приложи филтър sharpen върху нея (виж долу)
- да я върне на сървъра

2. Комуникация със сървъра - в https://github.com/elsys/oop/tree/master/materials/2019-2020/exams/exam-2-2/client ще намерите проект с готов HTTP клиент за приложението. Той има 2 метода:
- requestImage, който изпраща заявка и връща като резултат обект с данните за изображението
- sendImage, който изпраща готовото изображение обратно
Съдържа и класа ImageData, който съдържа:
- размерите в брой пиксели
- името на изображението
- списък със стойностите на пикселите *Важно: Всеки пиксел се състои от 4 последователни стойности в масива - червено, зелено, синьо и прозрачност. Когато обработвате пиксели трябва да имате това в предвид.*

3. Филтър sharpen - използва се за изостряне на детайлите в дадено изображение. Представлява маска с коефициенти, която се прилага върху пиксела и неговите съседи и връща стойността, която трябва да се добави(извади) към текущата. Резултатът е увеличен контраст на дадения пиксел спрямо съседите му.
Пример:
При маска
```
 0 -1  0
-1  4 -1
 0 -1  0
```
И стойности
```
10  5 10
10 20 10
10 15 10
```
Новата стойност на елемента в средата ще бъде `20 + 20*4 - 5 - 10 - 15 - 10 = 20 + 40 = 60`.
Използвайте маската от примера, като трябва да е приложите за всеки елемент независимо. Пропуснете елементи по ръба - такива, които нямат съседи.