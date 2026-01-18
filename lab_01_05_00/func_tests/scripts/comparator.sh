#!/bin/bash

# Функция, определяющая, является ли аргумент ЧПТ
isfloat() {
	if echo "$1" | grep -qE "e"; then
		if echo "$1" | grep -qE "^[-+]?[0-9]*[\.]?[0-9]*[e][-+]?[0-9]+$" && ! echo "$1" | grep -qE "^[-+]?[\.]$" && ! echo "$1" | grep -qE "^[-+]?[\.]?[e][0-9]*$" && ! echo "$1" | grep -qE "^[-+]?[\.]?[0-9]*[e]$"; then
			return 0
		fi
	elif echo "$1" | grep -qE "\."; then
		if echo "$1" | grep -qE "^[-+]?[0-9]*[\.][0-9]*$" && ! echo "$1" | grep -qE "^[-+]?[\.]$"; then
			return 0
		fi
	else
		if echo "$1" | grep -qE "^[-+]?[0-9]+$"; then
			return 0
		fi
	fi
	return 1

}

verbose=0

# Если некорректное число аргументов
if [ $# -ne 2 ] && [ $# -ne 3 ]; then
	echo 2<"Usage: $(basename "$0") file1 file2 [-v]"
	exit 100
fi

# Если переданные аргументы не являются файлами
if ! [ -f "$1" ] || ! [ -f "$2" ]; then
	echo 2<"Incorrect file(s)"
	exit 200
fi

# Проверка на наличие ключа -v
if [ "$3" == "-v" ] || [ "$3" == "--verbose" ]; then
	verbose=1
fi

tmp1=$(mktemp)
tmp2=$(mktemp)

flag_ans=0
float_counter1=0

IFS_OLD=$IFS
# Проход по file1 и запись ЧПТ из него в tmp1
while IFS="" read -r line; do
	for word in $line; do
		if isfloat "$word"; then
			float_counter1=$((float_counter1 + 1))
			echo "$word" >>"$tmp1"
		fi
	done
done <"$1"

# Проход по file2 и запись ЧПТ из него в tmp2
while IFS="" read -r line; do
	for word in $line; do
		if isfloat "$word"; then
			echo "$word" >>"$tmp2"
		fi
	done
done <"$2"

# Последовательности равны если равны tmp1 и tmp2
if cmp -s "$tmp1" "$tmp2"; then
	flag_ans=1
fi

rm "$tmp1"
rm "$tmp2"
IFS=$IFS_OLD

if [ "$flag_ans" -eq 0 ]; then
	if [ "$verbose" -eq 1 ]; then
		echo "float sequences aren't equal"
	fi
	exit 1
else
	if [ "$verbose" -eq 1 ]; then
		echo "float sequences are equal"
		echo "number of elements = $float_counter1"
	fi
	exit 0
fi