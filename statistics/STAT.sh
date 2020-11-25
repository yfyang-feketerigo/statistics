#!/bin/bash
echo 'enter start sample number:'
read nstart
echo 'enter stop sample number:'
read nstop
thisfoldername='Statistics'
exc='statistics.exe'
for ((i = $nstart; i <= $nstop; i++)); do
	echo -e "\033[31m$i start\033[0m"
	cd ..
	cp -r ./$thisfoldername ./$i/
	cd ./$i/$thisfoldername
	./$exc
	cd ..
	echo -e "\033[31m$i finshed\033[0m"
done
