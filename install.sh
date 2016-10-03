#!/bin/bash

PREFIX=/usr/local

for k in "$@"; do
	case "$k" in
		--prefix=*)
			PREFIX=( "${k#*=}" )
			shift
			;;
		*)
			echo Uknown options "$k"
			exit -1
	esac
done;

echo "Installing Alice with PREFIX=$PREFIX"

declare -a rollback

function do_cleanup ()
	{
	for k in "${rollback[@]}"; do
		echo "$k"
		eval "$k"
	done
	}

function uninstall_cmds ()
	{
	echo "PREFIX="'"'"$PREFIX"'"'
	for k in "${rollback[@]}"; do
		echo "$k"
	done
	}

trap '
if [ $? -ne 0 ]; then
	echo "Installation to $PREFIX failed"
	do_cleanup
fi
' 0

trap 'do_cleanup
exit 1' SIGINT SIGTERM 

function transaction ()
	{
	echo "$1"
	eval "$1"
	rollback=("$2" "${rollback[@]}")
	return 0
	}

set -e
transaction 'mkdir -p "$PREFIX"/include/alice' \
	'rmdir "$PREFIX"/include/alice && rmdir "$PREFIX"/include && rmdir "$PREFIX"'
transaction 'cp -n __targets/*.hpp "$PREFIX"/include/alice' \
	'rm "$PREFIX"/include/alice/*.hpp'
transaction 'mkdir -p "$PREFIX"/lib' \
	'rmdir "$PREFIX"/lib'
transaction 'cp -n __targets/libalice.a "$PREFIX/lib"'\
	'rm "$PREFIX"/lib/libalice.a'

if [ "$(id -u)" == "0" ]; then
	chmod -R o+r "$PREFIX"/include
	chmod -R o+r "$PREFIX"/bin
	chmod -R o+r "$PREFIX"/lib
	chmod -R o+r "$PREFIX"/include/alice
fi


uninstall_cmds > .uninstall.sh
chmod u+x .uninstall.sh

echo "Alice has now been installed"

if ! [[ "$CPATH" == ?(*:)"$PREFIX/include"?(:*) ]];then
	echo " * If you wish to use libalice, \
you may need to add $PREFIX/include to the CPATH variable."
fi

if ! [[ "$LIBRARY_PATH" == ?(*:)"$PREFIX/lib"?(:*) ]];then
	echo " * If you wish to use libalice, \
you may need to add $PREFIX/lib to the LIBRARY_PATH variable."
fi

if ! [[ "$LD_LIBRARY_PATH" == ?(*:)"$PREFIX/lib"?(:*) ]];then
	echo " * If you wish to use libalice you may need to add $PREFIX/lib to the LD_LIBRARY_PATH variable."
fi
