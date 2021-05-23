

int pro(int a, int b) {
	if (a%b==0){
		return a%b;
	} else if (a%b==1) {
		return a/b;
	} else {
		return a;
	}
}
