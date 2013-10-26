#include "core.h"
#include "pil.h"

int addFive(int num){
    return num + 5;
}

int dostuff(){
	int num  = giveTen();
	num = addFive(num);
	return num;
}