SerialPort.listDevices

a = ArduinoSMS("/dev/tty.usbmodem1d161", 9600);

(
~alloff = {fork{ 90.do{|ix| a.send( 1,ix,0); 0.01.wait}}};

~rowon = {|rn| fork{ 10.do{|ix| a.send( 1,ix+(10*rn),1); 0.05.wait}}};

~rowoff = {|rn| fork{ 10.do{|ix| a.send( 1,ix+(10*rn),0); 0.05.wait}}};

~clon = {|cn| fork{ 9.do{|ix| a.send( 1,cn+(10*ix),1); 0.05.wait}}};

~cloff = {|cn| fork{ 9.do{|ix| a.send( 1,cn+(10*ix),0); 0.05.wait}}};

~scr3 = { |numcyc spd| fork{
	numcyc.do{
		3.do{|ix|
				var tr = ix*30;
			10.do{|ix2|
				var bt = ix2;
				var tro;
				if(ix2==0, {tro=((ix+2)%3)*30}, {tro=tr});
				a.send( 3, ((bt+9)%10)+tro,0, ((bt+9)%10)+10+tro,0, ((bt+9)%10)+20+tro,0 );
				0.01.wait;
				a.send(3, bt+tr,1, bt+10+tr,1, bt+20+tr,1);
				spd.wait;
}}};~alloff.value}};

~lightsOn = {|lts| fork{lts.do{|it| a.send(1, it, 1); 0.01.wait}}};
~lightsOff = {|lts| fork{lts.do{|it| a.send(1, it, 0); 0.01.wait}}};
~seq = {|lts durs| fork{lts.do{|it ix| a.send(1,it,1); if(ix!=0,{0.01.wait;a.send(1,lts[ix-1],0)}); durs[ix%durs.size].wait};~alloff.value}};


~seqaccel = {|lts stdur acc| fork{
	lts.do{|it ix|
		var dur = stdur -(acc*ix);
		a.send(1,it,1);
		if(ix!=0,{0.01.wait;a.send(1,lts[ix-1],0)});
		dur.wait};
	~alloff.value}};
)

~seq.value([0,10,20,30,40,50,60,70,80], [0.6, 0.48, 0.384, 0.207, 0.245, 0.196, 0.157, 0.125, 0.1]);

~seqaccel.value( [0,10,20,30,40,50,60,70,80], 0.3, 0.038 );

~scr3.value(2, 0.5);
~alloff.value;

~lightsOn.value([0]);

~lightsOn.value([0,1,2,10,20,30,40,41,42,21,22, 44,54,64,74,84, 45,56,66,76,85, 7,9,17,19,28,38,48,58]);

~lightsOn.value([0,1,2,10,20,30,40,41,42,21,22, 44,54,64,74,84, 45,56,66,76,85, 7,9,17,19,28,38,48,58]);
~lightsOff.value([34]);

~lightsOn.value([24, 15, 25, 35, 45, 55, 64, 65, 66]); //1
~lightsOn.value([23, 14, 15, 26, 36, 45, 54, 63, 64, 65, 66]); //2



~tt = {|aa| aa.do{|it| it.postln}};
~tt.value([0,1,"fds",5,8,111.2345]);


~clon.value(4);
~cloff.value(4);

~rowon.value(0);
~rowon.value(1);
~rowon.value(2);
~rowon.value(3);
~rowon.value(4);
~rowon.value(5);
~rowon.value(6);
~rowon.value(7);
~rowon.value(8);

~rowoff.value(0);
~rowoff.value(1);
~rowoff.value(2);
~rowoff.value(3);
~rowoff.value(4);
~rowoff.value(5);
~rowoff.value(6);
~rowoff.value(7);
~rowoff.value(8);


//For cpLED_new_test (arduino patch)
a.send(1,0,1);
a.send(1,0,2);
a.send(1,0,3);
a.send(1,0,4);
a.send(1,0,5);
a.send(1,0,6);
a.send(1,0,7);
a.send(1,0,8);
a.send(1,0,9);

a.send(0,0,1);
a.send(0,0,2);
a.send(0,0,3);
a.send(0,0,4);
a.send(0,0,5);
a.send(0,0,6);
a.send(0,0,7);
a.send(0,0,8);
a.send(0,0,9);


a.send(1,1,0);
a.send(1,1,2);
a.send(1,1,3);
a.send(1,1,4);
a.send(1,1,5);
a.send(1,1,6);
a.send(1,1,7);
a.send(1,1,8);
a.send(1,1,9);


a.send(1,2,0);
a.send(1,2,1);
a.send(1,2,3);
a.send(1,2,4);
a.send(1,2,5);
a.send(1,2,6);
a.send(1,2,7);
a.send(1,2,8);
a.send(1,2,9);

a.send(0,2,0);
a.send(0,2,1);
a.send(0,2,3);
a.send(0,2,4);
a.send(0,2,5);
a.send(0,2,6);
a.send(0,2,7);
a.send(0,2,8);
a.send(0,2,9);

a.send(1,3,0);
a.send(1,3,1);
a.send(1,3,2);
a.send(1,3,4);
a.send(1,3,5);
a.send(1,3,6);
a.send(1,3,7);
a.send(1,3,8);
a.send(1,3,9);

a.send(0,3,0);
a.send(0,3,1);
a.send(0,3,2);
a.send(0,3,4);
a.send(0,3,5);
a.send(0,3,6);
a.send(0,3,7);
a.send(0,3,8);
a.send(0,3,9);

a.send(1,4,0);
a.send(1,4,1);
a.send(1,4,2);
a.send(1,4,3);
a.send(1,4,5);
a.send(1,4,6);
a.send(1,4,7);
a.send(1,4,8);
a.send(1,4,9);

a.send(0,4,0);
a.send(0,4,1);
a.send(0,4,2);
a.send(0,4,3);
a.send(0,4,5);
a.send(0,4,6);
a.send(0,4,7);
a.send(0,4,8);
a.send(0,4,9);


a.send(1,5,0);
a.send(1,5,1);
a.send(1,5,2);
a.send(1,5,3);
a.send(1,5,4);
a.send(1,5,6);
a.send(1,5,7);
a.send(1,5,8);
a.send(1,5,9);

a.send(0,5,0);
a.send(0,5,1);
a.send(0,5,2);
a.send(0,5,3);
a.send(0,5,4);
a.send(0,5,6);
a.send(0,5,7);
a.send(0,5,8);
a.send(0,5,9);


a.send(1,6,0);
a.send(1,6,1);
a.send(1,6,2);
a.send(1,6,3);
a.send(1,6,4);
a.send(1,6,5);
a.send(1,6,7);
a.send(1,6,8);
a.send(1,6,9);

a.send(0,6,0);
a.send(0,6,1);
a.send(0,6,2);
a.send(0,6,3);
a.send(0,6,4);
a.send(0,6,5);
a.send(0,6,7);
a.send(0,6,8);
a.send(0,6,9);


a.send(1,7,0);
a.send(1,7,1);
a.send(1,7,2);
a.send(1,7,3);
a.send(1,7,4);
a.send(1,7,5);
a.send(1,7,6);
a.send(1,7,8);
a.send(1,7,9);

a.send(0,7,0);
a.send(0,7,1);
a.send(0,7,2);
a.send(0,7,3);
a.send(0,7,4);
a.send(0,7,5);
a.send(0,7,6);
a.send(0,7,8);
a.send(0,7,9);


a.send(1,8,0);
a.send(1,8,1);
a.send(1,8,2);
a.send(1,8,3);
a.send(1,8,4);
a.send(1,8,5);
a.send(1,8,6);
a.send(1,8,7);
a.send(1,8,9);

a.send(0,8,0);
a.send(0,8,1);
a.send(0,8,2);
a.send(0,8,3);
a.send(0,8,4);
a.send(0,8,5);
a.send(0,8,6);
a.send(0,8,7);
a.send(0,8,9);


a.send(1,9,0);
a.send(1,9,1);
a.send(1,9,2);
a.send(1,9,3);
a.send(1,9,4);
a.send(1,9,5);
a.send(1,9,6);
a.send(1,9,7);
a.send(1,9,8);

a.send(0,9,0);
a.send(0,9,1);
a.send(0,9,2);
a.send(0,9,3);
a.send(0,9,4);
a.send(0,9,5);
a.send(0,9,6);
a.send(0,9,7);
a.send(0,9,8);


