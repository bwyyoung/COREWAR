#!/bin/bash --posix

typeset -r COREWAR_DIR="../"

typeset -r FILE=$1
typeset -r TMP_FILE=/tmp/cuted_

# get file size
eval $(stat -s ${FILE})

typeset -r CHAR_MAX=$(echo ${st_size})

for (( i = 1; i < $CHAR_MAX; i++ )); do
	head -c $i ${FILE} > ${TMP_FILE}${i}.cor
	echo -e "\033[K\r[$i/${CHAR_MAX}] files created\c"
done

for (( i = 0; i < $CHAR_MAX; i++ )); do
	${COREWAR_DIR}corewar ${TMP_FILE}${i}.cor
done

rm /tmp/cuted_*