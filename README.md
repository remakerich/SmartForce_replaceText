# SmartForce_replaceText

Задание на позицию Junior Backend Developer

Часть 1.

Реализовать программу автозамены текста во всех файлах каталога. 
Программе в качестве аргументов передаются:

- путь к каталогу с файлами
- текст, который нужно заменить 
- текст для замены.

Желательно, для каждого запуска программы создавать свой log-файл, 
содержащий историю автозамен: название файла, позиции файле, где были произведены замены, 
и примерный текст «как было» -> «как стало» (несколько символов до/после заменяемого текста).

Часть 2.

Реализовать Dockerfile, позволяющий запускать написанную программу автозамены, 
в виде Docker контейнера с внешними каталогами.
----------------------------------------------------------------------------------------------

Выполнение:
Часть 1. 
Производится поиск текста во всех .txt файлах каталога. Для удобства разработки и тестирования, 
программа открывает только .txt файлы. Но при желании можно добавить любые другие форматы.

Часть 2. 
Реализован Dockerfile, который создает образ alpine с бинарным файлом приложения (~5.5Mb). 
Для этого создается отдельный образ alpine с gcc (~200Mb) для компиляции программы.

Пример Dockerfile находится в репозитории
