# Home Library

Это приложение для управления домашней библиотекой, написанное на C++ с использованием Qt Creator. Приложение позволяет пользователю добавлять книги и выполнять поиск по различным параметрам.

## Основные функции

- Добавление новой книги в библиотеку с использованием хранимой процедуры в базе данных PostgreSQL.
- Поиск книг по различным параметрам, таким как название, автор, жанр, год выпуска.

## Требования к программе

- PostgreSQL для хранения базы данных.
- Библиотека Qt для создания графического интерфейса.

## Установка и запуск

1. Создайте базу данных с помощью SQL-скрипта.
2. Отредактируйте конфигурацию подключения к базе данных в исходном коде (main.cpp).
3. Соберите и запустите приложение с использованием Qt Creator.

## Пример использования

1. Запустите приложение.
2. Для добавления книги заполните соответствующие графы информацией.
3. Нажмите на кнопку "Добавить книгу".
В текстовом поле будет выведено, удалось ли добавить книгу.
4. Для поиска книги по различным параметрам, таким как "Название", "Автор", "Жанр" и "Год выхода", выберите необходимый параметр.
5. Впишите требуемое значение в строку напротив
6. Нажмите кнопку "Найти" для отображения результатов поиска в текстовом поле.