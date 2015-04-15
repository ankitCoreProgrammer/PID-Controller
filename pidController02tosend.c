#include"stdio.h"

//kp=proportional k, kd=derivative k, ki=integral k, 
//ei=integral error, ed=derivative error, ep=previous error, e=present error
//wp=previous omega, w=present omega, wd=desired omega
//td=time delta
float kd,kp,ki,ei,ed,ep,e,td;
volatile float w,wd,wp;
	
volatile float pidController(volatile float *w,volatile float wd){
	int i,j;
	// i think in practical implementation the we add just difference of pid regulator to the trust value
	td=1;
	kp=kd=ki=.91;//.9999;//.91;//.9100;
	kd=.002;//0;//.002;//.002000;
	ki=.09;//0;//.09;//.009;//.43;
	e=wd-(*w);
	i=0;
	while((i++<1200)||
		(e>.01 && e<-.01)){
		ed= (e-ep)/td;
		ei= e*td + ei*td;///ep*td;
		*w= e*kp + ei*ki + ed*kd;
		ep=e;
		e=wd-(*w);
		printf("%f\n",*w);
		//printf("%f\t%f\t%f\t%f\n",*w,e,ed,ei);
		//if(e<.1 && e>(-.1)){
		//	break;
		//}
	}
	return *w;
}

void main(){
	int i,j;
	wd=100;
	wp=w=20;
	ep=ed=ei=0;
	printf("%f\n",pidController(&w,wd));	
}
