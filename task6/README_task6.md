### Task6
### Пшеничнкивов Глеб, 212


## Библиотеки
Программа ипользует следующие библиотеки:  
```
#include <stdio.h>  
#include <stdlib.h>   
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/ipc.h>  
#include <sys/sem.h>  
#include <time.h>
#include <signal.h>
```

##  Функции
Прогамма обращается в ходе решения к следующим функуиям:   
* ``void eat(int i)``  
моделирует процесс приема пищи у филосова (процесс на 3 секунды)

* ``void think(int i)``  
моделирует процесс размышления у филосова (процесс на 3 секунды)

* ``void take_fork(int i)``  
филосов берет вилку с номером i (уменшает значение семафора на 1, соответсвующего данной вилке)

* ``void put_fork(int i)``  
филосов берет вилку с номером i (увеличивает значение семафора на 1, соответсвующего данной вилке)

* ``void up(int num)``  
увеличивает значение счетчика - семафора на 1 (счетчик соответствует кол-ву филосов сидящих за столом)

* `void down(int num)`  
уменьшает значение счетчика - семафора на 1 (счетчик соответствует кол-ву филосов сидящих за столом)


* `void philosopher (int i)`  
основная функция, в которой филосов думает, садится за стол (увеличивая при этом счетчик сидящих за столов филосовов), берет левую и правую вилки, ест. кладет обратно обе вилки, встает из-за стола (уменьшая при этом счетчик сидящих за столов филосовов)


## Основная программа 
Создаются N семафоров (для каждой вилки - один семафор) и заполняется единицами (1 - вилка свободна, 0 - занята). Создается семафор для счетчика филосовов, сидящих за столов и задается начальное значение 4 (так как за столов может сидеть толоко 4 филосова одновременно, чтобы не было критического слуачая, когда все вилки взяты и филосовы просто ждут). Затем создается N процессов (для каждого филосова свой процесс) и запускатеся функция `void philosopher (int i)`. Затем родительский процесс ждет завершения сыновей, удаляет семафоры и завершается.

## Запуск
Запуск осуществляется при помощи команды ./task6

