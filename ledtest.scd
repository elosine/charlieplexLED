SerialPort.listDevices

a = ArduinoSMS("/dev/tty.usbmodem1a141", 9600);

(
~rowon = {|rn| fork{ 10.do{|ix| a.send( 1,ix+(10*rn),1); 0.05.wait}}};

~rowoff = {|rn| fork{ 10.do{|ix| a.send( 1,ix+(10*rn),0); 0.05.wait}}};

~clon = {|cn| fork{ 9.do{|ix| a.send( 1,cn+(10*ix),1); 0.05.wait}}};

~cloff = {|cn| fork{ 9.do{|ix| a.send( 1,cn+(10*ix),0); 0.05.wait}}};

~scr3 = {

};
)

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


fork{9.do{|ix| a.send(0,ix,0); 0.1.wait;}};


~on = {|ln| fork{9.do{|ix| if(ix!=ln,{a.send(1,ln,ix); ix.postln; 5.wait; })}}};
~off = {|ln|fork{9.do{|ix| if(ix!=ln,{a.send(0,ln,ix); 0.05.wait;})}};};


~off.value(2);

~on.value(2);


a.send(2, 0,0,0,0,0,0)
a.send(1, 1,0,0)
a.send(2, 0,0,1,1,0,1)
a.send(2, 0,0,0,1,0,0)


a.send(1,1,0,1);
a.send(1,1,0,0);
a.send(1,1,1,1);
a.send(1,1,2,1);
a.send(1,1,3,1);
a.send(1,1,4,1);
a.send(1,1,5,1);
a.send(1,1,1,0);

a.send(6,0,0,0,1,8,0,1,4,1,1,13,1,1,3,1,1,16,1);
a.send(1,1);


a.send(0,1);
a.send(1,1);
a.send(2,1);
a.send(3,1);
a.send(4,1);
a.send(5,1);
a.send(6,1);
a.send(7,1);
a.send(8,1);
a.send(9,1);
a.send(0,0);
a.send(1,0);
a.send(1,1,2,0);
a.send(3,0);
a.send(4,0);
a.send(5,0);
a.send(6,0);
a.send(7,0);
a.send(8,0);
a.send(9,0);


a.send(10,1);
a.send(11,1);
a.send(12,1);
a.send(13,1);
a.send(14,1);
a.send(15,1);
a.send(16,1);
a.send(17,1);
a.send(18,1);
a.send(19,1);
a.send(10,0);
a.send(11,0);
a.send(12,0);
a.send(13,0);
a.send(14,0);
a.send(15,0);
a.send(16,0);
a.send(17,0);
a.send(18,0);
a.send(19,0);
fork{20.do{|ix| a.send(2,0,ix,0,1,ix,0); 0.05.wait; }};


(~rt = Routine{
	inf.do{|ix|
		var xi = ix%16;
		if(ix==0, { a.send(1,0,0,1) },{
			if(xi==0,{
				a.send(2,0,xi,1,0,15,0) },
				{a.send(2,0,xi,1,0,xi-1,0)});
		});
		0.33.wait;
}}.play)

~rt.stop;


a = ArduinoSMS("/dev/tty.usbmodem1a141", 9600);
a.action = {|msg| msg.postln;};

(~rt2 = Routine{
	inf.do{|ix|
		var xi = ix%16;
		if(ix==0, { a.send(2, 0,1, 20,1) },{
			if(xi==0,{
				a.send(4, xi,1, xi+20,1, 15,0, 35,0) },
				{a.send(4, xi,1, xi+20,1, xi-1,0, xi+19,0)});
		});
		0.33.wait;
}}.play)
~rt2.stop;

(~rt3 = Routine{
	inf.do{|ix|
		var xi = ix%16;
		if(ix==0, { a.send(1, 0,1) },{
			if(xi==0,{
				a.send(2, xi,1, 15,0) },
				{a.send(2, xi,1, xi-1,0 )});
		});
		0.08.wait;
}}.play)
~rt3.stop;

(~rt4 = Routine{
	inf.do{|ix|
		var xi = ix%16;
		xi = xi+20;
		if(ix==0, { a.send(1, 0,1) },{
			if(xi==20,{
				a.send(2, xi,1, 35,0) },
				{a.send(2, xi,1, xi-1,0 )});
		});
		0.1.wait;
}}.play)
~rt4.stop;

a.send( 2, 0,0, 20,0 );
a.send( 2, 1,0, 21,0 );

a.send(1,7,1);
a.send(1,7,0);
a.send(1,27,0);

//All Off
fork{ 20.do{|ix| a.send(2, ix,0, ix+20,0); ix.postln; 0.01.wait}}

a.send(2, 0,1, 20,1 );
a.send(2, 1,1, 21,1 );
a.send(1, 1,0,1);
a.send(1, 0,1,1);
a.send(1, 1,1,1);
a.send(1, 0,2,1);
a.send(1, 1,2,1);
a.send(2, 0,1,1,1,1,1);
a.send(4, 0,0,0,1,0,0, 0,1,1,1,1,1 );
a.send(4, 0,0,0,1,0,0, 0,1,1,1,1,1 );



(
b = 16;
c = Routine{ inf.do{
	b = (b+1)%16;
	b.postln;
	a.send(2,0,b,1,1,b,1);
	//0.03.wait;
	//if(b==0, { a.send(2,0,15,0,1,15,0) },{ a.send(2,0,b-1,0,1,b-1,0) });
	0.2.wait;
	}
}.play;
)

c.stop

(
b = 16;
c = Routine{ inf.do{
	b = (b+1)%16;
	a.send(1,1,1,1);
	0.05.wait;
	if(b==0, { a.send(1,1,15,0) },{ a.send(1,1,b-1,0) });
	0.2.wait;
	}
}.play;
)


a = ArduinoSMS("/dev/tty.usbmodem1a141", 9600);

(~rt3 = Routine{
	inf.do{|ix|
		var xi = ix%16;
		if(ix==0, { a.send(1,0,1,1) },{
			if(xi==0,{
				a.send(2,1,xi,1,1,15,0) },
				{a.send(2,1,xi,1,1,xi-1,0)});
		});
		0.1.wait;
}}.play)

~rt3.stop;
