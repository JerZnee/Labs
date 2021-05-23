#!/usr/bin/env bash

usage() {
	echo "Использование: ./repl [ПАРАМЕТР] [КАТАЛОГ]"
	echo "Если директория не указана, поступит запрос на указание директории"
	echo "Заменяет \\ на / во всех файлах заданного каталога"
	echo ""
	echo "-d directory/	указать нужную директорию"
	echo "-h --help	показать справку"
}

while (( $# > 0 )); do
	CUR="$1"
	if [[ "$CUR" == '-d' ]]; then
		DIR="$2"
		shift
	elif [[ "$CUR" == '-h' ]]; then
		HELP=1
		usage
	else
		ERR=1
	echo "неверный ключ"
	echo "По команле './repl -h' можно получить дополнительную информацию"
	fi
	shift
done


while [[ "$DIR" == '' ]]; do
	if [[ "$HELP" == 1 || "$ERR" == 1 ]]; then
		exit 1
	fi
		echo "Введите директорию"
		read DIR
	if [[ !(-d $DIR) ]]; then
		echo "Директория не найдена"
		DIR=''
	fi
done

find "$DIR" -type f -name "*.txt" -exec sed -e 's/\\/\//g' {} +
