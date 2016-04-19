ISR(reference call){
	start timer;
}
ISR(mic 1){
	Time 1:= Timer;
	recieved:=recieved+1;
}
ISR(mic 2){
	Time 2:= Timer;
	recieved:=recieved+1;
}
ISR(mic 3){
	Time 3:= Timer;
	recieved:=recieved+1;
}

While recieved = 3{
	time_1:= time_1-overhead_time;	//remove overhead time
	time_2:= time_2-overhead_time;	//remove overhead time
	time_3:= time_3-overhead_time;	//remove overhead time
	length_1:=time_1*speed_of_sound/clock_freq
	length_2:=time_2*speed_of_sound/clock_freq
	length_3:=time_3*speed_of_sound/clock_freq
	angle_1:=acos((length_1^2+mic_distance^2-length_2^2)/(2*length_1*mic_distance));
	angle_2:=acos((length_2^2+mic_distance^2-length_3^2)/(2*length_2*mic_distance));
	angle_3:=acos((length_3^2+mic_distance^2-length_1^2)/(2*length_3*mic_distance));
	read compas_angle;
	angle_1:=angle_1+compas_angle;
	angle_2:=angle_2+compas_angle;
	angle_3:=angle_3+compas_angle;
	x_1:=sin(angle_1)*length_1;
	x_2:=sin(angle_2)*length_2;
	x_3:=sin(angle_3)*length_3;
	y_1:=cos(angle_1)*length_1;
	y_2:=cos(angle_2)*length_2;
	y_3:=cos(angle_3)*length_3;
	x_center=x_1+center_distance_x;
	y_center:=Y_1+center_distance_y;
	recieved:=0;
}